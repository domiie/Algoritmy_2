#include <stdio.h>
#include <stdlib.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;

ATOM *vlak;

int main()
{
    vlak = NULL;
    vlak = ML;
    vlak->h = 13; vlak->nasl = NULL;
    vlak->nasl = ML;
    vlak->nasl->h = 8;
    vlak->nasl->nasl = NULL;
    vlak->nasl->nasl = ML;
    vlak->nasl->nasl->h = 49;
    vlak->nasl->nasl->nasl = NULL;

    ATOM *p;

    p = vlak;
//VLOZENIE NA KONIEC
    while(p->nasl != NULL)
        p = p->nasl;
    p->nasl = ML;
    p = p->nasl;
    p->h = 10;
    p->nasl = NULL;

    p = vlak;
    while(p != NULL) {
        printf("%d,",p->h);
        p = p->nasl;
    }
    printf("\n");
    p = vlak;

//VLOZENIE NA KONIEC
while(p->nasl != NULL)
        p = p->nasl;
    p->nasl = ML;
    p = p->nasl;
    p->h = 178;
    p->nasl = NULL;


     p = vlak;
    while(p != NULL) {
        printf("%d,",p->h);
        p = p->nasl;
    }
        printf("\n");

//VLOZENIE NA ZACIATOK
    p = ML;
    p->nasl = vlak;
    p->h = 3;
    vlak = p;
     p = vlak;

    while(p != NULL) {
        printf("%d,",p->h);
        p = p->nasl;
    }
        printf("\n");


    return 0;
}
