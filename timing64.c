#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>


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



#include "AP26.h"



int main(int argc, char *argv[])
{ 
    mytime = microtime();

    SearchAP26(985151,0);

    totaltime=microtime()-mytime;
    printf("TIME: %lld microseconds\n",totaltime);

  return 0;
}


