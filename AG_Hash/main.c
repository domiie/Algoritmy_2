#include <stdio.h>
#include <stdlib.h>
#define M 13
#define FI 0.6180339887

typedef struct{
    char m[20];
    char p[20];
    int v;
    float n;
}RB;

typedef struct atom{
    RB bytost;
    struct atom *nasl;
}ATOM;

//linearnym zobrazenim
int FPhash(float x){
    float min = 0.0, max = 100.0;
    return ceil(((x - min)/(max - min)) * (M - 1));
}

//linearnym zobrazenim
int INThash1(int x){
    float min = 0.0, max = 1000.0;
    return ceil(((x - min)/(max - min)) * (M - 1));
}

//najmensou mocninou 2
int INThash2(int x){
    float max = 1000.0;
    int w = ceil(log2(max));
    //printf("%d\n",w);
    w = pow(2,w);
    //printf("%d\n",w);
    return ceil((x/(float)w) * (M - 1));
}

//zlatym rezom
int INThash3(int x){
    float pom = x * FI;
    pom = pom - (int)pom;
    return ceil(pom * (M - 1));
}

//modulo M
int INThash4(int x){
    return x % M;
}

//vseobecne (maskovanie bitov)
int STRhash1(char *s){
    //'A' = 65 1000001 'a' = 97 1100001 0000011111 Baba -> abaB -> 00001000100000100010
    long long int x;
    int c;
    x = s[0] & 31;
    int i;
    for(i = 1; i < strlen(s); i++){
        x = x << 5; //x <<= 5;
        c = s[i] & 31;
        x = x | c;
    }
    long double pom = x * FI;
    pom = pom - (long long int)(pom);
    return ceil(pom * (M - 1));
}

//zretazenim bitov
int STRhash2(char *s){
    int x;
    int c;
    x = s[0] & 31;
    int i;
    for(i = 1; i < strlen(s); i++){
        c = s[i] & 31;
        x = x ^ c;
    }
    float pom = x * FI;
    pom = pom - (int)(pom);
    return ceil(pom * (M - 1));
}

//mod2 (XOR)
int STRhash3(char *s){
    long long int x;
    int c;
    x = s[0] & 31;
    int i;
    for(i = 1; i < strlen(s); i++){
        x<<=1;
        c = s[i] & 31;
        x = x ^ c;
    }
    long double pom = x * FI;
    pom = pom - (long long int)(pom);
    return ceil(pom * (M - 1));
}

int main()
{
    RB *pole[M];

    FILE *f;
    RB x;
    f = fopen("vstup.txt","r");
    while(!feof(f)){
        fscanf(f,"%s %s %d %f\n", x.m, x.p, &x.v, &x.n);
        //printf("%s %s %d %f\n", x.m, x.p, x.v, x.n);
        printf("FPhash(%f) = %d\n",x.n,FPhash(x.n));
        printf("INThash1(%d) = %d\n",x.v,INThash1(x.v));
        printf("INThash2(%d) = %d\n",x.v,INThash2(x.v));
        printf("INThash3(%d) = %d\n",x.v,INThash3(x.v));
        printf("INThash4(%d) = %d\n",x.v,INThash4(x.v));
    }
    return 0;
}
