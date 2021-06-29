/*! \file main.cpp
    \brief Plik główny programu
*/

#include <iostream>
#include "Pozycja.h"
#include "WejsciaWyjscia.h"
#include "Figury.h"
#include "SelekcjaRuchow.h"
#include "OcenaPozycji.h"
#include "MinMax.h"

using namespace std;

int main()
{
    //kod fen pozycji startowej: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    //mat w 2 r1r3k1/5ppp/8/8/8/8/Q7/R2K4 w - - 0 1
    //zagadka wielopoziomowa 1k6/8/8/6p1/5p2/4Q3/8/3K4 w - - 0 1

    bool warunek = true;
    Ruch r;
    cout<<"Podaj kod FEN pozycji, lub naci\230nij ENTER by wczyta\206 pozycj\251 pocz\245tkow\245: ";
    string fen = wczytajFEN();
    Pozycja poz = FenNaPozycje(fen);
    rysujPozycje(poz);

    cout<<"Czy poda\206 znalezione przez program legalne ruchy? (T/N): ";
    char odp; cin>>odp;
    if(odp=='T'||odp=='t') {
        cout<<endl<<"Znalezione ruchy: "<<endl;
        wypiszLR(wczytajWszystkieKNaR(poz));
    }

    while(true) {
        cout<<"Czy poda\206 najlepszy ruch znaleziony przez program? (T/N): ";
        cin>>odp;
        if(odp=='T'||odp=='t') {
            int odp2;
            while(true) {
                cout<<"Podaj g\210\251boko\230\206 poszukiwa\344 (>1): ";
                cin>>odp2;
                if(odp2<1) cout<<"Podano b\210\251dne dane"<<endl;
                else if(odp2>4) cout<<"Ta g\210\251boko\230\206 jest zbyt du\276a"<<endl;
                else break;
            }

            WynikMinMaxu wmm = MinMax(poz, odp2);
            cout<<"Ocena MinMaxu: "<<wmm.ocena<<","<<" Proponowany ruch: "<<(char)(wmm.ruch.z.kolumna+97)<<wmm.ruch.z.rzad+1<<(char)(wmm.ruch.na.kolumna+97)<<wmm.ruch.na.rzad+1<<endl;
        }

        while(warunek) {
            r = wczytajRuch();
            if(czyRuchJestNaLiscie(r, wczytajWszystkieKNaR(poz))) {
                poz = wykonajRuch(r, poz);
                warunek = false;
            } else cout<<"Nieprawid\210owy ruch"<<endl;
        }
        cout<<endl<<"Nowa pozycja: "<<endl;
        rysujPozycje(poz);

        if(czyMat(poz) && poz.czyjRuch==1) {
            cout<<endl<<"Bia\210e wygra\210y!"<<endl;
            break;
        }
        if(czyMat(poz) && poz.czyjRuch==0) {
            cout<<endl<<"Czarne wygra\210y!"<<endl;
            break;
        }
        if(czyPat(poz)) {
            cout<<endl<<"Remis"<<endl;
            break;
        }

        cout<<"Czy poda\206 znalezione przez program legalne ruchy (T/N): ";
        char odp; cin>>odp;
        if(odp=='T'||odp=='t') {
            cout<<endl<<"Znalezione ruchy: "<<endl;
            wypiszLR(wczytajWszystkieKNaR(poz));
        }

        warunek = true;
    }

    return 0;
}
