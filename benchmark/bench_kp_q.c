/*
 * bench_kp_q.c - Benchmark harness for AP28 k*p*q searches
 *
 * Compiles against the same search code as timing64_kp_q.c but accepts
 * command-line arguments so the benchmark script can sweep a K range
 * and select among non-special, special, and semi-special modes.
 *
 * Usage:
 *   ./bench_kp_q <K_start> <K_end> <SHIFT> <extraPrimes> [special_filter]
 *
 * special_filter (optional, default -1):
 *   -1 : use default lookup (skip p=29 entries with special=0)
 *    0 : match only entries with special=0  (e.g. k29_31 non-special)
 *   31 : match only entries with special=31 (e.g. k29 with 31 semi-special)
 *   37 : match only entries with special=37 (e.g. k29_31 with 37 semi-special)
 *
 * Example:
 *   ./bench_kp_q 1 6 0 899 0     # k29_31 non-special {29,31,0}
 *   ./bench_kp_q 1 6 0 899 37    # k29_31 semi-special 37 {29,31,37}
 *   ./bench_kp_q 1 6 0 29  31    # k29 semi-special 31 {29,0,31}
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

/* ---- identical helpers from the original timing64_kp_q.c ---- */

#include "../AP28_kp_q Files/PrimeQ64.h"

long long microtime(void)
{
    struct timeval start;
    long long result;
    gettimeofday(&start, NULL);
    result = start.tv_sec * 1000000LL + start.tv_usec;
    return result;
}

long long mytime, totaltime;

/* Global special filter for BENCH_MODE lookup in AP28_kp_q.h */
int g_special_filter = -1;

/* ReportSolution now prints to stdout; the shell script redirects this
   to the appropriate log file. */
void ReportSolution(int AP_Length, int difference, long long First_Term)
{
    if (AP_Length >= 14) {
        printf("%d %d %lld\n", AP_Length, difference, First_Term);
    }
}

/* ---- pull in abmod, constants table, and search function ---- */

#include "../abmod.h"
#include "../AP28_kp_q Files/CONST_kp_q.H"
#include "../AP28_kp_q Files/AP28_kp_q.h"

/* ---- main ---- */

int main(int argc, char *argv[])
{
    if (argc < 5 || argc > 6) {
        fprintf(stderr,
                "Usage: %s <K_start> <K_end> <SHIFT> <extraPrimes> [special_filter]\n",
                argv[0]);
        return 1;
    }

    int K_start      = atoi(argv[1]);
    int K_end        = atoi(argv[2]);
    int SHIFT        = atoi(argv[3]);
    int extraPrimes  = atoi(argv[4]);

    if (argc == 6) {
        g_special_filter = atoi(argv[5]);
    }

    fprintf(stderr, "=== Benchmark: K=[%d..%d], SHIFT=%d, extraPrimes=%d, special_filter=%d ===\n",
            K_start, K_end, SHIFT, extraPrimes, g_special_filter);

    long long grand_start = microtime();

    for (int K = K_start; K <= K_end; K++) {
        long long t0 = microtime();
        SearchAP28_kp_q(K, SHIFT, extraPrimes);
        long long elapsed = microtime() - t0;
        fprintf(stderr, "K=%d  TIME: %lld us\n", K, elapsed);
    }

    long long grand_elapsed = microtime() - grand_start;
    fprintf(stderr, "=== Total: %lld us  (%.3f s) ===\n",
            grand_elapsed, grand_elapsed / 1e6);

    return 0;
}
