#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct uzol{
    char slovo[40];
    struct uzol *L, *P;
}UZOL;

//Inicializacia stromu
void ini(UZOL **st){
    *st = NULL;
}

//Rekurzivne vkladanie udajov do stromu
void vloz(UZOL **u, char *s){
    if(*u == NULL){
        *u = (UZOL*)malloc(sizeof(UZOL));
        (*u)->L = (*u)->P = NULL;
        strcpy((*u)->slovo,s);
    }
    else
        if(strcmp((*u)->slovo,s) > 0)
            vloz(&(*u)->L,s);
        else
            vloz(&(*u)->P,s);
}

//Rekurzivne vyhladavanie v strome
int hladaj(UZOL *u, char *s){
    if(u == NULL)
        return 0;
    else
    if(strcmp(u->slovo,s) == 0)
            return 1;
    else
    if(strcmp(u->slovo,s) > 0)
        return hladaj(u->L,s);
    else
    if(strcmp(u->slovo,s) < 0)
        return hladaj(u->P,s);
}


void vypis(UZOL *st){
    if(st!=NULL){
        printf("%s\n",st->slovo);
        printf("<-\n");
        vypis(st->L);
        printf("->\n");
        vypis(st->P);
        printf("^\n");
        printf("|\n");
    }
}

//Rekurzivne odstranenie stromu
void zmaz(UZOL **u){
    if((*u)->L != NULL)
        zmaz(&(*u)->L);
    if((*u)->P != NULL)
        zmaz(&(*u)->P);
    printf("Odstranujem uzol so slovom %s.\n", (*u)->slovo);
    free((void*)*u);
    *u = NULL;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
