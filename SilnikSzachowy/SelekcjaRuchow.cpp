/*! \file SelekcjaRuchow.cpp
    \brief Plik źródłowy zawierający definicje struktur i funkcji mających na celu dokonania selekcji ruchów możliwych do wykonania w danej pozycji
*/

#include <stdlib.h>
#include "SelekcjaRuchow.h"
#include "Figury.h"

void dodajRuch(Ruch r, ListaRuchow *&l) {
    if(l->next==nullptr) {
        ListaRuchow * temp = new ListaRuchow;
        temp->ruch = r;
        temp->next = nullptr;
        l->next = temp;
    } else {
        dodajRuch(r, l->next);
    }
}

void wypiszLR(ListaRuchow * lr) {
    if(lr!=nullptr) {
        cout<<(char)(lr->ruch.z.kolumna+97)<<lr->ruch.z.rzad+1<<(char)(lr->ruch.na.kolumna+97)<<lr->ruch.na.rzad+1<<endl;
        wypiszLR(lr->next);
    }
}

void dodajKR(ListaFigur * lf, ListaRuchow *& lr, bool czyjRuch, Pozycja poz) {
    if(lf!=nullptr) {
        if(czyjRuch==0) {
            if(lf->figura.typ=='P') {
                PionB pb; pb.pole=lf->figura.pole;
                pb.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='B') {
                Goniec g; g.pole=lf->figura.pole;
                g.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='R') {
                Wieza w; w.pole=lf->figura.pole;
                w.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='N') {
                Skoczek s; s.pole=lf->figura.pole;
                s.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='Q') {
                Hetman h; h.pole=lf->figura.pole;
                h.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='K') {
                Krol k; k.pole=lf->figura.pole;
                k.zwrocKandydatowNaPola(lr, poz);
            }
            dodajKR(lf->nastepna, lr, czyjRuch, poz);
        } else {
            if(lf->figura.typ=='p') {
                PionC pc; pc.pole=lf->figura.pole;
                pc.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='b') {
                Goniec g; g.pole=lf->figura.pole;
                g.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='r') {
                Wieza w; w.pole=lf->figura.pole;
                w.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='n') {
                Skoczek s; s.pole=lf->figura.pole;
                s.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='q') {
                Hetman h; h.pole=lf->figura.pole;
                h.zwrocKandydatowNaPola(lr, poz);
            }
            if(lf->figura.typ=='k') {
                Krol k; k.pole=lf->figura.pole;
                k.zwrocKandydatowNaPola(lr, poz);
            }
            dodajKR(lf->nastepna, lr, czyjRuch, poz);
        }
    }
}

ListaRuchow * wczytajWszystkieKNaR(Pozycja poz) {
    ListaRuchow * l = new ListaRuchow;
    l->next=nullptr;
    dodajKR(poz.listaFigur, l, poz.czyjRuch, poz);
    l=l->next;
    return l;
}

char zwrocTypFigNaPolu(Pole p, ListaFigur * l) {
    if(l!=nullptr) {
        if(l->figura.pole.kolumna==p.kolumna && l->figura.pole.rzad==p.rzad) return l->figura.typ;
        zwrocTypFigNaPolu(p, l->nastepna);
    } else return ' ';
}

bool czyRuchJestNaLiscie(Ruch r, ListaRuchow * lr) {
    if(lr!=nullptr) {
        if(lr->ruch.z.kolumna==r.z.kolumna && lr->ruch.z.rzad==r.z.rzad && lr->ruch.na.kolumna==r.na.kolumna && lr->ruch.na.rzad==r.na.rzad) return true;
        else return czyRuchJestNaLiscie(r, lr->next);
    } else return false;
}
