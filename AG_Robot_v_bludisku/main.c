#include <stdio.h>
#include <stdlib.h>

int krok;
int nasiel;

void hladaj(char b[][8],int x, int y){
    //znacka
    krok++;
    b[x][y] = krok;
    printf("x = %d, y = %d\n",x,y);
    vypis(b);
    //if(nasiel) return;
    //nerekurzivna vetva
    if(!nasiel && x == 7 && y == 7){nasiel = 1;return;}
    if(!nasiel && x < 7 && b[x+1][y] == '.') hladaj(b,x+1,y);
    if(!nasiel && y < 7 && b[x][y+1] == '.') hladaj(b,x,y+1);
    if(!nasiel && x > 0 && b[x-1][y] == '.') hladaj(b,x-1,y);
    if(!nasiel && y > 0 && b[x][y-1] == '.') hladaj(b,x,y-1);
    //odobratie znacky
    b[x][y] = '.';
    krok--;
}



int main()
{

    char bludisko[8][8];
    nasiel = 0;
    int i, j;
    //inicializacia
    for(i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            bludisko[i][j] = '.';
    /*for(i = 0; i < 64; i++)
        printf("%d %d\n", i/8, i%8);*/
    //generovanie prekazok
    int prekazky[63], _prekazky = 63;
    bludisko[0][0] = '.';
    for(i = 1; i < _prekazky; i++)
        prekazky[i] = i;
    srand((unsigned)time(NULL));
    int pocet_prekazok = 10;
    i = 0;
    while(i < pocet_prekazok){
        j = rand() % _prekazky;
        bludisko[prekazky[j]/8][prekazky[j]%8] = '#';
        _prekazky--;
        prekazky[j] = prekazky[_prekazky];
        i++;
    }
    hladaj(bludisko,0,0);
    //vypis(bludisko);
    return 0;
}

void vypis(char b[][8]){
    int i,j;
    printf("----------------------------------------------------------\n");
    for(i = 0 ; i < 8; i++){
        for(j = 0; j < 8; j++)
            if(b[i][j] == '.' || b[i][j] == '#')
                printf("%c\t",b[i][j]);
            else
                printf("%d\t",b[i][j]);
        putchar('\n');
    }
    getch();
}
