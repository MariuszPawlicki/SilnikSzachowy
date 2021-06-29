/*! \file OcenaPozycji.h
    \brief Plik nagłówkowy zawierający deklarację funkcji przeprowadzającej ocenę statyczną, oraz jej funkcji pomocniczej
*/

#ifndef OCENAPOZYCJI_H
#define OCENAPOZYCJI_H

#include "Pozycja.h"

/**
 * @brief Struktura wynikZliczania służy do zwrócenia wyniku funkcji zliczLF, która potrzebuje zwrócić więcej niż jedną zmienną.
 */
struct wynikZliczania {
    float roznica;
    float suma;
};

/**
 * @brief Funkcja zliczLF służy do policzenia sumy wag wszystkich figur na szachownicy
 * @param lf Lista zliczanych figur (szachownica)
 * @param startowa1 Startowa suma wag przesyłana rekursywnie. Przy tym parametrze czarne mają przeciwny znak do białych (-)
 * @param startowa2Startowa suma wag przesyłana rekursywnie. Przy tym parametrze czarne mają taki sam znak co białe (+)
 * @return
 */
wynikZliczania zliczLF(ListaFigur * lf, float startowa1, int startowa2);

/**
 * @brief ocenaPozycji Funkcja ocenaPozycji służy do przeprowadzenia statycznej oceny pozycji poprzez wywołanie zliczania figur wraz z ich wagami, a następnie przeprowadzenia rachunku opartego na łącznej ilości figur na planszy (im mniej figur na planszy tym strona mająca więcej materiału odczuwa to jako większą przewagę)
 * @param poz Zadana pozycja do przeprowadzenia oceny statycznej
 * @return Zwraca wynik statycznej oceny jako liczbę zmiennoprzecinkową
 */
float ocenaPozycji(Pozycja poz);

#endif // OCENAPOZYCJI_H
