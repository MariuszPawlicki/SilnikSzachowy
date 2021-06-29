/*! \file OcenaPozycji.cpp
    \brief Plik źródłowy zawierający definicję funkcji przeprowadzającej ocenę statyczną, oraz jej funkcji pomocniczej
*/

#include "OcenaPozycji.h"
#include <cmath>

wynikZliczania zliczLF(ListaFigur * lf, float startowa1, int startowa2) {
    float wynik1=0; int wynik2=0;
    if(lf!=nullptr) {
        switch(lf->figura.typ) {
        case 'P':
            if((lf->figura.pole.kolumna==3||lf->figura.pole.kolumna==4)&&(lf->figura.pole.rzad>2)) wynik1+=1.45;
            else wynik1+=1;
            wynik2+=1;
            break;
        case 'p':
            if((lf->figura.pole.kolumna==3||lf->figura.pole.kolumna==4)&&(lf->figura.pole.rzad<5)) wynik1-=1.45;
            else wynik1-=1;
            wynik2+=1;
            break;
        case 'N':
            if((lf->figura.pole.kolumna==2||lf->figura.pole.kolumna==5)&&(lf->figura.pole.rzad==2)) wynik1+=3;
            else if((lf->figura.pole.kolumna==1||lf->figura.pole.kolumna==3||lf->figura.pole.kolumna==4||lf->figura.pole.kolumna==6)&&(lf->figura.pole.rzad==4)) wynik1+=3.15;
            else wynik1+=2.8;
            wynik2+=3;
            break;
        case 'n':
            if((lf->figura.pole.kolumna==2||lf->figura.pole.kolumna==5)&&(lf->figura.pole.rzad==5)) wynik1-=3;
            else if((lf->figura.pole.kolumna==1||lf->figura.pole.kolumna==3||lf->figura.pole.kolumna==4||lf->figura.pole.kolumna==6)&&(lf->figura.pole.rzad==5)) wynik1-=3.15;
            else wynik1-=2.8;
            wynik2+=3;
            break;
        case 'B':
            if(lf->figura.pole.rzad==2) wynik1+=3.1;
            else if(lf->figura.pole.rzad>2&&lf->figura.pole.rzad<5) wynik1+=3.2;
            else wynik1+=3;
            wynik2+=3;
            break;
        case 'b':
            if(lf->figura.pole.rzad==6) wynik1-=3.1;
            else if(lf->figura.pole.rzad<6&&lf->figura.pole.rzad>2) wynik1-=3.2;
            else wynik1-=3;
            wynik2+=3;
            break;
        case 'R':
            wynik1+=5;
            wynik2+=5;
            break;
        case 'r':
            wynik1-=5;
            wynik2+=5;
            break;
        case 'Q':
            if(lf->figura.pole.rzad==2) wynik1+=9.1;
            else if(lf->figura.pole.rzad>2&&lf->figura.pole.rzad<5) wynik1+=9.2;
            else wynik1+=9;
            wynik2+=9;
            break;
        case 'q':
            if(lf->figura.pole.rzad==6) wynik1-=9.1;
            else if(lf->figura.pole.rzad<6&&lf->figura.pole.rzad>2) wynik1-=9.2;
            else wynik1-=9;
            wynik2+=9;
            break;
        }
        return zliczLF(lf->nastepna, startowa1+wynik1, startowa2+wynik2);

    } else {
        wynikZliczania koncowy;
        koncowy.roznica = startowa1;
        koncowy.suma = startowa2;
        return koncowy;
    }
}

float ocenaPozycji(Pozycja poz) {
    wynikZliczania wyniki; float wynikKoncowy=0;
    wyniki = zliczLF(poz.listaFigur, 0, 0);
    wynikKoncowy=wyniki.roznica*sqrt((float)wyniki.suma/78);
    return wynikKoncowy;
}
