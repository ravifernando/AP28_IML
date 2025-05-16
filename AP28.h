#include "CONST.H"
#include <stdint.h>

void SearchAP28(int K, int SHIFT)
{ 
long long n, n43, n47, n53, n59;
int i43, i47, i53, i59;
int i3, i5, i31, i37, i41;

int i, j, jj;

long long STEP;
long long STEP5;
long long STEP4;
long long n0;
long long sito;



long long S31, S37, S41, S43, S47, S53, S59;

int s61, s67, s71, s73, s79, s83, s89, s97;
int m61, m67, m71, m73, m79, m83, m89, m97;

// skip k's that are divisible by 29, 31, ..., or 59 for the sake of simplicity
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

STEP=K*PRIM23;
STEP4=STEP*4;
STEP5=STEP*5;
n0=(N0*(K%17835)+((N0*17835)%MOD)*(K/17835)+N30)%MOD; // = N0 * K + N30 mod MOD
// congruent to 1 mod 2*3*5; 3*D mod 29; D mod 31*...*59 (see definition on page 3)
// these calculations are broken up to avoid long long overflow
// (17835 * MOD ~ 2^62)
S31=(PRES2*(K%17835)+((PRES2*17835)%MOD)*(K/17835))%MOD; // = PRES2 * K mod MOD
S37=(PRES3*(K%17835)+((PRES3*17835)%MOD)*(K/17835))%MOD; // etc.
S41=(PRES4*(K%17835)+((PRES4*17835)%MOD)*(K/17835))%MOD;
S43=(PRES5*(K%17835)+((PRES5*17835)%MOD)*(K/17835))%MOD;
S47=(PRES6*(K%17835)+((PRES6*17835)%MOD)*(K/17835))%MOD;
S53=(PRES7*(K%17835)+((PRES7*17835)%MOD)*(K/17835))%MOD;
S59=(PRES8*(K%17835)+((PRES8*17835)%MOD)*(K/17835))%MOD;
                        
s61=S59%61;
s67=S59%67;
s71=S59%71;
s73=S59%73;
s79=S59%79;
s83=S59%83;
s89=S59%89;
s97=S59%97;

m61=MOD%61;
m67=MOD%67;
m71=MOD%71;
m73=MOD%73;
m79=MOD%79;
m83=MOD%83;
m89=MOD%89;
m97=MOD%97;
        
#include "MAKES.H" // build OK and OKOK arrays; see page 8


for(i31=2;i31<5;++i31)
for(i37=2;i37<11;++i37)
// if(i37-i31<=10&&i31-i37<=4) // to make sure the good intervals intersect in an AP of length at least 26
					    // (more generally, we need i_q - i_p <= q - 27)
for(i41=2;i41<15;++i41)
// if(i41-i31<=14&&i41-i37<=14&&i31-i41<=4&&i37-i41<=10) // see above
for(i3=0;i3<2;++i3)
for(i5=0;i5<4;++i5)
{ 




n43=(n0+i3*S3+i5*S5+i31*S31+i37*S37+i41*S41+2*S43+2*S47+2*S53+2*S59)%MOD;
{

for(i43=(PRIME5-26);i43>2;i43--)
{

n47=n43;
for(i47=(PRIME6-26);i47>2;i47--)
{

n53=n47;
for(i53=(PRIME7-26);i53>2;i53--)
{
int r61, r67, r71, r73, r79, r83, r89, r97;

n59=n53;
r61=n59%61;
r67=n59%67;
r71=n59%71;
r73=n59%73;
r79=n59%79;
r83=n59%83;
r89=n59%89;
r97=n59%97;
for(i59=(PRIME8-26);i59>2;i59--)
{

#include "SITO.H" // bit mask sieving for primes from 61 to 331
{
int b;

for(b=0;b<64;b++)
if((sito>>b)&1)

{

n=n59+(b+SHIFT)*MOD;

#include "IF.H" // sieving for primes from 337 to 541
if(n%7) // sieving for primes from 7 to 23
if(n%11) // maybe should go before IF.H, but probably doesn't matter much
if(n%13)
if(n%17)
if(n%19)
if(n%23)
{
long long m;
int k;

// check for primes
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
if(i59>3){
n59+=S59;
r61+=s61;
r67+=s67;
r71+=s71;
r73+=s73;
r79+=s79;
r83+=s83;
r89+=s89;
r97+=s97;
if(n59>=MOD){
n59-=MOD;
r61-=m61;
r67-=m67;
r71-=m71;
r73-=m73;
r79-=m79;
r83-=m83;
r89-=m89;
r97-=m97;
if(r61<0)r61+=61;
if(r67<0)r67+=67;
if(r71<0)r71+=71;
if(r73<0)r73+=73;
if(r79<0)r79+=79;
if(r83<0)r83+=83;
if(r89<0)r89+=89;
if(r97<0)r97+=97;
};
if(r61>=61)r61-=61;            
if(r67>=67)r67-=67;            
if(r71>=71)r71-=71;            
if(r73>=73)r73-=73;            
if(r79>=79)r79-=79;            
if(r83>=83)r83-=83;            
if(r89>=89)r89-=89;            
if(r97>=97)r97-=97; 
}           
}               

n53+=S53;
if(n53>=MOD)n53-=MOD;
}

n47+=S47;
if(n47>=MOD)n47-=MOD;
}

n43+=S43;
if(n43>=MOD)n43-=MOD;
}
};


}
}
}





