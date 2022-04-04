#include <stdio.h>
#include <stdlib.h>
#define MAX 50

char pole[MAX][20];
int _pole = 0;

void vloz(char p[][20], int *_p, char * s){
    int j = *_p;
    while(j > 0 && strcmp(p[j-1],s)>0){
        strcpy(p[j],p[j-1]);
        j--;
    }
    strcpy(p[j],s);
    (*_p)++;
}

//Funkcia hladaj rekurzivne
int hladaj(char p[][20], int lava, int prava, char *s){
    //printf("l = %d, p = %d\n", lava, prava);
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
}



void vypis(char p[][20], int _p){
    int i;
    for(i = 0; i < _p; i++)
        printf("%s\n",p[i]);
}

int main()
{
//inicializacia pola = je prazdne = _pole = 0
    _pole = 0;
//aplikovanie vkladania do pola
    vloz(pole,&_pole,"jan");
    vloz(pole,&_pole,"jana");
    vloz(pole,&_pole,"anna");
    vloz(pole,&_pole,"peter");
    vloz(pole,&_pole,"michal");
    vloz(pole,&_pole,"anton");
    vloz(pole,&_pole,"roman");
    vloz(pole,&_pole,"klara");
    vloz(pole,&_pole,"monika");
    vloz(pole,&_pole,"simona");
    vloz(pole,&_pole,"jaro");
    vloz(pole,&_pole,"pavol");
    vloz(pole,&_pole,"adam");
    vloz(pole,&_pole,"zdenka");
    vypis(pole, _pole);
//aplikovanie vyhladavania
    int vysledok;
    char s[20] = "jaro";
    vysledok = hladaj(pole, 0, _pole, s);
    if(vysledok)
        printf("%s sa v poli nachadza\n", s);
    else
        printf("%s sa v poli nenachadza\n", s);

    strcpy(s,"roman");
    vysledok = hladaj(pole, 0, _pole, s);
    if(vysledok)
        printf("%s sa v poli nachadza\n", s);
    else
        printf("%s sa v poli nenachadza\n", s);

    strcpy(s,"dezider");
    vysledok = hladaj(pole, 0, _pole, s);
    if(vysledok)
        printf("%s sa v poli nachadza\n", s);
    else
        printf("%s sa v poli nenachadza\n", s);

    strcpy(s,"zoltan");
    vysledok = hladaj(pole, 0, _pole, s);
    if(vysledok)
        printf("%s sa v poli nachadza\n", s);
    else
        printf("%s sa v poli nenachadza\n", s);

    strcpy(s,"ada");
    vysledok = hladaj(pole, 0, _pole, s);
    if(vysledok)
        printf("%s sa v poli nachadza\n", s);
    else
        printf("%s sa v poli nenachadza\n", s);
}
