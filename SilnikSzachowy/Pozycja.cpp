/*! \file Pozycja.cpp
    \brief Plik źródłowy zawierający definicje struktur i funkcji niezbędnych do określenia pozycji szachowej i podejmowania na niej działań (wykonywania ruchów)
*/

#include "Pozycja.h"
#include "SelekcjaRuchow.h"
#include "WejsciaWyjscia.h"

void dodajFigure(Figura fig, ListaFigur *&lf) {
    if(lf->nastepna==nullptr) {
        ListaFigur * temp = new ListaFigur;
        temp->figura=fig;
        temp->nastepna=nullptr;
        lf->nastepna=temp;
    } else {
        dodajFigure(fig, lf->nastepna);
    }
}

void figuryNaTekst(char str[8][8], ListaFigur * lista) {
    if(lista!=nullptr) {
        str[lista->figura.pole.rzad][lista->figura.pole.kolumna] = lista->figura.typ;
        figuryNaTekst(str, lista->nastepna);
    }
}

Pozycja FenNaPozycje(string FEN) {
    Pozycja poz;
    char str[64];
    int i=0, j=0;
    while(true) {
        if((int)FEN[i]>=48 && (int)FEN[i]<=57) {
            for(int k=0;k<(int)FEN[i]-48;k++) {
                str[j] = ' ';
                j++;
            }
            i++;
        }
        else if(FEN[i]=='/') {
            i++;
        }
        else if(FEN[i]==' ') {
            i++;
            break;
        }
        else {
            str[j]=FEN[i];
            j++; i++;
        }
    }

    bool pierwsza = true;
    for(int w=7;w>=0;w--) {
        for(int k=0;k<8;k++) {
            if(str[(7-w)*8 + k]!=' ') {
                Figura temp;
                temp.typ=str[(7-w)*8 + k];
                temp.pole.rzad=w;
                temp.pole.kolumna=k;
                if(pierwsza) {
                    poz.listaFigur->figura=temp;
                    poz.listaFigur->nastepna=nullptr;
                    pierwsza = false;
                } else {
                    dodajFigure(temp, poz.listaFigur);
                }
            }
        }
    }

    if(FEN[i]=='w') {
        poz.czyjRuch=0;
        i+=2;
    } else if(FEN[i]=='b') {
        poz.czyjRuch=1;
        i+=2;
    }

    for(int k=0;k<5;k++) {
        if(FEN[i]==' ') {
            i++;
            break;
        } else if(FEN[i]=='K') {
            poz.rBialaKrotka=1;
            i++;
        } else if(FEN[i]=='Q') {
            poz.rBialaDluga=1;
            i++;
        } else if(FEN[i]=='k') {
            poz.rCzarnaKrotka=1;
            i++;
        } else if(FEN[i]=='q') {
            poz.rCzarnaDluga=1;
            i++;
        }
    }

    if(FEN[i]!='-') {
        poz.pBiciaWPrzelocie.rzad=((int)FEN[i])-97;
        poz.pBiciaWPrzelocie.kolumna=((int)FEN[i+1])-49;
        i+=3;
    } else {
        i+=2;
    }

    if(FEN[i+1]!=' ') {
        poz.polRuchy=(((int)FEN[i])-48)*10 + ((int)FEN[i+1])-48;
    } else {
        poz.polRuchy=((int)FEN[i])-48;
    }

    return poz;
}

void znajdzIZamienPoleFig(Ruch r, ListaFigur *& l) {
    if(l!=nullptr) {
        if(l->figura.pole.kolumna==r.z.kolumna && l->figura.pole.rzad==r.z.rzad) l->figura.pole=r.na;
        znajdzIZamienPoleFig(r, l->nastepna);
    }
}

void znajdzIZamienTypFig(Ruch r, ListaFigur *& l) {
    if(l!=nullptr) {
        if(l->figura.pole.kolumna==r.z.kolumna && l->figura.pole.rzad==r.z.rzad) l->figura.typ=r.figPromocji;
        znajdzIZamienTypFig(r, l->nastepna);
    }
}

void usunFigNaPolu(Pole p, ListaFigur *& l) {
    if(l!=nullptr) {
        if(l->figura.pole.kolumna==p.kolumna && l->figura.pole.rzad==p.rzad) l=l->nastepna;
        usunFigNaPolu(p, l->nastepna);
    }
}

Pozycja wykonajRuch(Ruch r, Pozycja poz) {
    Pozycja p = poz;
    p.czyJestpBiciaWPrzelocie=false;
    //promocje pionów
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='P' && r.na.rzad==7) {
        if(r.figPromocji==' ') r.figPromocji='Q';
        znajdzIZamienTypFig(r, p.listaFigur);
        usunFigNaPolu(r.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='p' && r.na.rzad==0) {
        if(r.figPromocji==' ') r.figPromocji='q';
        znajdzIZamienTypFig(r, p.listaFigur);
        usunFigNaPolu(r.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //roszady
    //biała długa
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='K' && r.z.rzad==0 && r.z.kolumna==4 && r.na.kolumna==2) {
        Ruch rDlaWiezy; rDlaWiezy.z.rzad=0; rDlaWiezy.z.kolumna=0; rDlaWiezy.na.rzad=0; rDlaWiezy.na.kolumna=3;
        usunFigNaPolu(r.na, p.listaFigur);
        usunFigNaPolu(rDlaWiezy.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        znajdzIZamienPoleFig(rDlaWiezy, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //biala krótka
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='K' && r.z.rzad==0 && r.z.kolumna==4 && r.na.kolumna==6) {
        Ruch rDlaWiezy; rDlaWiezy.z.rzad=0; rDlaWiezy.z.kolumna=7; rDlaWiezy.na.rzad=0; rDlaWiezy.na.kolumna=5;
        usunFigNaPolu(r.na, p.listaFigur);
        usunFigNaPolu(rDlaWiezy.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        znajdzIZamienPoleFig(rDlaWiezy, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //czarna długa
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='k' && r.z.rzad==7 && r.z.kolumna==4 && r.na.kolumna==2) {
        Ruch rDlaWiezy; rDlaWiezy.z.rzad=7; rDlaWiezy.z.kolumna=0; rDlaWiezy.na.rzad=7; rDlaWiezy.na.kolumna=3;
        usunFigNaPolu(r.na, p.listaFigur);
        usunFigNaPolu(rDlaWiezy.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        znajdzIZamienPoleFig(rDlaWiezy, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //czarna krótka
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='k' && r.z.rzad==7 && r.z.kolumna==4 && r.na.kolumna==6) {
        Ruch rDlaWiezy; rDlaWiezy.z.rzad=7; rDlaWiezy.z.kolumna=7; rDlaWiezy.na.rzad=7; rDlaWiezy.na.kolumna=5;
        usunFigNaPolu(r.na, p.listaFigur);
        usunFigNaPolu(rDlaWiezy.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        znajdzIZamienPoleFig(rDlaWiezy, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //ruch pionem o 2 pola
    if(zwrocTypFigNaPolu(r.z, p.listaFigur)=='P' && r.na.rzad-r.z.rzad==2) {
        usunFigNaPolu(r.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        p.czyJestpBiciaWPrzelocie=true;
        p.pBiciaWPrzelocie.kolumna=r.na.kolumna;
        p.pBiciaWPrzelocie.rzad=r.na.rzad-1;
        return p;
    }
    if(zwrocTypFigNaPolu(r.z, p.listaFigur)=='p' && r.z.rzad-r.na.rzad==2) {
        usunFigNaPolu(r.na, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        p.czyJestpBiciaWPrzelocie=true;
        p.pBiciaWPrzelocie.kolumna=r.na.kolumna;
        p.pBiciaWPrzelocie.rzad=r.na.rzad+1;
        return p;
    }
    //bicie w przelocie
    if(poz.czyJestpBiciaWPrzelocie==true && poz.pBiciaWPrzelocie.rzad==r.na.rzad && poz.pBiciaWPrzelocie.kolumna==r.na.kolumna && (zwrocTypFigNaPolu(r.z, poz.listaFigur)=='p' || zwrocTypFigNaPolu(r.z, poz.listaFigur)=='P')) {
        Pole poleDoUsun = r.na;
        if(p.czyjRuch==false) poleDoUsun.rzad--;
        else poleDoUsun.rzad++;
        usunFigNaPolu(poleDoUsun, p.listaFigur);
        znajdzIZamienPoleFig(r, p.listaFigur);
        p.czyjRuch=!p.czyjRuch;
        return p;
    }
    //zwykłych ruch, lub bicie
    usunFigNaPolu(r.na, p.listaFigur);
    znajdzIZamienPoleFig(r, p.listaFigur);
    p.czyjRuch=!p.czyjRuch;
    return p;
}

Pole znajdzPoleKrola(bool kolor, ListaFigur * lf) {
    char krol;
    if(kolor==false) krol='K';
    else krol='k';
    Pole p;
    p.rzad=-1;
    p.kolumna=-1;
    if(lf!=nullptr) {
        if(lf->figura.typ==krol) return lf->figura.pole;
        else return znajdzPoleKrola(kolor, lf->nastepna);
    } else return p;
}

bool czySzach(Pozycja poz) {
    Pole krol;
    if(poz.czyjRuch==false) {
        krol = znajdzPoleKrola(false, poz.listaFigur); Pole na;
        //czy pod szachem piona
        na.kolumna=krol.kolumna-1; na.rzad=krol.rzad+1;
        if(na.rzad>=0 && na.rzad<=7 && na.kolumna>=0 && na.kolumna<=7 && zwrocTypFigNaPolu(na, poz.listaFigur)=='p') return true;
        na.kolumna=krol.kolumna+1; na.rzad=krol.rzad+1;
        if(na.rzad>=0 && na.rzad<=7 && na.kolumna>=0 && na.kolumna<=7 && zwrocTypFigNaPolu(na, poz.listaFigur)=='p') return true;
        //czy pod szachem wiezy, lub hetmana pionowo w gore
        for(int i=1;i<=7;i++) {
            na.rzad=i+krol.rzad; na.kolumna=krol.kolumna;
            if(krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='r' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='r') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana pionowo w dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna;
            if(krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='r' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='r') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana poziomo w prawo
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='r' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='r') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana poziomo w lewo
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='r' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='r') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w prawo-gora
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad+i; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i>7 || krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='b' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='b') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w lewo-gora
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad+i; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='b' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='b') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w lewo-dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='b' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='b') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w prawo-dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i<0 || krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='b' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='b') {
                 return true;
            }
        }
        //czy pod szachem skoczka
        for(int x=-2; x<=2; x++) {
            if(x!=0) {
                if(x==2 || x==-2) {
                    for(int y=-1; y<=1; y+=2) {
                        na.rzad=krol.rzad+y; na.kolumna=krol.kolumna+x;
                        if(zwrocTypFigNaPolu(na, poz.listaFigur)=='n') return true;
                    }
                }
                if(x==1 || x==-1) {
                    for(int y=-2; y<=2; y+=4) {
                        na.rzad=krol.rzad+y; na.kolumna=krol.kolumna+x;
                        if(zwrocTypFigNaPolu(na, poz.listaFigur)=='n') return true;
                    }
                }
            }
        }

    } else {
        krol = znajdzPoleKrola(true, poz.listaFigur); Pole na;
        //czy pod szachem piona
        na.kolumna=krol.kolumna-1; na.rzad=krol.rzad-1;
        if(na.rzad>=0 && na.rzad<=7 && na.kolumna>=0 && na.kolumna<=7 && zwrocTypFigNaPolu(na, poz.listaFigur)=='P') return true;
        na.kolumna=krol.kolumna+1; na.rzad=krol.rzad-1;
        if(na.rzad>=0 && na.rzad<=7 && na.kolumna>=0 && na.kolumna<=7 && zwrocTypFigNaPolu(na, poz.listaFigur)=='P') return true;
        //czy pod szachem wiezy, lub hetmana pionowo w gore
        for(int i=1;i<=7;i++) {
            na.rzad=i+krol.rzad; na.kolumna=krol.kolumna;
            if(krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='R' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='R') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana pionowo w dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna;
            if(krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='R' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='R') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana poziomo w prawo
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='R' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='R') {
                 return true;
            }
        }
        //czy pod szachem wiezy, lub hetmana poziomo w lewo
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='R' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='R') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w prawo-gora
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad+i; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i>7 || krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='B' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='B') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w lewo-gora
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad+i; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || krol.rzad+i>7 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='B' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='B') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w lewo-dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna-i;
            if(krol.kolumna-i<0 || krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='B' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='B') {
                 return true;
            }
        }
        //czy pod szachem gonca, lub hetmana w prawo-dol
        for(int i=1;i<=7;i++) {
            na.rzad=krol.rzad-i; na.kolumna=krol.kolumna+i;
            if(krol.kolumna+i>7 || krol.rzad-i<0 || (zwrocTypFigNaPolu(na, poz.listaFigur)!='Q' && zwrocTypFigNaPolu(na, poz.listaFigur)!='B' && zwrocTypFigNaPolu(na, poz.listaFigur)!=' ')) {
                break;
            } else if(zwrocTypFigNaPolu(na, poz.listaFigur)=='Q' || zwrocTypFigNaPolu(na, poz.listaFigur)=='B') {
                 return true;
            }
        }
        //czy pod szachem skoczka
        for(int x=-2; x<=2; x++) {
            if(x!=0) {
                if(x==2 || x==-2) {
                    for(int y=-1; y<=1; y+=2) {
                        na.rzad=krol.rzad+y; na.kolumna=krol.kolumna+x;
                        if(zwrocTypFigNaPolu(na, poz.listaFigur)=='N') return true;
                    }
                }
                if(x==1 || x==-1) {
                    for(int y=-2; y<=2; y+=4) {
                        na.rzad=krol.rzad+y; na.kolumna=krol.kolumna+x;
                        if(zwrocTypFigNaPolu(na, poz.listaFigur)=='N') return true;
                    }
                }
            }
        }
    }
    return false;
}

void skopiujListeFigur(ListaFigur * lf, ListaFigur *& nowalf) {
    if(lf!=nullptr) {
        ListaFigur * temp = new ListaFigur;
        temp->figura=lf->figura;
        temp->nastepna=nullptr;
        nowalf=temp;
        skopiujListeFigur(lf->nastepna,nowalf->nastepna);
    }
}

bool czyRuchLegalny(Ruch r, Pozycja poz) {   
    //sprawdzanie roszad
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='K' && r.z.kolumna==4 && r.na.kolumna==2) {
        Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
        nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
        skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
        Ruch rDoSprawdzenia; rDoSprawdzenia.z = r.z; rDoSprawdzenia.na.rzad=0; rDoSprawdzenia.na.kolumna=3;
        nPoz = wykonajRuch(rDoSprawdzenia, nPoz);
        nPoz.czyjRuch=!nPoz.czyjRuch;
        if(czySzach(nPoz)) return false;
        return true;
    }
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='K' && r.z.kolumna==4 && r.na.kolumna==6) {
        Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
        nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
        skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
        Ruch rDoSprawdzenia; rDoSprawdzenia.z = r.z; rDoSprawdzenia.na.rzad=0; rDoSprawdzenia.na.kolumna=5;
        nPoz = wykonajRuch(rDoSprawdzenia, nPoz);
        nPoz.czyjRuch=!nPoz.czyjRuch;
        if(czySzach(nPoz)) return false;
        return true;
    }
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='k' && r.z.kolumna==4 && r.na.kolumna==2) {
        Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
        nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
        skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
        Ruch rDoSprawdzenia; rDoSprawdzenia.z = r.z; rDoSprawdzenia.na.rzad=7; rDoSprawdzenia.na.kolumna=3;
        nPoz = wykonajRuch(rDoSprawdzenia, nPoz);
        nPoz.czyjRuch=!nPoz.czyjRuch;
        if(czySzach(nPoz)) return false;
        return true;
    }
    if(zwrocTypFigNaPolu(r.z, poz.listaFigur)=='k' && r.z.kolumna==4 && r.na.kolumna==6) {
        Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
        nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
        skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
        Ruch rDoSprawdzenia; rDoSprawdzenia.z = r.z; rDoSprawdzenia.na.rzad=7; rDoSprawdzenia.na.kolumna=5;
        nPoz = wykonajRuch(rDoSprawdzenia, nPoz);
        nPoz.czyjRuch=!nPoz.czyjRuch;
        if(czySzach(nPoz)) return false;
        return true;
    }
    //sprawdzanie czy nie ma próby wykonania ruchu "pod szacha"
    Pozycja nPoz; nPoz.czyjRuch=poz.czyjRuch; nPoz.pBiciaWPrzelocie=poz.pBiciaWPrzelocie; nPoz.polRuchy=poz.polRuchy;
    nPoz.rBialaDluga=poz.rBialaDluga; nPoz.rBialaKrotka=poz.rBialaKrotka; nPoz.rCzarnaDluga=poz.rCzarnaDluga; nPoz.rCzarnaKrotka=poz.rCzarnaKrotka;
    skopiujListeFigur(poz.listaFigur, nPoz.listaFigur);
    nPoz = wykonajRuch(r, nPoz);
    nPoz.czyjRuch=!nPoz.czyjRuch;
    if(czySzach(nPoz)) return false;
    return true;
}

bool czyMat(Pozycja poz) {
    if(czySzach(poz) && wczytajWszystkieKNaR(poz)==nullptr) return true;
    else return false;
}

bool czyPat(Pozycja poz) {
    if(!czySzach(poz) && wczytajWszystkieKNaR(poz)==nullptr) return true;
    else return false;
}
