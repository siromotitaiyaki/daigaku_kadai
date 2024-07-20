#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define D 60
#define num 1000000 //試行回数

/* MT */

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */

/* MT */

int main(void){
    int card[D];
    int a, b, max_X, max_Y, max_Z;
    double max_rate=0;
    //枚数毎にシミュレーション
    for(a=16; a<18; a++){
        for(b=16; b<18; b++){
            int count = 0;
            for(int i=0; i<a; i++){ //X
                card[i] = 0;
            }
            for(int i=a; i<a+b; i++){ //Y
                card[i] = 1;
            }
            for(int i=a+b; i<D; i++){ //Z
                card[i] = 2;
            }
            unsigned long int seed;
            init_genrand(seed = (unsigned long)time(NULL));
            for(int k=0; k<num; k++){ //試行回数だけ繰り返し
                int n=7; //取り出す枚数
                while(n>3){ //n=3で負け、終了
                    int x=0, y=0, z=0;
                    /* 課題４流用 */
                    int i, a[D], tmp, flag=0;
                    a[0] = (int)(genrand_real2()*D); //最初の数
                    for(i=1; i<D; i++, flag=0){ //2番目以降の数
                        tmp = (int)(genrand_real2()*D);
                        for(int j=0; j<i; j++){ //同値有無判定
                            if(tmp == a[j]){
                                i--;
                                flag=1;
                                break;
                            }
                        }
                        if(flag == 0){ //判定
                            a[i] = tmp;
                        }
                    }
                    /* 課題４流用 */
                    for(int j=0; j<n; j++){ //結果
                        if(card[a[j]] == 0)x++;
                        else if(card[a[j]] == 1)y++;
                        else z++;
                    }
                    if(x>=1 && y>=1 && z>=2){ //勝敗判定
                        count++;
                        break;
                    }else{
                        n--;
                    }
                }
            }
            double win_rate = 100.0*count/num;
            if(max_rate < win_rate){ //勝率比較
                max_rate = win_rate;
                max_X = a;
                max_Y = b;
                max_Z = 60-a-b;
            }
            printf("勝率：%lf%%, (x,y,z)=(%d,%d,%d)\n", win_rate, a, b, 60-a-b);
        }
    }
    printf("最も高い勝率：%lf%%, (x,y,z)=(%d,%d,%d)\n", max_rate, max_X, max_Y, max_Z);
    return 0;
}