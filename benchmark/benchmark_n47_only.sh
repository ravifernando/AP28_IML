#!/bin/bash
# Benchmark: run only the 4-prime (n47) outer loop variant
# for the special k29*41 search with special prime 31.
# Runs K=1..10, records timing and solutions per K.

set -e

DIR="$(cd "$(dirname "$0")/.." && pwd)"
SRCDIR="$DIR/AP28_kp_q Files"
RESDIR="$DIR/benchmark/results"

mkdir -p "$RESDIR"

echo "=== Compiling n47 (4 outer primes) ==="
cd "$SRCDIR"

GMP_PREFIX=$(brew --prefix gmp 2>/dev/null || echo "/opt/homebrew/opt/gmp")
CFLAGS="-O2 -I$GMP_PREFIX/include -L$GMP_PREFIX/lib"

gcc $CFLAGS -o "$RESDIR/run_n47" run_k29_41_special31.c -lgmp -lm
echo "Compiled."
echo ""

SUMMARY="$RESDIR/summary_n47.txt"
> "$SUMMARY"

echo "=== Running n47 benchmark K=1..10 ==="
echo ""

for K in $(seq 1 10); do
    echo "--- K=$K ---"
    echo "  Running n47 (4 outer primes)..."
    "$RESDIR/run_n47" "$K" "$RESDIR/k${K}_n47.txt"
    echo ""
done

echo "=== Timing Summary (n47) ===" | tee -a "$SUMMARY"
printf "%-4s  %20s\n" "K" "n47 (4 outer)" | tee -a "$SUMMARY"
printf "%-4s  %20s\n" "----" "--------------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    T47=$(grep "TIME:" "$RESDIR/k${K}_n47.txt" | sed 's/TIME: //' | sed 's/ microseconds//')
    printf "%-4d  %17s us\n" "$K" "$T47" | tee -a "$SUMMARY"
done

echo "" | tee -a "$SUMMARY"
echo "=== Solution Counts (n47) ===" | tee -a "$SUMMARY"
printf "%-4s  %12s\n" "K" "n47" | tee -a "$SUMMARY"
printf "%-4s  %12s\n" "----" "------------" | tee -a "$SUMMARY"

for K in $(seq 1 10); do
    C47=$(grep -cv "TIME:" "$RESDIR/k${K}_n47.txt" 2>/dev/null || echo 0)
    printf "%-4d  %12d\n" "$K" "$C47" | tee -a "$SUMMARY"
done

echo ""
echo "Results saved in: $RESDIR/"
echo "Summary saved in: $SUMMARY"

# Cleanup binary
rm -f "$RESDIR/run_n47"
