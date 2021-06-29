/*! \file MinMax.h
    \brief Plik nagłówkowy zawierający deklarację najważniejszej funkcji w programie (MinMax)
*/

#ifndef MINMAX_H
#define MINMAX_H

#include "Pozycja.h"
#include "SelekcjaRuchow.h"

/**
 * @brief Struktura WynikMinMaxu służy do zwrócenia wyniku funkcji MinMax, która potrzebuje zwrócić więcej niż jedną zmienną.
 */
struct WynikMinMaxu{
    float ocena;
    Ruch ruch;
};

/**
 * @brief Funkcja MinMax jest najważniejszą funkcją programu znajdującą najlepszy do wykonania ruch w danej pozycji.
 * @param poz Zadana pozycja
 * @param glebokosc Głębokość na jakiej MinMax zakończy poszukiwania i przeprowadzi ocenę statyczną
 * @param alfa Parametr służący do odrzucenia niepotrzebnych rozgałęzień (alfa-beta pruning) dla strony maksymalizującej (koloru białego)
 * @param beta Parametr służący do odrzucenia niepotrzebnych rozgałęzień (alfa-beta pruning) dla strony minimalizującej (koloru czarnego)
 * @return Zwraca najlepszy ruch, oraz jego ocenę w formie struktury WynikMinMaxu
 */
WynikMinMaxu MinMax(Pozycja poz, int glebokosc, float alfa=-1000, float beta=1000);

#endif // MINMAX_H
