#!/usr/bin/env bash
#
# run_benchmark.sh - Benchmark for AP28 k*p*q search configurations.
#
# Test 1: Which special-type is fastest for k29_31?
#   a) k29_31 non-special      (extraPrimes=899, special=0)   {29,31,0}
#   b) k29_31 semi-special 37  (extraPrimes=899, special=37)  {29,31,37}
#   c) k29 semi-special 31     (extraPrimes=29,  special=31)  {29,0,31}
#
# Test 2: Which sieve limit is fastest?
#   a) SIEVE_LIMIT=463
#   b) SIEVE_LIMIT=541  (current default)
#   c) SIEVE_LIMIT=601
#
# Both tests use K=1..6, report timing and result counts by AP length.
#
# Results:
#   benchmark/results/timing_summary.txt
#   benchmark/results/test1_*.log
#   benchmark/results/test2_*.log
#
# Usage:
#   cd <project root>
#   bash benchmark/run_benchmark.sh
#   N_REPEATS=5 bash benchmark/run_benchmark.sh
#
set -euo pipefail

# ---------- tunables ----------
K_START="${K_START:-1}"
K_END="${K_END:-6}"
SHIFT="${SHIFT:-0}"
N_REPEATS="${N_REPEATS:-1}"

# ---------- paths ----------
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$SCRIPT_DIR"
RESULTS_DIR="$SCRIPT_DIR/results"

mkdir -p "$RESULTS_DIR"

# ---------- compile ----------
GMP_PREFIX="$(brew --prefix gmp 2>/dev/null || echo /opt/homebrew/opt/gmp)"
COMMON_CFLAGS=(-O3 -std=c11 -DBENCH_MODE "-I$PROJECT_ROOT" "-I$GMP_PREFIX/include" "-L$GMP_PREFIX/lib")

echo ">>> Compiling benchmark binaries ..."

# Default binary (SIEVE_LIMIT undefined = sieve to 541, same as current)
gcc "${COMMON_CFLAGS[@]}" \
    "$BUILD_DIR/bench_kp_q.c" \
    -o "$BUILD_DIR/bench_default" \
    -lgmp -lm
echo "    bench_default (sieve 541)"

# Sieve limit 463
gcc "${COMMON_CFLAGS[@]}" -DSIEVE_LIMIT=463 \
    "$BUILD_DIR/bench_kp_q.c" \
    -o "$BUILD_DIR/bench_sieve463" \
    -lgmp -lm
echo "    bench_sieve463"

# Sieve limit 601
gcc "${COMMON_CFLAGS[@]}" -DSIEVE_LIMIT=601 \
    "$BUILD_DIR/bench_kp_q.c" \
    -o "$BUILD_DIR/bench_sieve601" \
    -lgmp -lm
echo "    bench_sieve601"

echo ""

# ---------- helpers ----------

# Median of a list of integers (one per line)
median() {
    sort -n | awk '{a[NR]=$1} END {
        if (NR%2==1) print a[(NR+1)/2];
        else         print int((a[NR/2]+a[NR/2+1])/2)
    }'
}

# CPU warm-up: spin for ~0.5 s so frequency ramps up
warmup_cpu() {
    python3 -c "
import time, math
end = time.monotonic() + 0.5
s = 0.0
while time.monotonic() < end:
    for i in range(10000):
        s += math.sin(i)
" 2>/dev/null || true
}

# Count results by AP length and compute mid/long ratio.
# Args: <result_log>
# "mid-length": AP_Length 14-19, "long-length": AP_Length >= 20
count_results() {
    local result_log="$1"
    local mid long
    mid=$(grep -v '^#' "$result_log" | awk '$1 >= 14 && $1 <= 19' | wc -l | tr -d ' ')
    long=$(grep -v '^#' "$result_log" | awk '$1 >= 20' | wc -l | tr -d ' ')
    echo "      mid-length (14-19): $mid   long-length (>=20): $long   ratio: ${mid}/${long}"
}

# Run one configuration N_REPEATS times.
# Args: <label> <binary> <extraPrimes> <special_filter> <result_log>
run_config() {
    local label="$1"
    local binary="$2"
    local ep="$3"
    local sf="$4"
    local result_log="$5"
    local -a times=()

    # Header in result log
    printf "# %s  |  K=[%s..%s] SHIFT=%s extraPrimes=%s special=%s\n" \
           "$label" "$K_START" "$K_END" "$SHIFT" "$ep" "$sf" > "$result_log"
    printf "# Format: AP_Length  K  FirstTerm\n" >> "$result_log"
    printf "# -----------------------------------------------\n" >> "$result_log"

    for ((r = 1; r <= N_REPEATS; r++)); do
        echo "    repeat $r / $N_REPEATS ..."

        warmup_cpu

        local tmp_stderr
        tmp_stderr=$(mktemp)

        nice -n 0 "$binary" \
            "$K_START" "$K_END" "$SHIFT" "$ep" "$sf" \
            >> "$result_log" 2>"$tmp_stderr"

        # Extract total time from the "=== Total: <us> ===" line
        local total_us
        total_us=$(grep 'Total:' "$tmp_stderr" | sed 's/.*Total: \([0-9]*\).*/\1/')

        # Also dump per-K times into the result log (as comments)
        sed 's/^/# /' "$tmp_stderr" >> "$result_log"

        times+=("$total_us")
        echo "      -> ${total_us} us"
        rm -f "$tmp_stderr"
    done

    # Compute min / median / max
    local min_t max_t med_t
    min_t=$(printf '%s\n' "${times[@]}" | sort -n | head -1)
    max_t=$(printf '%s\n' "${times[@]}" | sort -n | tail -1)
    med_t=$(printf '%s\n' "${times[@]}" | median)

    printf "%-35s  min=%10s us  median=%10s us  max=%10s us\n" \
           "$label" "$min_t" "$med_t" "$max_t" | tee -a "$RESULTS_DIR/timing_summary.txt"

    # Count and display result categories
    count_results "$result_log" | tee -a "$RESULTS_DIR/timing_summary.txt"
}

# ---------- main ----------
echo "============================================================"
echo "  AP28 k*p*q Benchmark"
echo "  K range  : $K_START .. $K_END"
echo "  SHIFT    : $SHIFT"
echo "  Repeats  : $N_REPEATS"
echo "  Date     : $(date)"
echo "============================================================"
echo ""

# Header for summary
{
    echo "============================================================"
    echo "  AP28 k*p*q Benchmark Timing Summary"
    echo "  K range  : $K_START .. $K_END"
    echo "  SHIFT    : $SHIFT"
    echo "  Repeats  : $N_REPEATS"
    echo "  Date     : $(date)"
    echo "  Host     : $(uname -a)"
    echo "============================================================"
    echo ""
} > "$RESULTS_DIR/timing_summary.txt"

# ==========================================
# TEST 1: Special-type comparison
# ==========================================
echo "=========================================="
echo "  TEST 1: Special-type comparison (k29_31)"
echo "==========================================" | tee -a "$RESULTS_DIR/timing_summary.txt"
{
    echo ""
    echo "=========================================="
    echo "  TEST 1: Special-type comparison (k29_31)"
    echo "=========================================="
    echo ""
} >> "$RESULTS_DIR/timing_summary.txt"

echo ""
# Skipped T1a (k29_31 non-special) — already run.
# run_config "T1a: k29_31 non-special" "$BUILD_DIR/bench_default" 899 0 \
#     "$RESULTS_DIR/test1_nonspecial.log"

echo ">>> [1b/3] k29_31 semi-special 37 {29,31,37} (extraPrimes=899, special=37)"
run_config "T1b: k29_31 semi-special 37" "$BUILD_DIR/bench_default" 899 37 \
    "$RESULTS_DIR/test1_semispecial37.log"
echo ""

echo ">>> [1c/3] k29 semi-special 31 {29,0,31} (extraPrimes=29, special=31)"
run_config "T1c: k29 semi-special 31" "$BUILD_DIR/bench_default" 29 31 \
    "$RESULTS_DIR/test1_semispecial31.log"
echo ""

# ==========================================
# TEST 2: Sieve-limit comparison
# ==========================================
# Uses k29_31 semi-special 37 (the current default config) for all runs.
echo "=========================================="
echo "  TEST 2: Sieve-limit comparison"
echo "==========================================" | tee -a "$RESULTS_DIR/timing_summary.txt"
{
    echo ""
    echo "=========================================="
    echo "  TEST 2: Sieve-limit comparison"
    echo "  (using k29_31 semi-special 37 for all)"
    echo "=========================================="
    echo ""
} >> "$RESULTS_DIR/timing_summary.txt"

echo ""
echo ">>> [2a/3] Sieve limit 463 (extraPrimes=899, special=37)"
run_config "T2a: sieve_limit=463" "$BUILD_DIR/bench_sieve463" 899 37 \
    "$RESULTS_DIR/test2_sieve463.log"
echo ""

echo ">>> [2b/3] Sieve limit 541 (extraPrimes=899, special=37)"
run_config "T2b: sieve_limit=541" "$BUILD_DIR/bench_default" 899 37 \
    "$RESULTS_DIR/test2_sieve541.log"
echo ""

echo ">>> [2c/3] Sieve limit 601 (extraPrimes=899, special=37)"
run_config "T2c: sieve_limit=601" "$BUILD_DIR/bench_sieve601" 899 37 \
    "$RESULTS_DIR/test2_sieve601.log"
echo ""

# ==========================================
# Final summary
# ==========================================
echo "============================================================"
echo "  Done!  Results in: $RESULTS_DIR/"
echo "============================================================"
echo ""
cat "$RESULTS_DIR/timing_summary.txt"
