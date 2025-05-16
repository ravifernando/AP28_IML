#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//
// Computes (2^exponent) % m efficiently using modular exponentiation.
// This avoids overflow by squaring the base and reducing modulo m at every step.
// It's used to compute powers of 2 mod m in a safe and fast way.
//
uint64_t pow2_mod(uint64_t exponent, uint64_t m) {
    if (m == 1) return 0;
    uint64_t result = 1;
    uint64_t base = 2;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        exponent /= 2;
    }
    return result;
}

//
// Computes (a * b) % m using bit decomposition of b:
// b is written as a sum of powers of 2 (e.g., 273 = 2^8 + 2^4 + 2^0)
// For each bit k in b (starting from highest), it adds (a * 2^k) % m to the result.
// This ensures modular safety and avoids overflow.
//
// Early returns 0 if m is 0 or less than 2^63, based on problem constraints.
//
uint64_t abmodm(uint64_t a, uint64_t b, uint64_t m) {
    //for bounds
    if (m == 0 || m > (1ULL << 63)) {
        return 0;
    }

    uint64_t result = 0;

    
    for (int k = 0; k < 64; k++) {
        if ((b >> k) & 1) { // If k-th bit is set in b
            // Compute (a * 2^k) % m
            uint64_t pow2k_mod = pow2_mod(k, m);
            uint64_t term = (a * pow2k_mod) % m;

            // Add to running total mod m
            result = (result + term) % m;
        }
    }

    return result;
}

int main() {
    struct TestCase {
        uint64_t a;
        uint64_t b;
        uint64_t m;
        uint64_t expected;
    } test_cases[] = {
        {7, 273, 1000, 911}, // 7*273 = 1911 → 1911 % 1000 = 911
        {0, 5, 10, 0},       // 0*5 = 0 → 0 % 10 = 0
        {3, 5, 15, 0},       // 3*5 = 15 → 15 % 15 = 0
        {2, 3, 5, 1},        // 2*3 = 6 → 6 % 5 = 1
        {1, 0, 7, 0},        // 1*0 = 0 → 0 % 7 = 0
        {123, 456, 1, 0},    // Any number mod 1 is 0
        {123456789ULL, 987654321ULL, 1000000007ULL, 259106859},
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int passed = 0;

    for (int i = 0; i < num_tests; ++i) {
        struct TestCase tc = test_cases[i];
        uint64_t result = abmodm(tc.a, tc.b, tc.m);
        if (result == tc.expected) {
            passed++;
            printf("Test %d passed.\n", i + 1);
        } else {
            printf("Test %d failed: a=%" PRIu64 ", b=%" PRIu64 ", m=%" PRIu64 ", expected=%" PRIu64 ", got=%" PRIu64 "\n",
                   i + 1, tc.a, tc.b, tc.m, tc.expected, result);
        }
    }

    printf("%d/%d tests passed.\n", passed, num_tests);
    return passed == num_tests ? 0 : 1;
}