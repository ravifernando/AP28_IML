/* cpuavx2.cpp --

*/

#include <x86intrin.h>
#include <cinttypes>
#include <cstdio>
#include <pthread.h>

#include "cpuconst.h"

// m256 arrays total 223296 bytes
__m256d xOKOK61[61];
__m256d xOKOK67[67];
__m256d xOKOK71[71];
__m256d xOKOK73[73];
__m256d xOKOK79[79];
__m256d xOKOK83[83];
__m256d xOKOK89[89];
__m256d xOKOK97[97];
__m256d xOKOK101[101];
__m256d xOKOK103[103];
__m256d xOKOK107[107];
__m256d xOKOK109[109];
__m256d xOKOK113[113];
__m256d xOKOK127[127];
__m256d xOKOK131[131];
__m256d xOKOK137[137];
__m256d xOKOK139[139];
__m256d xOKOK149[149];
__m256d xOKOK151[151];
__m256d xOKOK157[157];
__m256d xOKOK163[163];
__m256d xOKOK167[167];
__m256d xOKOK173[173];
__m256d xOKOK179[179];
__m256d xOKOK181[181];
__m256d xOKOK191[191];
__m256d xOKOK193[193];
__m256d xOKOK197[197];
__m256d xOKOK199[199];
__m256d xOKOK211[211];
__m256d xOKOK223[223];
__m256d xOKOK227[227];
__m256d xOKOK229[229];
__m256d xOKOK233[233];
__m256d xOKOK239[239];
__m256d xOKOK241[241];
__m256d xOKOK251[251];
__m256d xOKOK257[257];
__m256d xOKOK263[263];
__m256d xOKOK269[269];
__m256d xOKOK271[271];
__m256d xOKOK277[277];


// true if any element is not zero
#define continue_sito(_X) !_mm256_testz_si256(_mm256_castpd_si256(_X), _mm256_castpd_si256(_X))

#define MAKE_OK(_X) \
  for(j=0;j<_X;j++) \
    OK##_X[j]=1; \
  for(j=(_X-23);j<=_X;j++) \
    OK##_X[(j*(STEP%_X))%_X]=0;


#define MAKE_OKOK(_X) \
  for(j=0;j<_X;j++){ \
    sOKOK[0]=0; \
    sOKOK[1]=0; \
    sOKOK[2]=0; \
    sOKOK[3]=0; \
    for(jj=0;jj<64;jj++){ \
      if(SHIFT < maxshift) \
        sOKOK[0] |= (((uint64_t)OK##_X[(j+(jj+SHIFT)*MOD)%_X])<<jj); \
      if(SHIFT+64 < maxshift) \
        sOKOK[1] |= (((uint64_t)OK##_X[(j+(jj+SHIFT+64)*MOD)%_X])<<jj); \
      if(SHIFT+128 < maxshift) \
        sOKOK[2] |= (((uint64_t)OK##_X[(j+(jj+SHIFT+128)*MOD)%_X])<<jj); \
      if(SHIFT+192 < maxshift) \
        sOKOK[3] |= (((uint64_t)OK##_X[(j+(jj+SHIFT+192)*MOD)%_X])<<jj); \
    } \
    xOKOK##_X[j] = _mm256_castsi256_pd ( _mm256_load_si256( (__m256i*)sOKOK ) ); \
  }


void *thr_func_avx2(void *arg) {

	thread_data_t *data = (thread_data_t *)arg;
	int i43, i47, i53, i59;
	uint64_t n, n43, n47, n53, n59;
	time_t boinc_last, boinc_curr;
	double cc, dd;
	uint64_t sito[4] __attribute__ ((aligned (32)));
 	int16_t rems[16] __attribute__ ((aligned (32)));
	const __m256i ZERO256 = _mm256_setzero_si256();
	uint32_t checksum = 0;
	uint32_t apcount = 0;	

	if(data->id == 0){
		time(&boinc_last);
		cc = (double)( data->K_DONE*numn43s*3 + data->iteration*numn43s );
		dd = 1.0 / (double)( data->K_COUNT*numn43s*3 );		
	}

	ckerr(pthread_mutex_lock(&lock1));
	int start = current_n43;
	int stop = start + thread_range;
	if(stop > numn43s) stop = numn43s;
	current_n43 = stop;
	ckerr(pthread_mutex_unlock(&lock1));

	while(start < numn43s){
		for(;start<stop;++start){
			
			if(data->id == 0){
				time (&boinc_curr);
				if( ((int)boinc_curr - (int)boinc_last) > 5 ){
					double prog = (cc + (double)start ) * dd;
					Progress(prog);
					boinc_last = boinc_curr;
				}
			}
			
			n43=n43_h[start];
			for(i43=(PRIME5-26);i43>2;i43--){
				n47=n43;
				for(i47=(PRIME6-26);i47>2;i47--){
					n53=n47;
					for(i53=(PRIME7-26);i53>2;i53--){
						n59=n53;
						rems[0] = REM(n59,61,6);
						rems[1] = REM(n59,67,7);
						rems[2] = REM(n59,71,7);
						rems[3] = REM(n59,73,7);
						rems[4] = REM(n59,79,7);
						rems[5] = REM(n59,83,7);
						rems[6] = REM(n59,89,7);
						rems[7] = REM(n59,97,7);
						rems[8] = REM(n59,101,7);
						rems[9] = REM(n59,103,7);
						rems[10] = REM(n59,107,7);
						rems[11] = REM(n59,109,7);
						rems[12] = REM(n59,113,7);
						rems[13] = REM(n59,127,7);
						rems[14] = REM(n59,131,8);
						rems[15] = REM(n59,137,8);
						__m256i rvec = _mm256_load_si256( (__m256i*)rems);

						for(i59=(PRIME8-26);i59>2;i59--){
							
							if(i59 < PRIME8-26){
								_mm256_store_si256( (__m256i*)rems, rvec);
							}								

							__m256d dsito = _mm256_and_pd( xOKOK61[rems[0]], xOKOK67[rems[1]] );
							dsito = _mm256_and_pd( dsito, xOKOK71[rems[2]] );
							dsito = _mm256_and_pd( dsito, xOKOK73[rems[3]] );
							dsito = _mm256_and_pd( dsito, xOKOK79[rems[4]] );
							dsito = _mm256_and_pd( dsito, xOKOK83[rems[5]] );
							dsito = _mm256_and_pd( dsito, xOKOK89[rems[6]] );
							dsito = _mm256_and_pd( dsito, xOKOK97[rems[7]] );
							dsito = _mm256_and_pd( dsito, xOKOK101[rems[8]] );
							dsito = _mm256_and_pd( dsito, xOKOK103[rems[9]] );
							dsito = _mm256_and_pd( dsito, xOKOK107[rems[10]] );
							dsito = _mm256_and_pd( dsito, xOKOK109[rems[11]] );
							dsito = _mm256_and_pd( dsito, xOKOK113[rems[12]] );
							dsito = _mm256_and_pd( dsito, xOKOK127[rems[13]] );
							dsito = _mm256_and_pd( dsito, xOKOK131[rems[14]] );
							dsito = _mm256_and_pd( dsito, xOKOK137[rems[15]] );
							if( continue_sito(dsito) ){
								dsito = _mm256_and_pd( dsito, xOKOK139[REM(n59,139,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK149[REM(n59,149,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK151[REM(n59,151,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK157[REM(n59,157,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK163[REM(n59,163,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK167[REM(n59,167,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK173[REM(n59,173,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK179[REM(n59,179,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK181[REM(n59,181,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK191[REM(n59,191,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK193[REM(n59,193,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK197[REM(n59,197,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK199[REM(n59,199,8)] );
							if( continue_sito(dsito) ){
								dsito = _mm256_and_pd( dsito, xOKOK211[REM(n59,211,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK223[REM(n59,223,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK227[REM(n59,227,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK229[REM(n59,229,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK233[REM(n59,233,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK239[REM(n59,239,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK241[REM(n59,241,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK251[REM(n59,251,8)] );
								dsito = _mm256_and_pd( dsito, xOKOK257[REM(n59,257,9)] );
								dsito = _mm256_and_pd( dsito, xOKOK263[REM(n59,263,9)] );
								dsito = _mm256_and_pd( dsito, xOKOK269[REM(n59,269,9)] );
								dsito = _mm256_and_pd( dsito, xOKOK271[REM(n59,271,9)] );
								dsito = _mm256_and_pd( dsito, xOKOK277[REM(n59,277,9)] );
							if( continue_sito(dsito) ){
								_mm256_store_si256( (__m256i*)sito, _mm256_castpd_si256(dsito) );
								for(int ii=0;ii<2;++ii){
									while(sito[ii]){
										int setbit = 63 - __builtin_clzll(sito[ii]);
										uint64_t n = n59+( setbit + data->SHIFT + (64*ii) )*MOD;

										if(n%7)
										if(n%11)
										if(n%13)
										if(n%17)
										if(n%19)
										if(n%23)
										if(OK281[n%281])
										if(OK283[n%283])
										if(OK293[n%293])
										if(OK307[n%307])
										if(OK311[n%311])
										if(OK313[n%313])
										if(OK317[n%317])
										if(OK331[n%331])
										if(OK337[n%337])
										if(OK347[n%347])
										if(OK349[n%349])
										if(OK353[n%353])
										if(OK359[n%359])
										if(OK367[n%367])
										if(OK373[n%373])
										if(OK379[n%379])
										if(OK383[n%383])
										if(OK389[n%389])
										if(OK397[n%397])
										if(OK401[n%401])
										if(OK409[n%409])
										if(OK419[n%419])
										if(OK421[n%421])
										if(OK431[n%431])
										if(OK433[n%433])
										if(OK439[n%439])
										if(OK443[n%443])
										if(OK449[n%449])
										if(OK457[n%457])
										if(OK461[n%461])
										if(OK463[n%463])
										if(OK467[n%467])
										if(OK479[n%479])
										if(OK487[n%487])
										if(OK491[n%491])
										if(OK499[n%499])
										if(OK503[n%503])
										if(OK509[n%509])
										if(OK521[n%521])
										if(OK523[n%523])
										if(OK541[n%541]){
											int k = 0;
											uint64_t m = n + data->STEP * 5;
											while(PrimeQ(m)){
												k++;
												m += data->STEP;
											}
											
											if(k>=10){
												m = n + data->STEP * 4;
												uint64_t mstart = m;
												while(PrimeQ(m)){
													k++;
													m -= data->STEP;
													if(m > mstart) break;
												}
											}

											if(k>=10){
												uint64_t first_term = m + data->STEP;

												ReportSolution(k, data->K, first_term, checksum);
												++apcount;
											}
										}
																								
										sito[ii] ^= ((uint64_t)1) << setbit; // toggle bit off
									}
								}
							}}}

							n59 += data->S59;

							rvec = _mm256_add_epi16(rvec, svec);

							if(n59>=MOD){
								n59-=MOD;

								rvec = _mm256_sub_epi16(rvec, mvec);
								__m256i addvec = _mm256_add_epi16(rvec, numvec1);
								rvec = _mm256_blendv_epi8( rvec, addvec, _mm256_cmpgt_epi16( ZERO256, rvec ) );

							}

							__m256i subvec = _mm256_sub_epi16(rvec, numvec1);
							rvec = _mm256_blendv_epi8(rvec, subvec, _mm256_cmpgt_epi16(rvec, numvec2) );						
						   
						}     
						n53 += data->S53;
						if(n53>=MOD)n53-=MOD;
					}
					n47 += data->S47;
					if(n47>=MOD)n47-=MOD;
				}
				n43 += data->S43;
				if(n43>=MOD)n43-=MOD;
			}
		}


		ckerr(pthread_mutex_lock(&lock1));
		start = current_n43;
		stop = start + thread_range;
		if(stop > numn43s) stop = numn43s;
		current_n43 = stop;
		ckerr(pthread_mutex_unlock(&lock1));
	}
	
	
	// add this threads checksum and ap count to total
	ckerr(pthread_mutex_lock(&lock3));
	uint64_t total = cksum;
	total += checksum;
	if(total > MAXINTV){
		total -= MAXINTV;
	}
	cksum = total;
	totalaps += apcount;
	ckerr(pthread_mutex_unlock(&lock3));		

	pthread_exit(NULL);

	return NULL;
}


void Search_avx2(int K, int startSHIFT, int K_COUNT, int K_DONE, int threads)
{ 
	int i3, i5, i31, i37, i41;
	int SHIFT;
	int maxshift = startSHIFT+640;
	uint64_t STEP;
	uint64_t n0;
	uint64_t S31, S37, S41, S43, S47, S53, S59;
	int j,jj,k;
	int err;
	uint64_t sOKOK[4] __attribute__ ((aligned (32)));

	time_t start_time, finish_time;

	if(boinc_standalone()){
		time (&start_time);
	}

	STEP=K*PRIM23;
	n0=(N0*(K%17835)+((N0*17835)%MOD)*(K/17835)+N30)%MOD;

	S31=(PRES2*(K%17835)+((PRES2*17835)%MOD)*(K/17835))%MOD;
	S37=(PRES3*(K%17835)+((PRES3*17835)%MOD)*(K/17835))%MOD;
	S41=(PRES4*(K%17835)+((PRES4*17835)%MOD)*(K/17835))%MOD;
	S43=(PRES5*(K%17835)+((PRES5*17835)%MOD)*(K/17835))%MOD;
	S47=(PRES6*(K%17835)+((PRES6*17835)%MOD)*(K/17835))%MOD;
	S53=(PRES7*(K%17835)+((PRES7*17835)%MOD)*(K/17835))%MOD;
	S59=(PRES8*(K%17835)+((PRES8*17835)%MOD)*(K/17835))%MOD;

	int count=0;

	for(i31=2;i31<5;++i31)
	for(i37=2;i37<11;++i37)
	//if(i37-i31<=10&&i31-i37<=4)
	for(i41=2;i41<15;++i41)
	//if(i41-i31<=14&&i41-i37<=14&&i31-i41<=4&&i37-i41<=10)
	for(i3=0;i3<2;++i3)
	for(i5=0;i5<4;++i5){ 
		n43_h[count]=(n0+i3*S3+i5*S5+i31*S31+i37*S37+i41*S41)%MOD;  //10840 of these  12673 n53 per
		count++;
	}

	//quick loop vectors
 	int16_t sarr[16] __attribute__ ((aligned (32))) = { (int16_t)(S59%61), (int16_t)(S59%67), (int16_t)(S59%71), (int16_t)(S59%73), (int16_t)(S59%79), (int16_t)(S59%83), (int16_t)(S59%89), (int16_t)(S59%97),
														(int16_t)(S59%101), (int16_t)(S59%103), (int16_t)(S59%107), (int16_t)(S59%109), (int16_t)(S59%113), (int16_t)(S59%127), (int16_t)(S59%131), (int16_t)(S59%137) };
	svec = _mm256_load_si256( (__m256i*)sarr );	

	int16_t marr[16] __attribute__ ((aligned (32))) = { (int16_t)(MOD%61), (int16_t)(MOD%67), (int16_t)(MOD%71), (int16_t)(MOD%73), (int16_t)(MOD%79), (int16_t)(MOD%83), (int16_t)(MOD%89), (int16_t)(MOD%97),
														(int16_t)(MOD%101), (int16_t)(MOD%103), (int16_t)(MOD%107), (int16_t)(MOD%109), (int16_t)(MOD%113), (int16_t)(MOD%127), (int16_t)(MOD%131), (int16_t)(MOD%137) };
	mvec = _mm256_load_si256( (__m256i*)marr );															
	
	int16_t narr[16] __attribute__ ((aligned (32))) = { 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137 };
	
	numvec1 = _mm256_load_si256( (__m256i*)narr );

	int16_t nnarr[16] __attribute__ ((aligned (32))) = { 60, 66, 70, 72, 78, 82, 88, 96, 100, 102, 106, 108, 112, 126, 130, 136 };
	numvec2 = _mm256_load_si256( (__m256i*)nnarr );		

	// init OK arrays    
	MAKE_OK(61);
	MAKE_OK(67);
	MAKE_OK(71);
	MAKE_OK(73);
	MAKE_OK(79);
	MAKE_OK(83);
	MAKE_OK(89);
	MAKE_OK(97);
	MAKE_OK(101);
	MAKE_OK(103);
	MAKE_OK(107);
	MAKE_OK(109);
	MAKE_OK(113);
	MAKE_OK(127);
	MAKE_OK(131);
	MAKE_OK(137);
	MAKE_OK(139);
	MAKE_OK(149);
	MAKE_OK(151);
	MAKE_OK(157);
	MAKE_OK(163);
	MAKE_OK(167);
	MAKE_OK(173);
	MAKE_OK(179);
	MAKE_OK(181);
	MAKE_OK(191);
	MAKE_OK(193);
	MAKE_OK(197);
	MAKE_OK(199);
	MAKE_OK(211);
	MAKE_OK(223);
	MAKE_OK(227);
	MAKE_OK(229);
	MAKE_OK(233);
	MAKE_OK(239);
	MAKE_OK(241);
	MAKE_OK(251);
	MAKE_OK(257);
	MAKE_OK(263);
	MAKE_OK(269);
	MAKE_OK(271);
	MAKE_OK(277);
	MAKE_OK(281);
	MAKE_OK(283);
	MAKE_OK(293);
	MAKE_OK(307);
	MAKE_OK(311);
	MAKE_OK(313);
	MAKE_OK(317);
	MAKE_OK(331);
	MAKE_OK(337);
	MAKE_OK(347);
	MAKE_OK(349);
	MAKE_OK(353);
	MAKE_OK(359);
	MAKE_OK(367);
	MAKE_OK(373);
	MAKE_OK(379);
	MAKE_OK(383);
	MAKE_OK(389);
	MAKE_OK(397);
	MAKE_OK(401);
	MAKE_OK(409);
	MAKE_OK(419);
	MAKE_OK(421);
	MAKE_OK(431);
	MAKE_OK(433);
	MAKE_OK(439);
	MAKE_OK(443);
	MAKE_OK(449);
	MAKE_OK(457);
	MAKE_OK(461);
	MAKE_OK(463);
	MAKE_OK(467);
	MAKE_OK(479);
	MAKE_OK(487);
	MAKE_OK(491);
	MAKE_OK(499);
	MAKE_OK(503);
	MAKE_OK(509);
	MAKE_OK(521);
	MAKE_OK(523);
	MAKE_OK(541);
		
	int iteration = 0;

	// 10 shift
	for(SHIFT=startSHIFT; SHIFT<maxshift; SHIFT+=256){

		MAKE_OKOK(61);
		MAKE_OKOK(67);
		MAKE_OKOK(71);
		MAKE_OKOK(73);
		MAKE_OKOK(79);
		MAKE_OKOK(83);
		MAKE_OKOK(89);
		MAKE_OKOK(97);
		MAKE_OKOK(101);
		MAKE_OKOK(103);
		MAKE_OKOK(107);
		MAKE_OKOK(109);
		MAKE_OKOK(113);
		MAKE_OKOK(127);
		MAKE_OKOK(131);
		MAKE_OKOK(137);
		MAKE_OKOK(139);
		MAKE_OKOK(149);
		MAKE_OKOK(151);
		MAKE_OKOK(157);
		MAKE_OKOK(163);
		MAKE_OKOK(167);
		MAKE_OKOK(173);
		MAKE_OKOK(179);
		MAKE_OKOK(181);
		MAKE_OKOK(191);
		MAKE_OKOK(193);
		MAKE_OKOK(197);
		MAKE_OKOK(199);
		MAKE_OKOK(211);
		MAKE_OKOK(223);
		MAKE_OKOK(227);
		MAKE_OKOK(229);
		MAKE_OKOK(233);
		MAKE_OKOK(239);
		MAKE_OKOK(241);
		MAKE_OKOK(251);
		MAKE_OKOK(257);
		MAKE_OKOK(263);
		MAKE_OKOK(269);
		MAKE_OKOK(271);
		MAKE_OKOK(277);

		pthread_t thr[threads];

		// create a thread_data_t argument array
		thread_data_t thr_data[threads];

		// initialize shared data
		current_n43 = 0;

		// create threads
		for (k = 0; k < threads; ++k) {
			thr_data[k].id = k;
			thr_data[k].K = K;
			thr_data[k].K_COUNT = K_COUNT;
			thr_data[k].K_DONE = K_DONE;
			thr_data[k].SHIFT = SHIFT;
			thr_data[k].STEP = STEP;
			thr_data[k].S43 = S43;
			thr_data[k].S47 = S47;
			thr_data[k].S53 = S53;
			thr_data[k].S59 = S59;
			thr_data[k].iteration = iteration;
			err = pthread_create(&thr[k], NULL, thr_func_avx2, &thr_data[k]);
			if (err){
				fprintf(stderr, "ERROR: pthread_create, code: %d\n", err);
				exit(EXIT_FAILURE);
			}
		}

		// block until all threads complete
		for (k = 0; k < threads; ++k) {
			err = pthread_join(thr[k], NULL);
			if (err){
				fprintf(stderr, "ERROR: pthread_join, code: %d\n", err);
				exit(EXIT_FAILURE);
			}
		}

		++iteration;
		
	}

	if(boinc_standalone()){
		time(&finish_time);
		printf("Computation of K: %d complete in %d seconds\n", K, (int)finish_time - (int)start_time);
	}



}
