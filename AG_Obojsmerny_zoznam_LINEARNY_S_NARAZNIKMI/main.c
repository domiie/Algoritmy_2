#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl, *pred;
}ATOM;

typedef struct{
    ATOM *zac, *ind, *kon;
}ZOZNAM;

void init(ZOZNAM *z){
    z->zac = ML;
    z->kon = ML;
    z->ind = z->kon;
    z->zac->nasl = z->kon;
    z->zac->pred = NULL;
    z->kon->nasl = NULL;
    z->kon->pred = z->zac;
}

int test(ZOZNAM z){
    return z.zac->nasl == z.kon;
}

int testZac(ZOZNAM z){
    return z.zac == z.ind;
}

int testKon(ZOZNAM z){
    return z.kon == z.ind;
}

void skokZac(ZOZNAM *z){
    z->ind = z->zac;
}

void skokKon(ZOZNAM *z){
    z->ind = z->kon;
}

void posunPred(ZOZNAM *z){
    if(!testZac(*z))
        z->ind = z->ind->pred;
}

void posunNasl(ZOZNAM *z){
    if(!testKon(*z))
        z->ind = z->ind->nasl;
}

void hodnota(ZOZNAM z, int *x){
    *x = '@';
    if(!testKon(z))
        if(!testZac(z))
            *x = z.ind->h;
}

void vloz(ZOZNAM *z, int x){
    if(testKon(*z)){
        z->kon->h = x;
        z->kon->nasl = ML;
        z->kon = z->kon->nasl;
        z->kon->nasl = NULL;
        z->kon->pred = z->ind;
        z->ind = z->kon;
    }else{
        ATOM *pom = ML;
        pom->h = x;
        pom->nasl = z->ind->nasl;
        pom->pred = z->ind;
        pom->nasl->pred = pom;
        z->ind->nasl = pom;
        z->ind = pom;
    }
}

void odober(ZOZNAM *z){
    if(!testZac(*z))
        if(!testKon(*z)){
            ATOM *pom = z->ind;
            z->ind->nasl->pred = z->ind->pred;
            z->ind->pred->nasl = z->ind->nasl;
            z->ind = z->ind->nasl;
            free((void*)pom);
        }
}

void odstran(ZOZNAM *z){
    skokZac(z);
    posunNasl(z);
    while(!test(*z))
        odober(z);
    free((void*)z->zac);
    free((void*)z->kon);
    z->zac = z->kon = z->ind = NULL;
}

int main()
{
    ZOZNAM zozl;
    char s[] = "streda";
    int c;

    init(&zozl);
    int i;
    for(i=0;i<strlen(s);i++){
        vloz(&zozl,s[i]);
    }
    skokZac(&zozl);
    while(!testKon(zozl)){
        hodnota(zozl,&c);
        printf("%c\n",c);
        posunNasl(&zozl);
    }
    posunPred(&zozl);posunPred(&zozl);posunPred(&zozl);
    vloz(&zozl, 'V');
    skokZac(&zozl);
    vloz(&zozl,'R');
    putchar('\n');

    skokKon(&zozl);
    while(!testZac(zozl)){
        hodnota(zozl,&c);
        printf("%c\n",c);
        posunPred(&zozl);
    }

    putchar('\n');
    skokKon(&zozl);
    posunPred(&zozl);posunPred(&zozl);posunPred(&zozl);
    odober(&zozl);

    odstran(&zozl);

    skokKon(&zozl);
    while(!testZac(zozl)){
        hodnota(zozl,&c);
        printf("%c\n",c);
        posunPred(&zozl);
    }

    return 0;
}
