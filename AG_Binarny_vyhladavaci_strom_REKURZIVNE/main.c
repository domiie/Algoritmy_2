#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct uzol{
    char slovo[20];
    struct atom *L, *P;
}UZOL;

UZOL *bst;

void init(UZOL **st){
    *st = NULL;
}

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
    init(&bst);
//volanie vkladania
    vloz(&bst,"vlado");
    vloz(&bst,"jana");
    vloz(&bst,"zdeno");
    vloz(&bst,"aladar");
    vloz(&bst,"karol");
    vloz(&bst,"jozo");
    vloz(&bst,"albin");
    vypis(bst);

//aplikovanie vyhladavania
    int vysledok;
    char slovo[20] = "koloman";
    vysledok = (hladaj(bst,slovo));
    if(vysledok)
        printf("%s sa nachadza v slovniku\n",slovo);
    else
        printf("%s sa nenachadza v slovniku\n",slovo);

    strcpy(slovo,"karol");
    vysledok = (hladaj(bst,slovo));
    if(vysledok)
        printf("%s sa nachadza v slovniku\n",slovo);
    else
        printf("%s sa nenachadza v slovniku\n",slovo);

    zmaz(&bst);
    return 0;
}
