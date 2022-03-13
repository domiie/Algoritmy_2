#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl, *pred;
}ATOM;

void init(ATOM **z){
    *z = NULL;

}

int test(ATOM *z){
    return z == NULL;
}

void vloz(ATOM **z, int x){
    if(test(*z)){
        *z = ML;
        (*z)->h = x;
        (*z)->nasl = *z;
        (*z)->pred = *z;
    }else{
        ATOM *pom = ML;
        pom->h = x;
        pom->nasl = (*z)->nasl;
        pom->pred = *z;
        (*z)->nasl->pred = pom;
        (*z)->nasl = pom;
        *z = pom;
    }
}

void hodnota(ATOM *z, int *x){
    if(!test(z))
        *x = z->h;
}

void posunNasl(ATOM **z){
    if(!test(*z)){
        *z = (*z)->nasl;
    }
}

void posunPred (ATOM **z){
    if(!test(*z)){
        *z = (*z)->pred;
    }
}

void odober(ATOM **z){
    if(!test(*z)){
        if((*z)->nasl == *z){
            free((void*)*z);
            *z = NULL;
        }else{
            ATOM *pom = *z;
            (*z)->pred->nasl = (*z)->nasl;
            (*z)->nasl->pred = (*z)->pred;
            *z = (*z)->nasl;
            free((void*)pom);
        }
    }
}

void odstran(ATOM **z){
    if(!test(*z))
        odober(z);
}

int main()
{
    ATOM *zoz;
    char s[] = "streda";
    init(&zoz);
    int i;
    for(i=0;i<strlen(s);i++){
        vloz(&zoz,s[i]);
    }

    int c;

    for(i=0;i<6;i++){
        hodnota(zoz,&c);
        printf("%c\n",c);
        posunPred(&zoz);
    }
    odober(&zoz);odober(&zoz);odober(&zoz);
    for(i=0;i<6;i++){
        hodnota(zoz,&c);
        printf("%c\n",c);
        posunPred(&zoz);
    }

    return 0;
}
