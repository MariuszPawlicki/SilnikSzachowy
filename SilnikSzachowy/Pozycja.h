/*! \file Pozycja.h
    \brief Plik nagłówkowy zawierający deklarację struktur i funkcji niezbędnych do określenia pozycji szachowej i podejmowania na niej działań (wykonywania ruchów)
*/

#ifndef POZYCJA_H
#define POZYCJA_H

#include <iostream>

using namespace std;

/**
 * @brief Struktura Pole odpowiada przechowuje kordynaty pojedyńczego pola na szachownicy
 */
struct Pole {
    int kolumna;
    int rzad;
};

/**
 * @brief Struktura Ruch przechowuje pola z którego poruszamy figurę, pole na jakie poruszamy figurę, oraz ewentualną figurę na jaką chcemy wypromować piona w przypadku jego przejścia na ostatni rząd na szachownicy
 */
struct Ruch {
    Pole z;
    Pole na;
    char figPromocji = ' ';
};

/**
 * @brief Struktura Figura przechowuje typ figury jako znak np. 'P' - biały pion, lub 'b' - czarny goniec (b - bishop, mała litera - czarne); Struktura ta przechowuje też pole na jakim znajduję się ta figura
 */
struct Figura {
    char typ;
    Pole pole;
};

/**
 * @brief Struktura ListaFigur tworzy listę jednokierunkową przechowującą pokolei wszystkie figury
 */
struct ListaFigur {
    Figura figura;
    ListaFigur * nastepna;
};

/**
 * @brief Struktura Pozycja przechowuje listę figur w danej pozycji, a także inne informacje takie jak kto wykonuje ruch, jakie roszady są jeszcze dostępne itp.
 */
struct Pozycja {
    ListaFigur * listaFigur = new ListaFigur;
    bool czyjRuch; //0 - białe, 1 - czarne
    bool rBialaKrotka=0;
    bool rBialaDluga=0;
    bool rCzarnaKrotka=0;
    bool rCzarnaDluga=0;
    bool czyJestpBiciaWPrzelocie=false;
    Pole pBiciaWPrzelocie;
    int polRuchy;
};

/**
 * @brief dodajFigure Funkcja ta dodaje zadaną figurę na koniec listy figur
 * @param fig Zadana figura do dodania
 * @param lf Lista do której dodajemy figurę
 */
void dodajFigure(Figura fig, ListaFigur *&lf);
/**
 * @brief figuryNaTekst Funkcja ta wypełnia zadaną tablicę znaków 8x8 typami figur zawartymi w zadanej jednokierunkowej liście figur
 * @param str Zdana tablica znaków 8x8
 * @param lista Zadana jednokierunkowa lista figur
 */
void figuryNaTekst(char str[8][8], ListaFigur * lista);
/**
 * @brief FenNaPozycje Funkcja ta zamienia zadany jako ciąg znaków kod FEN na strukturę Pozycja
 * @param FEN Zadany kod FEN
 * @return Zwraca wypełnioną strukturę Pozycja
 */
Pozycja FenNaPozycje(string FEN);
/**
 * @brief znajdzIZamienPoleFig Funkcja ta znajduje zadaną figurę na liście figur i zmienia jej pole na takie jakie wskazuje zadany ruch
 * @param r Zadany ruch, który mówi o tym jaką figurę należy przesunąć (pole z), oraz na jakie pole (pole na)
 * @param l Zadana lista figur w której robiona jest zmiana
 */
void znajdzIZamienPoleFig(Ruch r, ListaFigur *& l);
/**
 * @brief usunFigNaPolu Funkcja ta usuwa figurę z zadanej listy figur na zadanym polu (używana w przypadku bicia figury)
 * @param p Pole z którego należy usunąć figurę
 * @param l Lista figur z której usuwana jest figura
 */
void usunFigNaPolu(Pole p, ListaFigur *& l);
/**
 * @brief wykonajRuch Funkcja ta wykonuje zadany ruch w zadanej pozycji
 * @param r Ruch do wykonania
 * @param poz Pozycja w której wykonywany jest ruch
 * @return Zwraca nowo powstałą pozycję po wykonaniu ruchu
 */
Pozycja wykonajRuch(Ruch r, Pozycja poz);
/**
 * @brief znajdzPoleKrola Funkcja ta znajduje pole z zadanej listy figur na którym jest król zadanego koloru
 * @param kolor Klor figury (króla)
 * @param lf Lista figur w której poszukiwana jest figura (król zadanego koloru)
 * @return Zwraca odpowiednio wypełnioną strukturę Pole
 */
Pole znajdzPoleKrola(bool kolor, ListaFigur * lf);
/**
 * @brief czySzach Funkcja ta sprawdza czy w zadanej pozycji padł szach
 * @param poz Zadana pozycja do sprawdzenia
 * @return Zwraca prawda gdy szach
 */
bool czySzach(Pozycja poz);
/**
 * @brief skopiujListeFigur Funkcja ta tworzy nową identyczną do zadanej listę figur (żeby przy przesłaniu do funkcji móc operować nową listą dynamiczną)
 * @param lf Lista do skopiowania
 * @param nowalf Pusta lista figur do której kopiowana jest zawartość wcześniej zadanej listy
 */
void skopiujListeFigur(ListaFigur * lf, ListaFigur *& nowalf);
/**
 * @brief czyRuchLegalny Funkcja ta sprawdza czy wykonanie zadanego ruchu w zadanej pozycji jest legalne (chodzi tu głównie o ruchy "pod szacha" itp)
 * @param r Ruch do wykonania
 * @param poz Pozycja w której ruch ma zostać wykonany
 * @return Zwraca prawda gdy ruch legalny
 */
bool czyRuchLegalny(Ruch r, Pozycja poz);
/**
 * @brief czyMat Funkcja ta sprawdza czy w zadanej pozycji doszło do mata
 * @param poz Pozycja do sprawdzenia
 * @return Zwraca prawda gdy mat
 */
bool czyMat(Pozycja poz);
/**
 * @brief czyPat Funkcja ta sprawdza czy w zadanej pozycji doszło do remisu (pata)
 * @param poz Pozycja do sprawdzenia
 * @return Zwraca prawda gdy remis
 */
bool czyPat(Pozycja poz);

#endif // POZYCJA_H
