#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;

void init(ATOM **x){
    *x = NULL;
}

int test(ATOM *x){
    return x == NULL;
}

void vloz(ATOM **x, int o){
    if(test(*x)){ //ak je prazdny
        *x = ML;
        (*x)->nasl = NULL;
        (*x)->h = o;
    }else{
        ATOM *pom = *x;
        while(pom->nasl != NULL)
            pom = pom->nasl;
        pom->nasl = ML;
        pom->nasl->h = o;
        pom->nasl->nasl = NULL;
    }
}

void odober(ATOM **x){
    if(!test(*x)){
        if((*x)->nasl == NULL){
            free((void*)*x);
            *x = NULL;
        }else{
            ATOM *pom = *x;
            *x = (*x)->nasl;
            free((void*)pom);
        }
    }
}

void hodnota(ATOM *x, int *o){
    if(!test(x)){
        *o = x->h;
    }
}

void odstran(ATOM **x){
    while(!test(*x))
        odober(x);
    free((void*)*x);
    *x = NULL;
}

int main()
{
    ATOM *rad_a;
    init(&rad_a);
    char s[] = "ahoj";
    int i;
    for(i = 0; i < strlen(s); i++){
        vloz(&rad_a,s[i]);
    }

    int c;
    while(!test(rad_a)){
        hodnota(rad_a, &c);
        printf("%c\n",c);
        odober(&rad_a);
    }

    return 0;
}
