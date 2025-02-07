/*
 AP26 implementation by Jarosław Wróblewski
 Source:  http://www.math.uni.wroc.pl/~jwr/AP26/AP26.ZIP
 Plus some comments and superficial changes by Ravi Fernando
 */

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



// below you define what action to take when a solution is found
void ReportSolution(int AP_Length,int difference,long long First_Term){
  if(AP_Length>=10){
    FILE *out;
    out = fopen("SOL-AP26.TXT", "a");
    fprintf(out,"%d %d %lld\n",AP_Length,difference,First_Term);
    fclose(out);
  }
};



#include "AP26.h"



int main(int argc, char *argv[])
{ 
	  	FILE *in, *out;
	  	int K, KMIN, KMAX, shift;

if(argc!=4){
	in = fopen("AP26-ini.txt", "r");
	if(NULL == in){
		printf("Cannot read AP26-ini.txt !!!\n");
		exit(0);
	} else {
		fscanf(in,"%d %d %d\n",&KMIN,&KMAX,&shift);
		fclose(in);
	}
}else{
sscanf(argv[1],"%d",&KMIN);
sscanf(argv[2],"%d",&KMAX);
sscanf(argv[3],"%d",&shift);
}

	out = fopen("AP26-ini.txt", "w");
	if(NULL == out){
		printf("Cannot write AP26-ini.txt !!!\n");
		exit(0);
	} else {
		fprintf(out,"%d %d %d\n",KMIN,KMAX,shift);
		fclose(out);
	}

for(K=KMIN;K<=KMAX;++K){
    SearchAP26(K,shift);
    
	out = fopen("AP26-ini.txt", "w");
	if(NULL == out){
		printf("Cannot write AP26-ini.txt !!!\n");
		exit(0);
	} else {
		fprintf(out,"%d %d %d\n",K+1,KMAX,shift);
		fclose(out);
	}
}

  return 0;
}


