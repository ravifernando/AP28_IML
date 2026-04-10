#!/bin/bash
# Benchmark: run only the 5-prime (n53) outer loop variant
# for the special k29*41 search with special prime 31.
# Runs K=1..10, records timing and solutions per K.

set -e

DIR="$(cd "$(dirname "$0")/.." && pwd)"
SRCDIR="$DIR/AP28_kp_q Files"
RESDIR="$DIR/benchmark/results"

mkdir -p "$RESDIR"

echo "=== Compiling n53 (5 outer primes) ==="
cd "$SRCDIR"

GMP_PREFIX=$(brew --prefix gmp 2>/dev/null || echo "/opt/homebrew/opt/gmp")
CFLAGS="-O2 -I$GMP_PREFIX/include -L$GMP_PREFIX/lib"

gcc $CFLAGS -o "$RESDIR/run_n53" run_k29_41_special31_n53.c -lgmp -lm
echo "Compiled."
echo ""

SUMMARY="$RESDIR/summary_n53.txt"
> "$SUMMARY"

echo "=== Running n53 benchmark K=1..10 ==="
echo ""

for K in $(seq 1 10); do
    echo "--- K=$K ---"
    echo "  Running n53 (5 outer primes)..."
    "$RESDIR/run_n53" "$K" "$RESDIR/k${K}_n53.txt"
    echo ""
done

echo "=== Timing Summary (n53) ===" | tee -a "$SUMMARY"
printf "%-4s  %20s\n" "K" "n53 (5 outer)" | tee -a "$SUMMARY"
printf "%-4s  %20s\n" "----" "--------------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    T53=$(grep "TIME:" "$RESDIR/k${K}_n53.txt" | sed 's/TIME: //' | sed 's/ microseconds//')
    printf "%-4d  %17s us\n" "$K" "$T53" | tee -a "$SUMMARY"
done

echo "" | tee -a "$SUMMARY"
echo "=== Solution Counts (n53) ===" | tee -a "$SUMMARY"
printf "%-4s  %12s\n" "K" "n53" | tee -a "$SUMMARY"
printf "%-4s  %12s\n" "----" "------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    C53=$(grep -cv "TIME:" "$RESDIR/k${K}_n53.txt" 2>/dev/null || echo 0)
    printf "%-4d  %12d\n" "$K" "$C53" | tee -a "$SUMMARY"
done

echo "" | tee -a "$SUMMARY"
echo "=== Cross-check: n53 subset of n47 ===" | tee -a "$SUMMARY"

ANY_DIFF=0
for K in $(seq 1 10); do
    if [ -f "$RESDIR/k${K}_n47.txt" ]; then
        # Every n53 solution should appear in n47
        EXTRA=$(comm -23 \
            <(grep -v "TIME:" "$RESDIR/k${K}_n53.txt" | sort) \
            <(grep -v "TIME:" "$RESDIR/k${K}_n47.txt" | sort) 2>/dev/null || true)
        if [ -n "$EXTRA" ]; then
            ANY_DIFF=1
            echo "K=$K: n53 has solutions NOT in n47 (UNEXPECTED):" | tee -a "$SUMMARY"
            echo "$EXTRA" | tee -a "$SUMMARY"
        fi
    fi
done

if [ "$ANY_DIFF" -eq 0 ]; then
    echo "Confirmed: n53 is a subset of n47 for all K." | tee -a "$SUMMARY"
fi

echo ""
echo "Results saved in: $RESDIR/"
echo "Summary saved in: $SUMMARY"

# Cleanup binary
rm -f "$RESDIR/run_n53"
