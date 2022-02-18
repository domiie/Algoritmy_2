#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM*)malloc(sizeof(ATOM)) //makro na rychle alkovanie atomu v halde

typedef int TYP; //definovanie typu udajov ukladanych v poli, teraz sme zvolili int

typedef struct  atom {
    TYP h; //na ukladanie hodnoty v atome
    struct atom *nasl; //rekurzivna cas struktury
}ATOM;



//deklaracia - zoznam funkcii
void create(ATOM **z); //inicializacia zasobnika
int empty(ATOM *z); //test na prazdnost zasobnika
void push(ATOM **z, TYP x); //vkladanie prvku na vrch zasobnika
void pop(ATOM **z); //odoberanie prvku z vrchu zasobnika
void top(ATOM *z, TYP *x); //citanie hodnoty z vrchu zasobnika
void destroy(ATOM **z); //odstranenie zasobnika z pamate  !!! Ma vyznam len pri pouziti dynamickeho pola !!!

void analyzuj(char *s);

int main()
{
    char s_ok[] = "((())())(())";
    char s_r[] = "()(()))())()";
    char s_l[] = "((()(())()";
    char vyraz[] = "(a + b) * ((a - c) / ((a + 6)";
    analyzuj(s_ok);
    analyzuj(s_r);
    analyzuj(s_l);
    analyzuj(vyraz);
    return 0;
}


void create(ATOM **z) {
    //vytvorime atom, ktory bude plnit funkciu naraznika
    *z = ML;
    (*z)->nasl = NULL;
    //(*z)->h = '#'; nie je potrebne, lebo atom plni ulohu naraznika
}

int empty(ATOM *z) {
    return z->nasl == NULL;
}

void push(ATOM **z, TYP x) {
    ATOM *p;
    p = ML;
    p->h = x;
    p->nasl = *z;
    *z = p;
}

void pop(ATOM **z) {
    if(!empty(*z)) {
        ATOM *p;
        p = *z;
        *z = (*z)->nasl;
        free((void*)p);
        //p = NULL; nie je potrebne
    }
    else {
        fprintf(stderr,"Pokus o odobratie atomu z prazdneho zasobnika.\n");
    }
}

void top(ATOM *z, TYP *x) {
    if(!empty(z)) {
        *x = z->h;
    }
    else {
        fprintf(stderr,"Pokus o citanie z prazdneho zasobnika.\n");
    }
}

void destroy(ATOM **z) {
    while(!empty(*z))
        pop(z);
    //este odobrat naraznik
    free((void*)*z);
    *z = NULL;
}

void analyzuj(char *s) {
    ATOM *a;
    create(&a);
    int i = 0;
    int chyba = 0;
    while(i < strlen(s) && !chyba) {
        printf("%c",s[i]);
        if(s[i] == '(')
            push(&a,'#');
            else
                if(s[i] == ')')
                    if(empty(a))
                        chyba = 1;
                    else
                        pop(&a);
            i++;
    }
    printf("\n");
    if(chyba)
        printf("Chyba lava zatvorka.\n");
    else
        if(!empty(a)) {
            printf("Lavych zatvoriek je viac ako pravych.\n");
        }
        else
            printf("Vyraz je spravne uzatvorkovany.\n");
    destroy(&a);
}
