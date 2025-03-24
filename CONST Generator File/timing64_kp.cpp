#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <vector>
#include <algorithm>

#include "PrimeQ64.h"
//#include "PrimeQ32.h" 
// choose 64 or 32 bit version above

long long microtime(void)
{
        struct timeval start;
        long long result;

        gettimeofday( &start, NULL );
        result = start.tv_sec * 1000000LL + start.tv_usec;
        return result;
}

long long mytime, totaltime;


// below you define what action to take when a solution is found
void ReportSolution(int AP_Length,int difference,long long First_Term){
  if(AP_Length>=14){
    //FILE *out;
    //out = fopen("SOL98.TXT", "a");
    //fprintf(out,"%d %d %lld\n",AP_Length,difference,First_Term);
    //fclose(out);
    printf("%d %d %lld\n",AP_Length,difference,First_Term);
  }
};



#include "AP28_kp.h"
#include "CONST_Generator.cpp"


void setUpSearch(long long divisor) {

  // Get vectors of prime numbers needed to write CONST_kp.H file
  std::vector<long long> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };
  std::vector<long long> commonDifferenceDivisors = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };

  // If divisor = 0, then we do not need prime 61 (we are doing AP28 Search with 29 special in this case); otherwise, we do.
  // Moreover, we add divisor to commonDifferenceDivisors if divisor != 0 to have the common difference be divisible by divisor.
  if (divisor != 0) {
    primes.push_back(61);
    commonDifferenceDivisors.push_back(divisor);
  }

  // Primes for sieving to generate candidates are obtained by { 2, 3, 5 } union (primes \ commonDifferenceDivisors)
  std::vector<long long> primesForCandidates = { 2, 3, 5 };
  std::set_difference(
      primes.begin(), primes.end(),
      commonDifferenceDivisors.begin(), commonDifferenceDivisors.end(),
      std::back_inserter(primesForCandidates)
  );

  // Set up inputs for constWriter (I assigned each input to variables for the sake of clarity)
  constexpr long long specialPrime = 0;
  constexpr long long multiply = 0;
  constexpr long long bitmaskPrime = 331;
  constexpr long long sievePrime = 541;

  // Write CONST_kp.H
  constWriter("CONST Generator File/CONST_kp.H", commonDifferenceDivisors, primesForCandidates, specialPrime, multiply, bitmaskPrime, sievePrime);
}


int main(int argc, char *argv[])
{
    // Set up AP28 Search
    long long divisor = 37; // The common difference is a multiple of 23# * divisor. If we want 23# only, divisor = 0.
    setUpSearch(divisor); // setUpSearch function is defined directly above.

    mytime = microtime();

    SearchAP28_kp(1, divisor, 0);

    totaltime=microtime()-mytime;
    printf("TIME: %lld microseconds\n",totaltime);

  return 0;
}

