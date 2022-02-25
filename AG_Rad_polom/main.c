#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4

typedef struct{
    int *pole;
    int zac, kon;
    int pocet;
}RAD;

void init(RAD *x){
    x->pole = (int*)malloc(sizeof(int)*MAX);
    int i;
    for(i = 0; i < MAX; i++)
        x->pole[i] = ' ';
    x->zac = x->kon = 0;
    x->pocet = 0;
}

void vloz(RAD *x, int o){
    if(x->pocet < MAX){
        x->pole[x->kon] = o;
        x->kon = (x->kon + 1) % MAX;
        x->pocet++;
    }else
        fprintf(stderr,"rad je plny\n");
}

void odober(RAD *x){
    if(x->pocet > 0){
        x->pole[x->zac] = ' ';
        x->zac = (x->zac + 1) % MAX;
        x->pocet--;
    }else{
        fprintf(stderr,"rad je uz prazdny");
    }
}

void hodnota(RAD x, int *o){
    *o = x.pole[x.zac];
}

void odstran(RAD *x){
    free((void*)x->pole);
    x->pole = NULL;
    x->zac = x->kon = 0;
}

int main()
{
    RAD rad_e;
    init(&rad_e);
    char s[] = "ahoj";
    int i;
    for(i = 0; i < strlen(s); i++){
        vloz(&rad_e,s[i]);
    }

    for(i = 0; i < MAX; i++){
        printf("%c,",rad_e.pole[i]);
    }

    putchar('\n');
    odober(&rad_e);
    for(i = 0; i < MAX; i++){
        printf("%c,",rad_e.pole[i]);
    }

    putchar('\n');
    vloz(&rad_e,'1');
    for(i = 0; i < MAX; i++){
        printf("%c,",rad_e.pole[i]);
    }


    /*
    int c;
    while(rad_e.pocet > 0){
        hodnota(rad_e, &c);
        printf("%c\n",c);
        odober(&rad_e);
    }
    */
    return 0;
}
