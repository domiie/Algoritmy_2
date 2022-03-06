#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM))

typedef struct atom{
    int h;
    struct atom *nasl;
}ATOM;


void init(ATOM **z){
    *z = NULL;
}

int test(ATOM *z){
    return z == NULL;
}

void hodnota(ATOM *z, int *x){
    if(!test(z))
        *x = z->h;
}

void vloz(ATOM **z, int x){
    if(test(*z)){
        *z = ML;
        (*z)->h = x;
        (*z)->nasl = *z;
    }else{
        ATOM *pom = ML;
        pom->h = x;
        pom->nasl = (*z)->nasl;
        (*z)->nasl = pom;
        *z = pom;
    }
}

void vSmere(ATOM **z){
    if(!test(*z))
        *z = (*z)->nasl;
}

void protiSmere(ATOM **z){
    if(!test(*z)){
        ATOM *pom = *z;
        while(pom->nasl != *z)
            pom = pom->nasl;
        *z = pom;
    }
}

void odober(ATOM **z){
    if(!test(*z)){
        if((*z)->nasl == *z){
            free((void*)*z);
            *z = NULL;
        }else{
            ATOM *pom;
            pom = *z;
            while(pom->nasl != *z)
                pom = pom->nasl;
            pom->nasl = (*z)->nasl;
            free((void*)*z);
            *z = pom->nasl;
        }
    }
}

void odstran(ATOM **z){
    while(!test(*z)){
        odober(z);
    }
}

int main()
{
    ATOM *zoz;
    init(&zoz);
    char s[] = "streda";
    int i;
    int c;
    for(i = 0; i < strlen(s); i++)
        vloz(&zoz, s[i]);

    for(i=0; i< 6; i++){
        hodnota(zoz, &c);
        printf("%c\n", c);
        protiSmere(&zoz);
    }

    vSmere(&zoz);
    vSmere(&zoz);
    vSmere(&zoz);

    odober(&zoz);



    return 0;
}
