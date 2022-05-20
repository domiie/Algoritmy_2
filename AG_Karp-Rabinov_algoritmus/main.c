#include <stdio.h>
#include <stdlib.h>
#define Z 256 //mozny pocet znakov v abecede - my ich tu tolko nemame, ale nech je to mocnina 2
#define P 11//257 //dostatocne velke prvocislo; cim vacsie, tym menej kolizii
char text[1500];

//predpokladame latinku bez diakritiky a znaky zo zakladnej ASCII tabulky t.j. 'A' - 'Z', 'a' - 'z', ' ','.', ','

int main()
{
    int i,j;
    int pocet_porovnani;
    //nacitanie textu zo suboru
    //vystacime s ANSII, lebo s UTF-8 by to bolo komplikovane
    FILE *f;
    int _text = 0;//pocet znakov v prehladavanom texte
    f = fopen("text.txt","r");
    while(!feof(f)){
        fscanf(f,"%c", &text[_text++]);
    }
    //vyhladavany podretazec
    char vzor[] = "vehicula";
    //char vzor[] = "Lorem";
    int _vzor = strlen(vzor); //pocet znakov vo vzore
/*-----------------------------------------------------------------------------*/
    //algoritmus Karp-Rabin
    int textH = 0, vzorH = 0; //na hese, kedze robime modulo 257, tak staci int
    //inicializacia

    //vypocet h, co je Z umocnene na dlzku vzoru - 1, t.j. _vzor-1 a modulo P

    int h = 1; //nastavime na neutralnu hodnotu pre operaciu nasobenia
    for(i = 0; i < _vzor - 1; i++)
        h = (h * Z) % P; //vzdy robime modulo
    /*
    Mozete si overit, ze (Z * Z *Z) % P je to iste ako ((((Z % P) * Z) % P) * Z) % P.
    */
    printf("h = %d\n", h);

    //trosku inteligentnejsie hesovanie, ako pri primitivnom KR algoritme
    for(i = 0; i < _vzor; i++){
        /* Povodna verzia
        textH ^= text[i];
        vzorH ^= vzor[i];*/
        textH = (Z * textH + text[i]) % P;
        vzorH = (Z * vzorH + vzor[i]) % P;
    }
    //printf("textH = %d\n", textH);
    //printf("vzorH = %d\n", vzorH);

    pocet_porovnani = 0;
    //printf("textH = %d, vzorH = %d\n", textH, vzorH);

    //posuvanie s hesovanim
    i = 0;
    int zhodne = 0; //priznak najdenia riesenia
    while(i <= _text - _vzor && !zhodne){
        //porovname hese
        if(textH == vzorH){
            //ak su rovnake
            //musime overit znak po znaku, ze naozaj je to zhodne
            j = 0;
            while(j < _vzor && text[i + j] == vzor[j]){
                j++;
                pocet_porovnani++;
            }
            if(j == _vzor)
                zhodne = 1;
        }
        //posun s hesovanim
        if(i < _text - _vzor){
            //odstranime hodnotu pre prve pismeno a pridame nasledujuce pismeno
            //vyuzivame modularnu aritmetiku
            textH = (Z * (textH - text[i] * h) + text[i + _vzor]) % P;
            //Z * (textH - text[i] * h) je odstranenie hodnoty znaku zo zaciatku
            //+ text[i + _vzor] je pridanie noveho pismenka na koniec
            //a cele sa to vydeli modulo P

            //mozeme dosta zapornu hodnotu v textH, preto pouzijeme modularnu aritmetiku
            if(textH < 0)
                textH = textH + P;
            pocet_porovnani++;
        }

        i++;
    }

    if(!zhodne)
        printf("Retazec %s sa v texte nenachadza.\n",vzor);
    else
        printf("Retazec %s sa v texte prvykrat nachadza na pozicii %d.\n",vzor,i);
    printf("Algoritmus Karp-Rabin urobil %d porovnani.\n",pocet_porovnani);

    //kontrolny vystup
    for(i = 0; i < _text; i++)
        printf("%c", text[i]);
    fclose(f);
    return 0;
}
