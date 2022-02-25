#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;

typedef struct{
    struct atom *zac, *kon;
}RAD;

void init(RAD *x){
    x->kon = ML;
    x->zac = x->kon;
    x->kon->nasl = NULL;
}

int test(RAD x){
    return x.zac->nasl == NULL;
}

void vloz(RAD *x, int o){
    x->kon->nasl = ML;
    x->kon->h = o;

    x->kon = x->kon->nasl; //presun konca na novy naraznik
    x->kon->nasl = NULL;
}

void odober(RAD *x){
    if(!test(*x)){
        ATOM *pom = x->zac;
        x->zac = x->zac->nasl;
        free((void*)pom);
    }
}

void hodnota(RAD x, int *o){
    if(!test(x)){
        *o = x.zac->h;
    }
}

void odstran(RAD *x){
    while(!test(*x))
        odober(x);
    free((void*)x);
    x = NULL;
}

int main()
{
    RAD rad_b;
    ATOM *rad_a;
    char s[] = "ahoj";
    int i;
    init(&rad_b);
    for(i = 0; i < strlen(s); i++){
        vloz(&rad_b,s[i]);
    }

    int c;
    while(!test(rad_b)){
        hodnota(rad_b, &c);
        printf("%c\n",c);
        odober(&rad_b);
    }

    return 0;
}
