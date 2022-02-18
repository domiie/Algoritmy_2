#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

/*
typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;
*/

typedef struct{
    char m[10];
    char p[20];
    int v;
}CLOVEK;

typedef struct atom{
    CLOVEK h;
    struct atom *nasl;
}ATOM;

int main()
{
    /*
    ATOM *p_a;
    p_a = ML;
    p_a->nasl = NULL;
    p_a->h = 3;
    p_a->nasl = ML;
    p_a->nasl->nasl = NULL;
    p_a->nasl->h = 4;
    p_a->nasl->nasl = ML;
    p_a->nasl->nasl->nasl = NULL;
    p_a->nasl->nasl->h = 5;

    //printf("%d", p_a->h);


    ATOM *pom;
    pom = p_a;
    while(pom != NULL){
        printf("%d ",pom->h);
        pom = pom->nasl;
    }


    ATOM *pom;
    pom = p_a;
    while(pom->nasl != NULL){
        pom = pom->nasl;
    }
    pom->nasl = ML;
    pom->nasl->nasl = NULL;
    pom->nasl->h = 10;

    ATOM *p;
    p = p_a;
    while(p != NULL){
        printf("%d ",p->h);
        p = p->nasl;
    }
    */

    ATOM *x;
    x = ML;
    x->nasl = NULL;
    strcpy(x->h.m, "Xenia");
    strcpy(x->h.p, "Dobra");
    x->h.v = 18;
    x->nasl = ML;
    x->nasl->nasl = NULL;
    strcpy(x->nasl->h.m, "Anna");
    strcpy(x->nasl->h.p, "Zlata");
    x->nasl->h.v = 10;

    ATOM *p;


    p = x;
    while(p->nasl != NULL){
        p = p->nasl;
    }
    p->nasl = ML;
    p->nasl->nasl = NULL;
    strcpy(p->nasl->h.m, "David");
    strcpy(p->nasl->h.p, "Hrasko");
    p->nasl->h.v = 17;

    p = x;
    while(p != NULL){
        printf("%s %s %d\n",p->h.m, p->h.p, p->h.v);
        p = p->nasl;
    }

    free((void*)x);
    x = NULL;
    free((void*)p);
    p = NULL;

    return 0;
}
