#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct{
    char m[20];
    int v;
}CLOVEK;

typedef struct atom{
    CLOVEK h;
    struct atom *nasl;
}ATOM;

// INICIALIZACIA
void init(ATOM **x){
    *x = ML;
    (*x)->nasl = NULL;
}

//TEST PRAZDNOSTI
int test(ATOM *x){
    return x->nasl == NULL;
}

//VKLADANIE NA VRCH
void vloz(ATOM **x, CLOVEK o){
    ATOM *pom;
    pom = ML;
    pom->nasl = *x;
    *x = pom;
    pom->h.v = o.v;
    strcpy(pom->h.m, o.m);
}

//ODOBERANIE Z VRCHU
void odober(ATOM **x){
    if(!test(*x)){
        ATOM *pom;
        pom = *x;
        *x = pom->nasl;
        free((void*)pom);
    }
}

//ZISTENIE HODNOTY
void hodnota(ATOM *x, CLOVEK *o){
    if(!test(x)){
        o->v = x->h.v;
        strcpy(o->m, x->h.m);
    }
}

//ODSTRANENIE
void odstran(ATOM **x){
    while(!test(*x))
        odober(x);
    //odstranenie naraznika
    free((void*)*x);
    *x = NULL;
}

int main()
{
    ATOM *a;
    init(&a);
    FILE *f;
    CLOVEK c;
    f = fopen("vstup.txt","r");
    while(!feof(f)){
        fscanf(f, "%s %d\n",c.m,&c.v);
        vloz(&a,c);
    }

    CLOVEK pom;
    while(!test(a)){
        hodnota(a,&pom);
        printf("%s %d\n",pom.m, pom.v);
        odober(&a);
    }
    fclose(f);
    return 0;
}
