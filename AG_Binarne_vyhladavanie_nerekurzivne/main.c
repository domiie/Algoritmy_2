#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct uzol{
    char slovo[40];
    struct uzol *L, *P;
}UZOL;

void vloz(char p[][20], int *_p, char * s){
    int j = *_p;
    while(j > 0 && strcmp(p[j-1],s)>0){
        strcpy(p[j],p[j-1]);
        j--;
    }
    strcpy(p[j],s);
    (*_p)++;
}

//Funkcia hladaj nerekurzivne
int hladaj(char p[][20], int max, char *s){
    int lava = 0, prava = max, stred;
    while(lava < prava){
        stred = (lava+prava)/2;
        printf("porovnavam %s, %s\n",p[stred],s);
        if(strcmp(p[stred],s) == 0)
            return 1;
        if(strcmp(p[stred],s) > 0)
                prava = stred - 1;
            else
                lava = stred + 1;
    }
    return -1;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
