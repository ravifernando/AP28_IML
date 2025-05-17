#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>


/*
Inputs: a, b, m. in the expression ab mod m
Output: ab mod m (in an efficient way)

First needs to check bounds to prevent overflow or other unwanted action

Then has result variable that continues to update every iteration

Loop 64 times, 1 for each bit in a uint64_t variable, and check if k'th bit is equal to 1 (i.e. k'th bit & 1)

    If it is, for that small component, compute a(2^k'th bit) mod m

    And finally, add this temporary result to result and mod m again

Finally, return result

*/
uint64_t abmodm(uint64_t a, uint64_t b, uint64_t m) {
    

    uint64_t max_bound = 1ULL << 63;
    //early return if either mod 0 or overflow
    if (m == 0 || m > max_bound) {
        return 0;
    }

    uint64_t result = 0;

    
    for (int k = 0; k < 64; k++) {

        int cur_bit = b >> k;

        if (cur_bit & 1) {  //if the current bit is 1, then it is part of the binary expansian

            uint64_t temp_result = pow(2, k) * a;
            temp_result %= m;

            result = (result + temp_result) % m;
        }
    }

    return result;
}
