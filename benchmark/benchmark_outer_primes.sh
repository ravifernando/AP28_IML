#!/bin/bash
# Benchmark: compare 2-prime (n37), 3-prime (n43), and 4-prime (n47) outer loop variants
# for the special k29*41 search with special prime 31.
# Runs K=1..10, interleaved: for each K, run n37 then n43 then n47.
# Results are recorded per-K per-variant and summarized at the end.

set -e

DIR="$(cd "$(dirname "$0")/.." && pwd)"
SRCDIR="$DIR/AP28_kp_q Files"
RESDIR="$DIR/benchmark/results"

mkdir -p "$RESDIR"

echo "=== Compiling all 3 variants ==="
cd "$SRCDIR"

GMP_PREFIX=$(brew --prefix gmp 2>/dev/null || echo "/opt/homebrew/opt/gmp")
CFLAGS="-O2 -I$GMP_PREFIX/include -L$GMP_PREFIX/lib"

echo "Compiling n37 (2 outer primes)..."
gcc $CFLAGS -o "$RESDIR/run_n37" run_k29_41_special31_n37.c -lgmp -lm
echo "Compiling n43 (3 outer primes)..."
gcc $CFLAGS -o "$RESDIR/run_n43" run_k29_41_special31_n43.c -lgmp -lm
echo "Compiling n47 (4 outer primes)..."
gcc $CFLAGS -o "$RESDIR/run_n47" run_k29_41_special31.c -lgmp -lm
echo "All compiled."
echo ""

# Clear summary file
SUMMARY="$RESDIR/summary.txt"
> "$SUMMARY"

echo "=== Running benchmark K=1..10 ==="
echo ""

for K in $(seq 1 10); do
    echo "--- K=$K ---"

    echo "  Running n37 (2 outer primes)..."
    "$RESDIR/run_n37" "$K" "$RESDIR/k${K}_n37.txt"

    echo "  Running n43 (3 outer primes)..."
    "$RESDIR/run_n43" "$K" "$RESDIR/k${K}_n43.txt"

    echo "  Running n47 (4 outer primes)..."
    "$RESDIR/run_n47" "$K" "$RESDIR/k${K}_n47.txt"

    echo ""
done

echo "=== Timing Summary ===" | tee -a "$SUMMARY"
printf "%-4s  %20s  %20s  %20s\n" "K" "n37 (2 outer)" "n43 (3 outer)" "n47 (4 outer)" | tee -a "$SUMMARY"
printf "%-4s  %20s  %20s  %20s\n" "----" "--------------------" "--------------------" "--------------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    T37=$(grep "TIME:" "$RESDIR/k${K}_n37.txt" | sed 's/TIME: //' | sed 's/ microseconds//')
    T43=$(grep "TIME:" "$RESDIR/k${K}_n43.txt" | sed 's/TIME: //' | sed 's/ microseconds//')
    T47=$(grep "TIME:" "$RESDIR/k${K}_n47.txt" | sed 's/TIME: //' | sed 's/ microseconds//')
    printf "%-4d  %17s us  %17s us  %17s us\n" "$K" "$T37" "$T43" "$T47" | tee -a "$SUMMARY"
done

echo "" | tee -a "$SUMMARY"
echo "=== Solution Counts ===" | tee -a "$SUMMARY"
printf "%-4s  %12s  %12s  %12s\n" "K" "n37" "n43" "n47" | tee -a "$SUMMARY"
printf "%-4s  %12s  %12s  %12s\n" "----" "------------" "------------" "------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    C37=$(grep -cv "TIME:" "$RESDIR/k${K}_n37.txt" 2>/dev/null || echo 0)
    C43=$(grep -cv "TIME:" "$RESDIR/k${K}_n43.txt" 2>/dev/null || echo 0)
    C47=$(grep -cv "TIME:" "$RESDIR/k${K}_n47.txt" 2>/dev/null || echo 0)
    printf "%-4d  %12d  %12d  %12d\n" "$K" "$C37" "$C43" "$C47" | tee -a "$SUMMARY"
done

echo "" | tee -a "$SUMMARY"
echo "=== Cross-variant result diffs ===" | tee -a "$SUMMARY"

ANY_DIFF=0
for K in $(seq 1 10); do
    # Compare n37 vs n43
    D1=$(diff <(grep -v "TIME:" "$RESDIR/k${K}_n37.txt" | sort) \
              <(grep -v "TIME:" "$RESDIR/k${K}_n43.txt" | sort) 2>/dev/null || true)
    # Compare n43 vs n47
    D2=$(diff <(grep -v "TIME:" "$RESDIR/k${K}_n43.txt" | sort) \
              <(grep -v "TIME:" "$RESDIR/k${K}_n47.txt" | sort) 2>/dev/null || true)
    if [ -n "$D1" ] || [ -n "$D2" ]; then
        ANY_DIFF=1
        echo "K=$K: DIFFERENCES FOUND" | tee -a "$SUMMARY"
        if [ -n "$D1" ]; then
            echo "  n37 vs n43:" | tee -a "$SUMMARY"
            echo "$D1" | tee -a "$SUMMARY"
        fi
        if [ -n "$D2" ]; then
            echo "  n43 vs n47:" | tee -a "$SUMMARY"
            echo "$D2" | tee -a "$SUMMARY"
        fi
    fi
done

if [ "$ANY_DIFF" -eq 0 ]; then
    echo "All variants found identical solutions for every K." | tee -a "$SUMMARY"
fi

echo ""
echo "Full results saved in: $RESDIR/"
echo "Summary saved in: $SUMMARY"

# Cleanup binaries
rm -f "$RESDIR/run_n37" "$RESDIR/run_n43" "$RESDIR/run_n47"
