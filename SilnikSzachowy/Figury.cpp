/*! \file Figury.cpp
    \brief Plik źródłówy zawierający definicje wszystkich figur (struktur) i ich funkcji
*/

#include "Figury.h"
#include "SelekcjaRuchow.h"
#include "Pozycja.h"

void PionB::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;

    if((pole.kolumna-1)>=0 && (pole.rzad+1)<=7) {
        r.na.kolumna=pole.kolumna-1; r.na.rzad=pole.rzad+1;
        if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false && zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if((pole.kolumna+1)<=7 && (pole.rzad+1)<=7) {
        r.na.kolumna=pole.kolumna+1; r.na.rzad=pole.rzad+1;
        if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false && zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if((pole.rzad+1)<=7) {
        r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad+1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if(pole.rzad==1) {
        r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad+1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {
            r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad+2;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
        }
    }
    //bicie w przelocie prawe
    if(poz.czyJestpBiciaWPrzelocie==true) {
        if(poz.pBiciaWPrzelocie.kolumna==pole.kolumna+1 && poz.pBiciaWPrzelocie.rzad==pole.rzad+1 && czyRuchLegalny(r, poz)) {
            r.na.rzad=poz.pBiciaWPrzelocie.rzad; r.na.kolumna=poz.pBiciaWPrzelocie.kolumna;
            dodajRuch(r, lr);
        }
    }
    //bicie w przelocie lewe
    if(poz.czyJestpBiciaWPrzelocie==true) {
        if(poz.pBiciaWPrzelocie.kolumna==pole.kolumna-1 && poz.pBiciaWPrzelocie.rzad==pole.rzad+1 && czyRuchLegalny(r, poz)) {
            r.na.rzad=poz.pBiciaWPrzelocie.rzad; r.na.kolumna=poz.pBiciaWPrzelocie.kolumna;
            dodajRuch(r, lr);
        }
    }
}

void PionC::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    if((pole.kolumna-1)>=0 && (pole.rzad-1)>=0) {
        r.na.kolumna=pole.kolumna-1; r.na.rzad=pole.rzad-1;
        if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true && zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if((pole.kolumna+1)<=7 && (pole.rzad-1)>=0) {
        r.na.kolumna=pole.kolumna+1; r.na.rzad=pole.rzad-1;
        if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true && zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if((pole.rzad-1)>=0) {
        r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad-1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    if(pole.rzad==6) {
        r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad-1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {
            r.na.kolumna=pole.kolumna; r.na.rzad=pole.rzad-2;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' && czyRuchLegalny(r, poz)) dodajRuch(r, lr);
        }
    }
    //bicie w przelocie prawe
    if(poz.czyJestpBiciaWPrzelocie==true) {
        if(poz.pBiciaWPrzelocie.kolumna==pole.kolumna+1 && poz.pBiciaWPrzelocie.rzad==pole.rzad-1 && czyRuchLegalny(r, poz)) {
            r.na.rzad=poz.pBiciaWPrzelocie.rzad; r.na.kolumna=poz.pBiciaWPrzelocie.kolumna;
            dodajRuch(r, lr);
        }
    }
    //bicie w przelocie lewe
    if(poz.czyJestpBiciaWPrzelocie==true) {
        if(poz.pBiciaWPrzelocie.kolumna==pole.kolumna-1 && poz.pBiciaWPrzelocie.rzad==pole.rzad-1 && czyRuchLegalny(r, poz)) {
            r.na.rzad=poz.pBiciaWPrzelocie.rzad; r.na.kolumna=poz.pBiciaWPrzelocie.kolumna;
            dodajRuch(r, lr);
        }
    }
}

void Goniec::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    for(int i=1; i<8; i++) {
        if(i+pole.rzad>7 || i+pole.kolumna>7) break;
        else {
            r.na.rzad=i+pole.rzad; r.na.kolumna=i+pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0 || pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0 || pole.kolumna+i>7) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna+i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }

        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad+i>7 || pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad+i; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
}

void Wieza::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    for(int i=1; i<8; i++) {
        if(i+pole.rzad>7) break;
        else {
            r.na.rzad=i+pole.rzad; r.na.kolumna=pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.kolumna+i>7) break;
        else {
            r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna+i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
}

void Skoczek::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    if(pole.rzad+2<=7 && pole.kolumna+1<=7) {
        r.na.rzad=pole.rzad+2; r.na.kolumna=pole.kolumna+1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad+2<=7 && pole.kolumna-1>=0) {
        r.na.rzad=pole.rzad+2; r.na.kolumna=pole.kolumna-1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad-2>=0 && pole.kolumna+1<=7) {
        r.na.rzad=pole.rzad-2; r.na.kolumna=pole.kolumna+1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad-2>=0 && pole.kolumna-1>=0) {
        r.na.rzad=pole.rzad-2; r.na.kolumna=pole.kolumna-1;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad+1<=7 && pole.kolumna+2<=7) {
        r.na.rzad=pole.rzad+1; r.na.kolumna=pole.kolumna+2;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad+1<=7 && pole.kolumna-2>=0) {
        r.na.rzad=pole.rzad+1; r.na.kolumna=pole.kolumna-2;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad-1>=0 && pole.kolumna+2<=7) {
        r.na.rzad=pole.rzad-1; r.na.kolumna=pole.kolumna+2;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
    if(pole.rzad-1>=0 && pole.kolumna-2>=0) {
        r.na.rzad=pole.rzad-1; r.na.kolumna=pole.kolumna-2;
        if(zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ' || isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==poz.czyjRuch) {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);}
    }
}

void Hetman::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    for(int i=1; i<8; i++) {
        if(i+pole.rzad>7) break;
        else {
            r.na.rzad=i+pole.rzad; r.na.kolumna=pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.kolumna+i>7) break;
        else {
            r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna+i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(i+pole.rzad>7 || i+pole.kolumna>7) break;
        else {
            r.na.rzad=i+pole.rzad; r.na.kolumna=i+pole.kolumna;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0 || pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad-i<0 || pole.kolumna+i>7) break;
        else {
            r.na.rzad=pole.rzad-i; r.na.kolumna=pole.kolumna+i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
    for(int i=1; i<8; i++) {
        if(pole.rzad+i>7 || pole.kolumna-i<0) break;
        else {
            r.na.rzad=pole.rzad+i; r.na.kolumna=pole.kolumna-i;
            if(zwrocTypFigNaPolu(r.na, poz.listaFigur)!=' ') {
                if(poz.czyjRuch==0) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==true) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
                if(poz.czyjRuch==1) {
                    if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==false) break;
                    else {
                        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
                        break;
                    }
                }
            }
        }
        if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
    }
}

void Krol::zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz) {
    Ruch r; r.z.kolumna = pole.kolumna; r.z.rzad = pole.rzad;
    bool warunek = poz.czyjRuch;
    if(pole.rzad+1<=7) { r.na.rzad=pole.rzad+1; r.na.kolumna=pole.kolumna; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.rzad-1>=0) { r.na.rzad=pole.rzad-1; r.na.kolumna=pole.kolumna; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna+1<=7) { r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna+1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna-1>=0) { r.na.rzad=pole.rzad; r.na.kolumna=pole.kolumna-1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna+1<=7 && pole.rzad+1<=7) { r.na.rzad=pole.rzad+1; r.na.kolumna=pole.kolumna+1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna-1>=0 && pole.rzad+1<=7) { r.na.rzad=pole.rzad+1; r.na.kolumna=pole.kolumna-1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna-1>=0 && pole.rzad-1>=0) { r.na.rzad=pole.rzad-1; r.na.kolumna=pole.kolumna-1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    if(pole.kolumna+1<=7 && pole.rzad-1>=0) { r.na.rzad=pole.rzad-1; r.na.kolumna=pole.kolumna+1; if(isupper(zwrocTypFigNaPolu(r.na, poz.listaFigur))==warunek || zwrocTypFigNaPolu(r.na, poz.listaFigur)==' ') {if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);} }
    //roszady
    if(zwrocTypFigNaPolu(pole, poz.listaFigur)=='k') {
        Pole pDoSpr1=r.z, pDoSpr2=r.z, pDoSpr3=r.z, pDoSpr4=r.z, pDoSpr5=r.z, pDoSpr6=r.z, pDoSpr7=r.z;
        pDoSpr1.kolumna=0, pDoSpr2.kolumna=1, pDoSpr3.kolumna=2, pDoSpr4.kolumna=3, pDoSpr5.kolumna=5, pDoSpr6.kolumna=6, pDoSpr7.kolumna=7;
        //czarna krotka
        if(poz.rCzarnaKrotka==true) {
            if(zwrocTypFigNaPolu(pDoSpr5, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr6, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr7, poz.listaFigur)=='r') {
                 r.na.rzad=7; r.na.kolumna=6;
                 if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
             }
        }
        //czarna dluga
        if(poz.rCzarnaDluga==true) {
            if(zwrocTypFigNaPolu(pDoSpr1, poz.listaFigur)=='r'
                && zwrocTypFigNaPolu(pDoSpr2, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr3, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr4, poz.listaFigur)==' ') {
                 r.na.rzad=7; r.na.kolumna=2;
                 if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
             }
        }
    }
    if(zwrocTypFigNaPolu(pole, poz.listaFigur)=='K') {
        Pole pDoSpr1=r.z, pDoSpr2=r.z, pDoSpr3=r.z, pDoSpr4=r.z, pDoSpr5=r.z, pDoSpr6=r.z, pDoSpr7=r.z;
        pDoSpr1.kolumna=0, pDoSpr2.kolumna=1, pDoSpr3.kolumna=2, pDoSpr4.kolumna=3, pDoSpr5.kolumna=5, pDoSpr6.kolumna=6, pDoSpr7.kolumna=7;
        //biala krotka
        if(poz.rBialaKrotka==true) {
            if(zwrocTypFigNaPolu(pDoSpr5, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr6, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr7, poz.listaFigur)=='R') {
                 r.na.rzad=0; r.na.kolumna=6;
                 if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
             }
        }
        //biala dluga
        if(poz.rBialaDluga==true) {
            if(zwrocTypFigNaPolu(pDoSpr1, poz.listaFigur)=='R'
                && zwrocTypFigNaPolu(pDoSpr2, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr3, poz.listaFigur)==' '
                && zwrocTypFigNaPolu(pDoSpr4, poz.listaFigur)==' ') {
                 r.na.rzad=0; r.na.kolumna=2;
                 if(czyRuchLegalny(r, poz)) dodajRuch(r, lr);
             }
        }
    }
}
