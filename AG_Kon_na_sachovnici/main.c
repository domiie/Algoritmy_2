#include <stdio.h>
#include <stdlib.h>


int krok, nasiel;

void vypis(char b[][8]){
    int i,j;
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            if(b[i][j] == '.' || b[i][j] == '#'){
                printf("%c\t", b[i][j]);
            }else{
                printf("%d\t", b[i][j]);
            }
        }
        putchar('\n');
    }
    getchar();
}

void hladaj(char b[][8], int x, int y){
    krok++;
    b[x][y] = krok;
    printf("x = %d, y = %d\n", x, y);
    vypis(b);
    if(krok == 64){
        nasiel = 1;
        return;
    }
    if(!nasiel && x+2 < 8 && y+1 < 8 && b[x+2][y+1] == '.')hladaj(b, x+2, y+1);
    if(!nasiel && x+2 < 8 && y-1 > 0 && b[x+2][y-1] == '.')hladaj(b, x+2, y-1);
    if(!nasiel && x-2 > 0 && y+1 < 8 && b[x-2][y+1] == '.')hladaj(b, x-2, y+1);
    if(!nasiel && x-2 > 0 && y-1 > 0 && b[x-2][y-1] == '.')hladaj(b, x-2, y-1);
    if(!nasiel && x-1 > 0 && y+2 < 8 && b[x-1][y+2] == '.')hladaj(b, x-1, y+2);
    if(!nasiel && x-1 > 0 && y-2 > 0 && b[x-1][y-2] == '.')hladaj(b, x-1, y-2);
    if(!nasiel && x+1 < 8 && y+2 < 8 && b[x+1][y+2] == '.')hladaj(b, x+1, y+2);
    if(!nasiel && x+1 < 8 && y-2 > 0 && b[x+1][y-2] == '.')hladaj(b, x+1, y-2);
    b[x][y] = '.';
    krok--;
}

int main()
{
    char bludisko[8][8];
    int i,j;
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            bludisko[i][j] = '.';
        }
    }

    srand((unsigned)time(NULL));
    krok = 0;
    nasiel = 0;
    i = 0;

    vypis(bludisko);
    hladaj(bludisko, 0, 0);


    return 0;
}
