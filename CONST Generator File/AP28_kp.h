#include <stdio.h>

void SearchAP28_kp(int K, struct Constants* kp, int SHIFT)
{

long long n, n43, n47, n53, n59, n61; // Added n61 due to there being more inner loops (more additions)
int iPRIME4, iPRIME5, iPRIME6, iPRIME7, iPRIME8;
int i3, i5, iPRIME1, iPRIME2, iPRIME3;

int p = kp->p;
int q = kp->q;
int PRIME1 = kp->PRIME1;
int PRIME2 = kp->PRIME2;
int PRIME3 = kp->PRIME3;
int PRIME4 = kp->PRIME4;
int PRIME5 = kp->PRIME5;
int PRIME6 = kp->PRIME6;
int PRIME7 = kp->PRIME7;
int PRIME8 = kp->PRIME8;

int i, j, jj;

long long STEP;
long long STEP5;
long long STEP4;
long long n0;
long long sito;

long long COMMONDIFF = kp->COMMONDIFF;
long long MOD = kp->MOD;
long long N0 = kp->N0;
long long N30 = kp->N30;
long long S3 = kp->S3;
long long S5 = kp->S5;
long long PRES2 = kp->PRES2;
long long PRES3 = kp->PRES3;
long long PRES4 = kp->PRES4;
long long PRES5 = kp->PRES5;
long long PRES6 = kp->PRES6;
long long PRES7 = kp->PRES7;
long long PRES8 = kp->PRES8;
long long PRES9 = kp->PRES9;

// printf("p: %d\n", p);
// printf("q: %d\n", q);
// printf("COMMONDIFF: %lld\n", COMMONDIFF);
// printf("PRIME1: %d\n", PRIME1);
// printf("PRIME2: %d\n", PRIME2);
// printf("PRIME3: %d\n", PRIME3);
// printf("PRIME4: %d\n", PRIME4);
// printf("PRIME5: %d\n", PRIME5);
// printf("PRIME6: %d\n", PRIME6);
// printf("PRIME7: %d\n", PRIME7);
// printf("PRIME8: %d\n", PRIME8);
// printf("MOD: %lld\n", MOD);
// printf("N0: %lld\n", N0);
// printf("N30: %lld\n", N30);
// printf("S3: %lld\n", S3);
// printf("S5: %lld\n", S5);
// printf("PRES2: %lld\n", PRES2);
// printf("PRES3: %lld\n", PRES3);
// printf("PRES4: %lld\n", PRES4);
// printf("PRES5: %lld\n", PRES5);
// printf("PRES6: %lld\n", PRES6);
// printf("PRES7: %lld\n", PRES7);
// printf("PRES8: %lld\n", PRES8);
// printf("PRES9: %lld\n", PRES9);

long long SPRIME1, SPRIME2, SPRIME3, SPRIME4, SPRIME5, SPRIME6, SPRIME7, SPRIME8; // Added S61 (now SPRIME8)

int s67, s71, s73, s79, s83, s89, s97, s101; // Removed s61; added s101 if needed
int m67, m71, m73, m79, m83, m89, m97, m101; // Removed m61; added m101 if needed

// skip k's that are divisible by PRIME1, ..., or PRIME8 for the sake of simplicity
if(
        K%PRIME1&&
        K%PRIME2&&
        K%PRIME3&&
        K%PRIME4&&
        K%PRIME5&&
        K%PRIME6&&
        K%PRIME7&&
        K%PRIME8
    )
{

char OK67[67];
char OK71[71];
char OK73[73];
char OK79[79];
char OK83[83];
char OK89[89];
char OK97[97];
char OK101[101];
char OK103[103];
char OK107[107];
char OK109[109];
char OK113[113];
char OK127[127];
char OK131[131];
char OK137[137];
char OK139[139];
char OK149[149];
char OK151[151];
char OK157[157];
char OK163[163];
char OK167[167];
char OK173[173];
char OK179[179];
char OK181[181];
char OK191[191];
char OK193[193];
char OK197[197];
char OK199[199];
char OK211[211];
char OK223[223];
char OK227[227];
char OK229[229];
char OK233[233];
char OK239[239];
char OK241[241];
char OK251[251];
char OK257[257];
char OK263[263];
char OK269[269];
char OK271[271];
char OK277[277];
char OK281[281];
char OK283[283];
char OK293[293];
char OK307[307];
char OK311[311];
char OK313[313];
char OK317[317];
char OK331[331];
char OK337[337];
char OK347[347];
char OK349[349];
char OK353[353];
char OK359[359];
char OK367[367];
char OK373[373];
char OK379[379];
char OK383[383];
char OK389[389];
char OK397[397];
char OK401[401];
char OK409[409];
char OK419[419];
char OK421[421];
char OK431[431];
char OK433[433];
char OK439[439];
char OK443[443];
char OK449[449];
char OK457[457];
char OK461[461];
char OK463[463];
char OK467[467];
char OK479[479];
char OK487[487];
char OK491[491];
char OK499[499];
char OK503[503];
char OK509[509];
char OK521[521];
char OK523[523];
char OK541[541];
long long OKOK67[67];
long long OKOK71[71];
long long OKOK73[73];
long long OKOK79[79];
long long OKOK83[83];
long long OKOK89[89];
long long OKOK97[97];
long long OKOK101[101];
long long OKOK103[103];
long long OKOK107[107];
long long OKOK109[109];
long long OKOK113[113];
long long OKOK127[127];
long long OKOK131[131];
long long OKOK137[137];
long long OKOK139[139];
long long OKOK149[149];
long long OKOK151[151];
long long OKOK157[157];
long long OKOK163[163];
long long OKOK167[167];
long long OKOK173[173];
long long OKOK179[179];
long long OKOK181[181];
long long OKOK191[191];
long long OKOK193[193];
long long OKOK197[197];
long long OKOK199[199];
long long OKOK211[211];
long long OKOK223[223];
long long OKOK227[227];
long long OKOK229[229];
long long OKOK233[233];
long long OKOK239[239];
long long OKOK241[241];
long long OKOK251[251];
long long OKOK257[257];
long long OKOK263[263];
long long OKOK269[269];
long long OKOK271[271];
long long OKOK277[277];
long long OKOK281[281];
long long OKOK283[283];
long long OKOK293[293];
long long OKOK307[307];
long long OKOK311[311];
long long OKOK313[313];
long long OKOK317[317];
long long OKOK331[331];

STEP=K*COMMONDIFF; // Changed to COMMONDIFF, since AP28_kp works with various common differences.
STEP4=STEP*4; // The program starts at sieving n + 4 * STEP and then sieves n + 3 * STEP, n + 2 * STEP, n + STEP, n, n - STEP, ...; I made no edits as this seems to be preferential.
STEP5=STEP*5; // The program starts at sieving n + 5 * STEP and then sieves n + 6 * STEP, n + 7 * STEP, n + 8 * STEP, ...; I made no edits as this seems to be preferential.
// Since 17835 * MOD ~ 2^62 in the original code, I am maintaining this equation; it seems to prevent integer overflow.
long long num = 4611686018427387904 / MOD; // Calculating the "magic number" (the big number is 2^62)
n0=(N0*(K%num)+((N0*num)%MOD)*(K/num)+N30)%MOD;
SPRIME1=(PRES2*(K%num)+((PRES2*num)%MOD)*(K/num))%MOD;
SPRIME2=(PRES3*(K%num)+((PRES3*num)%MOD)*(K/num))%MOD;
SPRIME3=(PRES4*(K%num)+((PRES4*num)%MOD)*(K/num))%MOD;
SPRIME4=(PRES5*(K%num)+((PRES5*num)%MOD)*(K/num))%MOD;
SPRIME5=(PRES6*(K%num)+((PRES6*num)%MOD)*(K/num))%MOD;
SPRIME6=(PRES7*(K%num)+((PRES7*num)%MOD)*(K/num))%MOD;
SPRIME7=(PRES8*(K%num)+((PRES8*num)%MOD)*(K/num))%MOD;
SPRIME8=(PRES9*(K%num)+((PRES9*num)%MOD)*(K/num))%MOD; // Calculate S61 (now SPRIME8)

s67=SPRIME8%67; // Removed s61=S61%61;
s71=SPRIME8%71;
s73=SPRIME8%73;
s79=SPRIME8%79;
s83=SPRIME8%83;
s89=SPRIME8%89;
s97=SPRIME8%97;
// s101=SPRIME8%101; // if needed, uncomment

m67=MOD%67; // Removed m61=MOD%61;
m71=MOD%71;
m73=MOD%73;
m79=MOD%79;
m83=MOD%83;
m89=MOD%89;
m97=MOD%97;
// m101=MOD%101; // if needed, uncomment

#include "MAKES_kp.H"

// Since we want a tighter sieve, I made all bounds be from 0 to (p-28) for the outer loops.
for(iPRIME1=0;iPRIME1<(PRIME1-28);++iPRIME1)
for(iPRIME2=0;iPRIME2<(PRIME2-28);++iPRIME2)
for(iPRIME3=0;iPRIME3<(PRIME3-28);++iPRIME3)
for(i3=0;i3<2;++i3)
for(i5=0;i5<4;++i5)
{




n43=(n0+i3*S3+i5*S5+iPRIME1*SPRIME1+iPRIME2*SPRIME2+iPRIME3*SPRIME3)%MOD;
{
// Since we want a tighter sieve, I made all bounds be from (p-28) to 0 for the inner loops.
for(iPRIME4=(PRIME4-28);iPRIME4>0;iPRIME4--)
{

n47=n43;
for(iPRIME5=(PRIME5-28);iPRIME5>0;iPRIME5--)
{

n53=n47;
for(iPRIME6=(PRIME6-28);iPRIME6>0;iPRIME6--)
{

n59=n53;
for(iPRIME7=(PRIME7-28);iPRIME7>0;iPRIME7--)
{
int r67, r71, r73, r79, r83, r89, r97, r101; // Removed r61; added r101 if needed

n61=n59;
r67=n61%67; // Removed r61=n61%61;
r71=n61%71;
r73=n61%73;
r79=n61%79;
r83=n61%83;
r89=n61%89;
r97=n61%97;
// r101=n61%101; // if needed, uncomment
for(iPRIME8=(PRIME8-28);iPRIME8>0;iPRIME8--)
{

#include "SITO_kp.H"
{
int b;

for(b=0;b<64;b++)
if((sito>>b)&1)

{

n=n61+(b+SHIFT)*MOD;

#include "IF.H"
if(n%7) // Sieving for primes from 7 to 23 and p
if(n%11)
if(n%13)
if(n%17)
if(n%19)
if(n%23)
if(n%p) // Added this if statement to reflect sieving mod p
if(q == 0 || n % q) // Added this if statement to reflect sieving mod q
{
long long m;
int k;

k=0; m=n+STEP5;
while(PrimeQ(m)){
k++;
m+=STEP;
};


if(k>=10){
m=n+STEP4;
while(m>0&&PrimeQ(m)){
k++;
m-=STEP;
};
};



if(k>=10)
{
ReportSolution(k,K,m+STEP);
};
};

}

}
if(iPRIME8>1){
n61+=SPRIME8;
r67+=s67; // Removed r61+=s61;
r71+=s71;
r73+=s73;
r79+=s79;
r83+=s83;
r89+=s89;
r97+=s97;
// r101+=s101; // if needed, uncomment
if(n61>=MOD){
n61-=MOD;
r67-=m67; // Removed r61-=m61;
r71-=m71;
r73-=m73;
r79-=m79;
r83-=m83;
r89-=m89;
r97-=m97;
// r101+=m101; // if needed, uncomment
if(r67<0)r67+=67; // Removed if(r61<0)r61+=61;
if(r71<0)r71+=71;
if(r73<0)r73+=73;
if(r79<0)r79+=79;
if(r83<0)r83+=83;
if(r89<0)r89+=89;
if(r97<0)r97+=97;
// if(r101<0)r101+=101; // if needed, uncomment
};
if(r67>=67)r67-=67; // Removed if(r61>=61)r61-=61;
if(r71>=71)r71-=71;
if(r73>=73)r73-=73;
if(r79>=79)r79-=79;
if(r83>=83)r83-=83;
if(r89>=89)r89-=89;
if(r97>=97)r97-=97;
// if(r101>=101)r101-=101; // if needed, uncomment
}
}

n59+=SPRIME7; // Added this addition operation for n59
if(n59>=MOD)n59-=MOD;
}

n53+=SPRIME6;
if(n53>=MOD)n53-=MOD;
}

n47+=SPRIME5;
if(n47>=MOD)n47-=MOD;
}

n43+=SPRIME4;
if(n43>=MOD)n43-=MOD;
}
};


}
}
}



