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
    x->zac = x->kon = NULL;
}

int test(RAD x){
    return x.zac == NULL;
}

void vloz(RAD *x, int o){
    if(test(*x)){
        x->kon = ML;
        x->kon->h = o;
        x->kon->nasl = NULL;
        x->zac = x->kon;
    }else{
        x->kon->nasl = ML;
        x->kon = x->kon->nasl;
        x->kon->h = o;
        x->kon->nasl = NULL;
    }
}

void odober(RAD *x){
    if(!test(*x)){
        if(x->zac->nasl == NULL){
            free((void*)x->zac);
            x->zac = x->kon = NULL;
        }else{
            ATOM *pom = x->zac;
            x->zac = x->zac->nasl;
            free((void*)pom);
        }
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
