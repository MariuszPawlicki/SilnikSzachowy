/*! \file WejsciaWyjscia.cpp
    \brief Plik źródłowy zawierający funkcje obsługujące interfejs konsolowy
*/

#include "WejsciaWyjscia.h"

string wczytajFEN() {
    string f;
    getline(cin, f);
    if(f=="") f="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    return f;
}

Ruch wczytajRuch() {
    string wej;
    Ruch r;
    cout<<"Podaj ruch: ";
    cin>>wej;
    r.z.kolumna = ((int)wej[0])-97;
    r.z.rzad = ((int)wej[1])-49;
    r.na.kolumna = ((int)wej[2])-97;
    r.na.rzad = ((int)wej[3])-49;
    if(wej.length()>4) r.figPromocji = wej[4];
    else r.figPromocji = ' ';
    return r;
}

void rysujPozycje(Pozycja poz) {
    char str[8][8];
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            str[i][j] = ' ';
        }
    }
    figuryNaTekst(str, poz.listaFigur);
    cout<<"  ---------------------------------"<<endl;
    for(int i=0;i<8;i++) {
        cout<<8-i<<" | ";
        for(int j=0;j<8;j++) {
            cout<<str[7-i][j]<<" | ";
        }
        cout<<endl<<"  ---------------------------------"<<endl;
    }
    cout<<"    A   B   C   D   E   F   G   H"<<endl;
    cout<<"Ruch wykonuj\245: ";
    if(poz.czyjRuch==0) cout<<"bia\210e";
    else cout<<"czarne";
    cout<<endl;
}
