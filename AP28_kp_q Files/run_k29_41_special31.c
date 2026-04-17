#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "PrimeQ64.h"

long long microtime(void)
{
        struct timeval start;
        long long result;

        gettimeofday( &start, NULL );
        result = start.tv_sec * 1000000LL + start.tv_usec;
        return result;
}

long long mytime, totaltime;

FILE *out;

void ReportSolution(int AP_Length,int difference,long long First_Term){
  if(AP_Length>=14){
    fprintf(out,"%d %d %lld\n",AP_Length,difference,First_Term);
    fflush(out);
    printf("%d %d %lld\n",AP_Length,difference,First_Term);
  }
};



#include "CONST_kp_q.H"
#include "AP28_kp_q.h"



int main(int argc, char *argv[])
{
    out = fopen("result_k29_41_special31.txt", "w");

    mytime = microtime();

    SearchAP28_kp_q(1, 0, 29 * 41);

    totaltime=microtime()-mytime;
    fprintf(out,"TIME: %lld microseconds\n",totaltime);
    printf("TIME: %lld microseconds\n",totaltime);

    fclose(out);

  return 0;
}
