#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;

typedef struct{
    ATOM *zac, *kon, *ind; //zaciatok, koniec, index
}ZOZNAM;

void init(ZOZNAM *z){
    z->zac = ML;
    z->kon = ML;
    z->zac->nasl = z->kon;
    z->kon->nasl = NULL;
    z->ind = z->kon;
}

int test(ZOZNAM z){
    return z.zac->nasl == z.kon;
}

int test_zac(ZOZNAM z){
    return z.zac == z.ind;
}

int test_kon(ZOZNAM z){
    return z.kon == z.ind;
}

void vloz(ZOZNAM *z, int x){
    if(test_kon(*z)){
        z->kon->nasl = ML;
        z->kon->h = x;
        z->kon = z->kon->nasl;
        z->kon->nasl = NULL;
        z->ind = z->kon;
    }else{
        ATOM *pom;
        pom = ML;
        pom->h = x;
        pom->nasl = z->ind->nasl;
        z->ind->nasl = pom;
        z->ind = pom;
    }
}

void skok_zac(ZOZNAM *z){
    z->ind = z->zac;
}

void skok_kon(ZOZNAM *z){
    z->ind = z->kon;
}

void hodnota(ZOZNAM z, int *x){
    if(!test_kon(z))
        if(!test_zac(z))
            *x = z.ind->h;
}

void smerKon(ZOZNAM *z){
    if(!test_kon(*z))
        z->ind = z->ind->nasl;
}

void smerZac(ZOZNAM *z){
    if(!test_zac(*z)){
        ATOM *pom = z->zac;
        while(pom->nasl != z->ind)
            pom = pom->nasl;
        z->ind = pom;
    }
}

void odober(ZOZNAM *z){
    if(!test_kon(*z))
        if(!test_zac(*z)){
            ATOM *pom = z->zac;
            while(pom->nasl != z->ind)
                pom = pom->nasl;
            pom->nasl = z->ind->nasl;
            free((void*)z->ind);
            z->ind = pom->nasl;
        }
}

void odstran(ZOZNAM *z){
    skok_zac(z);
    smerKon(z);
    while(!test(*z))
        odober(z);
    free((void*)z->zac);
    free((void*)z->kon);
    z->zac = z->kon = z->ind = NULL;
}

int main()
{
    ZOZNAM zoz_s;
    char s[] = "streda";
    int i;
    int c;

    init(&zoz_s);
    for(i = 0; i < strlen(s); i++){
        /*skok_zac(&zoz_s);*/
        vloz(&zoz_s,s[i]);
    }

    skok_zac(&zoz_s);
    while(!test_kon(zoz_s)){
        hodnota(zoz_s, &c);
        smerKon(&zoz_s);
        printf("%c\n",c);
    }

    smerZac(&zoz_s);smerZac(&zoz_s);smerZac(&zoz_s);
    odober(&zoz_s);
    putchar('\n');

    skok_zac(&zoz_s);
    while(!test_kon(zoz_s)){
        hodnota(zoz_s, &c);
        smerKon(&zoz_s);
        printf("%c\n",c);
    }

    /*
    skok_kon(&zoz_s);
    while(!test_zac(zoz_s)){
        hodnota(zoz_s, &c);
        smerZac(&zoz_s);
        printf("%c\n",c);
    }
    */

    odstran(&zoz_s);

    return 0;
}
