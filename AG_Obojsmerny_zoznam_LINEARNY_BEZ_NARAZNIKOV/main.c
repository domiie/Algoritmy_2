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
    z->zac = z->kon = z->ind = NULL;
}

int test(ZOZNAM z){
    return z.ind == NULL;
}

int testZac(ZOZNAM z){
    return z.ind == z.zac;
}

int testKon(ZOZNAM z){
    return z.ind == z.kon;
}

void skokZac(ZOZNAM *z){
    z->ind = z->zac;
}

void skokKon(ZOZNAM *z){
    z->ind = z->kon;
}

void posunPred(ZOZNAM *z){
    if(!test(*z))
        if(!testZac(*z))
            z->ind = z->ind->pred;
}

void posunNasl(ZOZNAM *z){
    if(!test(*z))
        if(!testKon(*z))
            z->ind = z->ind->nasl;
}

void hodnota(ZOZNAM z, int *x){
    *x = '@';
    if(!test(z))
        *x = z.ind->h;
}

void vloz(ZOZNAM *z, int x){
    if(test(*z)){
        z->ind = ML;
        z->ind->h = x;
        z->ind->pred = NULL;
        z->ind->nasl = NULL;
        z->zac = z->kon = z->ind;
    }else{
        if(testKon(*z)){
            z->ind->nasl = ML;
            z->kon = z->ind->nasl;
            z->kon->h = x;
            z->kon->nasl = NULL;
            z->kon->pred = z->ind;
            z->ind = z->kon;
        }else{
            ATOM *pom = ML;
            pom->h = x;
            pom->nasl = z->ind->nasl;
            pom->pred = z->ind;
            pom->nasl->pred = pom;
            pom->pred->nasl = pom;
            z->ind = pom;
        }
    }
}

void odober(ZOZNAM *z){
    if(!test(*z))
        if(z->zac == z->kon){
            free((void*)z->ind);
            z->ind = z->zac = z->kon = NULL;
        }else{
            if(testKon(*z)){
                z->kon = z->kon->pred;
                free((void*)z->ind);
                z->ind = z->kon;
                z->kon->nasl = NULL;
            }else{
                if(testZac(*z)){
                    z->zac = z->zac->nasl;
                    free((void*)z->ind);
                    z->ind = z->zac;
                    z->zac->pred = NULL;
                }else{
                    ATOM *pom = z->ind;
                    pom->pred->nasl = pom->nasl;
                    pom->nasl->pred = pom->pred;
                    z->ind = z->ind->nasl;
                    free((void*)pom);
                }
            }
        }
}

void odstran(ZOZNAM *z){
    while(!test(*z))
        odober(z);
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
