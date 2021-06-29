/*! \file MinMax.cpp
    \brief Plik źródłowy zawierający definicję najważniejszej funkcji w programie (MinMax)
*/

#include "MinMax.h"
#include "OcenaPozycji.h"
#include "SelekcjaRuchow.h"

WynikMinMaxu MinMax(Pozycja poz, int glebokosc, float alfa, float beta) {
    WynikMinMaxu wynikTymczasowy, wynikKoncowy; wynikKoncowy.ocena=1001; //1001 - pierwszy element

    if(glebokosc==0) {
        wynikKoncowy.ocena = ocenaPozycji(poz);
    } else if(poz.czyjRuch==false) { //strona maksymalizująca (białe)
        ListaRuchow * listaR = wczytajWszystkieKNaR(poz);
        ListaRuchow *w = listaR;
        while(w!=nullptr) {
            Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
            nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
            skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
            nPoz = wykonajRuch(w->ruch, nPoz);
            if(czyMat(nPoz)) {
                wynikTymczasowy.ocena=101;
                wynikTymczasowy.ruch=w->ruch;
                if(alfa<wynikTymczasowy.ocena) alfa=wynikTymczasowy.ocena;
            }else if(czyPat(nPoz)) {
                wynikTymczasowy.ocena=0;
                wynikTymczasowy.ruch=w->ruch;
                if(alfa<wynikTymczasowy.ocena) alfa=wynikTymczasowy.ocena;
            } else {
                wynikTymczasowy=MinMax(nPoz, glebokosc-1, alfa, beta);
                wynikTymczasowy.ruch=w->ruch;
                if(alfa<wynikTymczasowy.ocena) alfa=wynikTymczasowy.ocena;
            }

            if(wynikKoncowy.ocena==1001) {
                wynikKoncowy=wynikTymczasowy;
                if(alfa<wynikTymczasowy.ocena) alfa=wynikTymczasowy.ocena;
            } else if(wynikKoncowy.ocena<wynikTymczasowy.ocena) {
                wynikKoncowy=wynikTymczasowy;
                if(alfa<wynikTymczasowy.ocena) alfa=wynikTymczasowy.ocena;
            }

            if(beta<=alfa) break;
            w = w->next;
        }
    } else { //strona minimalizująca (czarne)
        ListaRuchow * listaR = wczytajWszystkieKNaR(poz);
        ListaRuchow *w = listaR;
        while(w!=nullptr) {
            Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
            nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
            skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
            nPoz = wykonajRuch(w->ruch, nPoz);
            if(czyMat(nPoz)) {
                wynikTymczasowy.ocena=-101;
                wynikTymczasowy.ruch=w->ruch;
                if(beta>wynikTymczasowy.ocena) beta=wynikTymczasowy.ocena;
            }else if(czyPat(nPoz)) {
                wynikTymczasowy.ocena=0;
                wynikTymczasowy.ruch=w->ruch;
                if(beta>wynikTymczasowy.ocena) beta=wynikTymczasowy.ocena;
            } else {
                wynikTymczasowy=MinMax(nPoz, glebokosc-1, alfa, beta);
                wynikTymczasowy.ruch=w->ruch;
                if(beta>wynikTymczasowy.ocena) beta=wynikTymczasowy.ocena;
            }

            if(wynikKoncowy.ocena==1001) {
                wynikKoncowy=wynikTymczasowy;
                if(beta>wynikTymczasowy.ocena) beta=wynikTymczasowy.ocena;
            } else if(wynikKoncowy.ocena>wynikTymczasowy.ocena) {
                wynikKoncowy=wynikTymczasowy;
                if(beta>wynikTymczasowy.ocena) beta=wynikTymczasowy.ocena;
            }

            if(beta<=alfa) break;
            w = w->next;
        }
    }
    return wynikKoncowy;
}
