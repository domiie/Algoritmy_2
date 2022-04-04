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

/*Funkcia hladaj rekurzivne
int hladaj(char p[][20], int lava, int prava, char *s){
    printf("l = %d, p = %d\n", lava, prava);
    if(lava > prava)
        return 0;
    else{
        int stred = (lava+prava)/2;
        printf("porovnavam %s, %s\n",p[stred],s);
        if(strcmp(p[stred],s) == 0)
            return 1;
        else
            if(strcmp(p[stred],s) > 0)
                return hladaj(p,lava, stred -1,s);
            else
                return hladaj(p, stred + 1, prava,s);
    }
}*/

int main()
{
    printf("Hello world!\n");
    return 0;
}
