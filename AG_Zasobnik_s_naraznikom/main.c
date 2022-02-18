#include <stdio.h>
#include <stdlib.h>

#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
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
void vloz(ATOM **x, int o){
    ATOM *pom;
    pom = ML;
    pom->nasl = *x;
    *x = pom;
    pom->h = o;
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
void hodnota(ATOM *x, int *o){
    if(!test(x))
        *o = x->h;
}

//ODSTRANENIE
void odstran(ATOM **x){
    while(!test(*x))
        odober(x);
    free((void*)*x);
    *x = NULL;
}

int main()
{
    ATOM *a;
    //inicializacia
    init(&a);
    //vlozenie hodnoty
    vloz(&a,7);
    vloz(&a,8);
    vloz(&a,9);
    //test prazdnosti
    int i = test(a);
    printf("%d\n",i);
    //hodnota na vrchu zasobnika
    int hod;
    hodnota(a,&hod);
    printf("%d\n",hod);
    //odobratie z vrchu
    odober(&a);
    hodnota(a,&hod);
    printf("%d\n",hod);
    //odstranenie zasobnika
    odstran(&a);
}
