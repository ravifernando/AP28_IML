#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

// A C++ program to demonstrate
// working of Chinese remainder
// Theorem
#include <bits/stdc++.h>

// Returns modulo inverse of a
// with respect to m using
// extended Euclid Algorithm.
// Refer below post for details:
// https://www.geeksforgeeks.org/
// multiplicative-inverse-under-modulo-m/
long long inv(long long a, long long m)
{
  long long m0 = m, t, q;
  long long x0 = 0, x1 = 1;

  if (m == 1)
    return 0;

  // Apply extended Euclid Algorithm
  while (a > 1) {
    // q is quotient
    q = a / m;

    t = m;

    // m is remainder now, process same as
    // euclid's algo
    m = a % m, a = t;

    t = x0;

    x0 = x1 - q * x0;

    x1 = t;
  }

  // Make x1 positive
  if (x1 < 0)
    x1 += m0;

  return x1;
}

// k is size of num[] and rem[]. Returns the smallest
// number x such that:
// x % num[0] = rem[0],
// x % num[1] = rem[1],
// ..................
// x % num[k-2] = rem[k-1]
// Assumption: Numbers in num[] are pairwise coprime
// (gcd for every pair is 1)
long long findMinX(const std::vector<long long> &num, const std::vector<long long> &rem)
{
  // Compute product of all numbers
  long long prod = 1;
  for (long long i = 0; i < num.size(); i++)
    prod *= num.at(i);

  // Initialize result
  long long result = 0;

  // Apply above formula
  for (long long i = 0; i < num.size(); i++) {
    long long pp = prod / num.at(i);
    result += rem.at(i) * inv(pp, num.at(i)) * pp;
  }

  const long long out = result % prod;
  // Checking for accuracy
  for (long long i = 0; i < num.size(); i++) {
    if (out % num.at(i) != rem.at(i) % num.at(i)) {
      std::cout << "ERROR: Result did not satisfy the system of congruences (probably a long long overflow issue)." << std::endl;
      abort();
    }
  }
  return out;
}

std::vector<bool> sieveOfEratosthenes(const long long n) {
  if (n <= 1) {
    std::cout << "ERROR: Invalid input; if you are using constWriter, then the sievePrime parameter is causing this issue." << std::endl;
    abort();
  }
  std::vector<bool> primes(n, true);
  primes.at(0) = false;
  primes.at(1) = false;

  for (long long i = 2; i <= std::floor(std::sqrt(n)); i++) if (primes.at(i)) for(long long j = i*i; j < n; j += i) primes.at(j) = false;

  return primes;
}

long long mult(const long long a, const long long b) {
  if (a < 0 || b < 0) {
    std::cout << "ERROR: Invalid inputs for the mult function; this function only takes nonnegative integers." << std::endl;
  }
  long long c = a * b;
  if (a != 0 && c / a != b) {
    std::cout << "ERROR: Overflow in multiplication." << std::endl;
    abort();
  }
  return c;
}

void constWriter(const std::string& filename,
  std::vector<long long> commonDifferenceDivisors,
  std::vector<long long> primesForCandidates,
  const long long specialPrime,
  const long long multiply,
  const long long bitmaskPrime,
  const long long sievePrime) {

  // Checks if specialPrime and multiply parameters make sense
  if (specialPrime > 0 && multiply == 0) {
    std::cout << "ERROR: specialPrime is nonzero, but multiply is 0." << std::endl;
    abort();
  } else if (specialPrime < 0) {
    std::cout << "ERROR: specialPrime is not negative. This input should be set to 0 if there is no special prime." << std::endl;
    abort();
  } else if (specialPrime == 0 && multiply != 0) {
    std::cout << "ERROR: specialPrime is 0, but multiply is nonzero. The multiply input should be set to 0" << std::endl;
  }

  // Checks if bitmaskPrime and sievePrime parameters make sense
  if (bitmaskPrime > sievePrime) {
    std::cout << "ERROR: bitmaskPrime greater than sievePrime." << std::endl;
    abort();
  }
  if (bitmaskPrime <= 1 || sievePrime <= 1) {
    std::cout << "ERROR: bitmaskPrime or sievePrime is less than or equal to 1." << std::endl;
    abort();
  }

  // Sorts both vectors first for labeling purposes
  std::sort(commonDifferenceDivisors.begin(), commonDifferenceDivisors.end());
  std::sort(primesForCandidates.begin(), primesForCandidates.end());

  // Use the Sieve of Eratosthenes to get all primes from 2 to sievePrime
  std::vector<bool> primes = sieveOfEratosthenes(sievePrime + 1);

  // Opens the file for writing
  std::ofstream writeToFile;
  writeToFile.open(filename);

  // Calculates the common difference and writes to file
  // The name of this variable is PRIM + the largest prime factor of MOD (last element of modDivisors)
  long long commonDifference = 1;
  for (const long long p : commonDifferenceDivisors) commonDifference = mult(commonDifference, p);
  writeToFile << "#define PRIM" << commonDifferenceDivisors.at(commonDifferenceDivisors.size() - 1) << " " << commonDifference << "LL\n";

  // PRIMEConstants = primesForCandidates \ commonDifferenceDivisors; this set subtraction determines the values of the PRIME constants.
  std::vector<long long> PRIMEConstants;
  std::set_difference(
      primesForCandidates.begin(), primesForCandidates.end(),
      commonDifferenceDivisors.begin(), commonDifferenceDivisors.end(),
      std::back_inserter(PRIMEConstants)
  );

  // Writes the PRIME constants to file
  for (long long i = 0; i < PRIMEConstants.size(); i++) writeToFile << "#define PRIME" << (i + 1) << " " << PRIMEConstants.at(i) << "\n";

  // Calculates MOD and writes to file
  long long MOD = 1;
  for (const long long p : primesForCandidates) MOD = mult(MOD, p);
  writeToFile << "#define MOD" << " " << MOD << "LL\n";

  // Calculates N0, N30 and writes to file
  if (specialPrime == 0) writeToFile << "#define N0 " << commonDifference << "LL\n";
  else {
    std::vector<long long> congruences;
    for (long long i = 0; i < primesForCandidates.size(); i++) congruences.push_back(commonDifference % primesForCandidates.at(i));
    auto iter = std::find(primesForCandidates.begin(), primesForCandidates.end(), specialPrime);
    if (iter != primesForCandidates.end()) congruences.at(iter - primesForCandidates.begin()) = mult(multiply, commonDifference % specialPrime) % specialPrime;
    else {
      std::cout << "ERROR: Invalid special prime." << std::endl;
      abort();
    }
    long long N0 = findMinX(primesForCandidates, congruences);
    writeToFile << "#define N0 " << N0 << "LL\n";
  }
  std::vector<long long> congruences(primesForCandidates.size(), 0);
  congruences.at(0) = 1;
  congruences.at(1) = 1;
  congruences.at(2) = 1;
  long long CRT = findMinX(primesForCandidates, congruences);
  writeToFile << "#define N30 " << CRT << "LL\n";
  congruences.at(0) = 0;
  congruences.at(1) = 0;
  congruences.at(2) = 0;

  // Calculates SP where P are primes > 2 that divides the common difference and are used for sieving and writes to file
  std::vector<long long> SPprimes;
  std::set_intersection(
    primesForCandidates.begin(), primesForCandidates.end(),
    commonDifferenceDivisors.begin(), commonDifferenceDivisors.end(),
    std::back_inserter(SPprimes)
  );
  for (long long SPprime : SPprimes) {
    if (SPprime == 2) continue;
    auto iter = std::find(primesForCandidates.begin(), primesForCandidates.end(), SPprime);
    congruences.at(iter - primesForCandidates.begin()) = 1;
    CRT = findMinX(primesForCandidates, congruences);
    writeToFile << "#define S" << SPprime << " " << CRT << "LL\n";
    congruences.at(iter - primesForCandidates.begin()) = 0;
  }

  // Calculates PRESP where P are primes in the PRIMEConstants vector
  long long index = 2;
  for (long long PRIMEConstant : PRIMEConstants) {
    if (PRIMEConstant == specialPrime) continue;
    auto iter = std::find(primesForCandidates.begin(), primesForCandidates.end(), PRIMEConstant);
    congruences.at(iter - primesForCandidates.begin()) = commonDifference % PRIMEConstant;
    CRT = findMinX(primesForCandidates, congruences);
    writeToFile << "#define PRES" << index << " " << CRT << "LL\n";
    congruences.at(iter - primesForCandidates.begin()) = 0;
    index++;
  }

  // Writes OK and OKOK arrays to file
  for (long long p = primesForCandidates.at(primesForCandidates.size() - 1) + 1; p < primes.size(); p++) {
    if (primes.at(p)) {
      writeToFile << "char OK" << p << "[" << p << "];\n";
    }
  }
  for (long long p = primesForCandidates.at(primesForCandidates.size() - 1) + 1; p <= bitmaskPrime; p++) {
    if (primes.at(p)) {
      writeToFile << "long long OKOK" << p << "[" << p << "];\n";
    }
  }
  // Closes file after all writing needed is finished
  writeToFile.close();
}

int main(int argc, char const *argv[]) {
  const std::vector<long long> commonDifferenceDivisors = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
  const std::vector<long long> primesForCandidates = { 2, 3, 5, 31, 37, 41, 43, 47, 53, 59, 61 };
  constWriter("WRITE_CONST.H", commonDifferenceDivisors, primesForCandidates, 31, 3, 331, 541);
  return 0;
}