typedef unsigned long long uint64;

#define SIZ(x) ((x)->_mp_size)
#define PTR(x) ((x)->_mp_d)
#define ALLOC(x) ((x)->_mp_alloc)

int PrimeQ(long long value)
{
	int out;
       mpz_t  n;
       mpz_init2(n,64);
       PTR(n)[0] = value;
       SIZ(n) =1;

       out=mpz_probab_prime_p (n,1);
       mpz_clear(n);
       return out;

}

