#include <stdio.h>
#include <stdlib.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;

void init(ATOM **x);
int test(ATOM *x);
void vloz(ATOM **x, int o);
void odober(ATOM **x);
void odstran(ATOM **x);
void hodnota(ATOM *x, int *o);

int main()
{
    ATOM *a;
    init(&a);
    vloz(&a, 8);
    int i;
    hodnota(a,&i);
    printf("%d\n",i);
    return 0;
}

void init(ATOM **x){
    *x = NULL;
}

int test(ATOM *x){
    return x==NULL;
}

void vloz(ATOM **x, int o){
    if(test(*x)){ //ak je prazdny
        *x = ML;
        (*x)->nasl = NULL;
        (*x)->h = o;
    }else{ //ak nie je prazdny
        ATOM *pom;
        pom = ML;
        pom->nasl = *x;
        pom->h = o;
    }
}

void odober(ATOM **x){
    if(!test(*x)){ //iba 1 atom
        if((*x)->nasl == NULL){
            free((void*)x);
            *x = NULL;
        }else{
            ATOM *pom;
            pom = *x;
            *x = (*x)->nasl;
            free((void*)pom);
        }
    }
}

void hodnota(ATOM *x, int *o) {
    if(!test(x)) {
        *o = x->h;
    }
}

void odstran(ATOM **x){
    while(!test(*x))
        odober(x);
}
