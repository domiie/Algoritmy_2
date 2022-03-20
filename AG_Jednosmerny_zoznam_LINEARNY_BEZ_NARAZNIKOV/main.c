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
    z->zac = z->kon = z->ind = NULL;
}

int test(ZOZNAM z){
    return z.ind == NULL;
}

int test_zac(ZOZNAM z){
    return z.ind == z.zac;
}

int test_kon(ZOZNAM z){
    return z.ind == z.kon;
}

void skok_zac(ZOZNAM *z){
    z->ind = z->zac;
}

void skok_kon(ZOZNAM *z){
    z->ind = z->kon;
}

void hodnota(ZOZNAM z, int *x){
    if(!test(z))
        *x = z.ind->h;
}

void vloz(ZOZNAM *z, int x){
    if(test(*z)){
        z->ind = ML;
    	z->zac = z->kon = z->ind;
    	z->ind->h = x;
    	z->ind->nasl = NULL;
    }else{
        if(test_kon(*z)){
            z->kon->nasl = ML;
            z->kon = z->kon->nasl;
            z->kon->nasl = NULL;
            z->kon->h = x;
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
}

void smerKon(ZOZNAM *z){
    if(!test(*z))
        if(!test_kon(*z))
            z->ind = z->ind->nasl;
}

void smerZac(ZOZNAM *z){
    if(!test(*z))
        if(!test_zac(*z)){
            ATOM *pom = z->zac;
            while(pom->nasl != z->ind)
                pom = pom->nasl;
            z->ind = pom;
        }
}

void odober(ZOZNAM *z){
    if(!test(*z)){
        if(z->zac == z->kon){
            free((void*)z->ind);
            z->ind = z->kon = z->zac = NULL;
        }else{
            if(test_kon(*z)){
                ATOM *pom = z->zac;
                while(pom->nasl != z->kon)
                    pom = pom->nasl;
                free((void*)z->kon);
                z->kon = z->ind = pom;
            }else{
                if(test_zac(*z)){
                    z->ind = z->ind->nasl;
                    free((void*)z->zac);
                    z->zac = z->ind;
                }else{
                    ATOM *pom = z->zac;
                    while(pom->nasl != z->ind)
                        pom = pom->nasl;
                    pom->nasl = z->ind->nasl;
                    free((void*)z->ind);
                    z->ind = pom->nasl;
                }
            }
        }
    }
}

void odstran(ZOZNAM *z){
    skok_zac(z);
	while(!test(*z))
		odober(z);
	z->zac = z->kon = z->ind = NULL;
}

int main()
{
    ZOZNAM zoz_b;
    char s[] = "streda";
    int i;
    int c;

    init(&zoz_b);
    for(i = 0; i < strlen(s); i++){
        /*skok_zac(&zoz_b);*/
        vloz(&zoz_b,s[i]);
    }

    skok_kon(&zoz_b);
    odober(&zoz_b);

    skok_kon(&zoz_b);
    while(!test_zac(zoz_b)){
        hodnota(zoz_b, &c);
        printf("%c\n",c);
        smerZac(&zoz_b);
    }




    return 0;
}
