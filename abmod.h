#ifndef ABMOD_H
#define ABMOD_H

// Overflow-safe modular multiplication: computes (a * b) % m
// Uses Russian Peasant Multiplication to avoid 64-bit overflow.
// Requires: a, b, m > 0; a < m (or a will be reduced first).
static long long abmodm(long long a, long long b, long long m) {
    if (m == 0) return 0;

    long long result = 0;
    a %= m;

    while (b > 0) {
        if (b & 1) {
            // Safe addition: (result + a) % m without overflow
            if (result >= m - a) {
                result -= (m - a);
            } else {
                result += a;
            }
        }

        // Double a for next bit
        if (a >= m - a) {
            a -= (m - a);
        } else {
            a <<= 1;
        }

        b >>= 1;
    }

    return result;
}

#endif
