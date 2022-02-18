#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int pole[MAX];
    int _pole;
}ZASOBNIK;

void init(ZASOBNIK *x);
int test(ZASOBNIK x);
void vloz(ZASOBNIK *x, int o);
void odober(ZASOBNIK *x);
void hodnota(ZASOBNIK x, int *o);
void odstran(ZASOBNIK *x);

int main()
{
    ZASOBNIK a;
    init(&a);
    return 0;
}

void init(ZASOBNIK *x){
    x->_pole = 0;
}

int test(ZASOBNIK x){
    return x._pole == 0;
}

void vloz(ZASOBNIK *x, int o){
    if(x->_pole < MAX){
        x->pole[x->_pole] = 0;
        x->_pole++;
    }
}

void odober(ZASOBNIK *x){
    if(!test(*x))
        x->_pole--;
}

void hodnota(ZASOBNIK x, int *o){
        if(!test(x))
            *o = x.pole[x._pole-1];
}

void odstran(ZASOBNIK *x){
    x->_pole = 0;
}
