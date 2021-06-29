/*! \file WejsciaWyjscia.h
    \brief Plik nagłówkowy zawierający funkcje obsługujące interfejs konsolowy
*/

#ifndef WEJSCIAWYJSCIA_H
#define WEJSCIAWYJSCIA_H

#include "Pozycja.h"

/**
 * @brief wczytajFEN Funkcja ta pobiera od użytkownika kod FEN, lub traktuje jego brak jako chęć wybrania pozycji początkowej
 * @return Zwraca kod FEN w formie zmiennej typu string
 */
string wczytajFEN();
/**
 * @brief wczytajRuch Funkcja ta pobiera od użytkownika ruch w formie ciągu znaków i zamienia na strukturę Ruch
 * @return Zwraca strukturę Ruch
 */
Ruch wczytajRuch();
/**
 * @brief rysujPozycje Funkcja ta rysuje w konsoli zadaną pozycję
 * @param poz Pozycja do narysowania
 */
void rysujPozycje(Pozycja poz);

#endif // WEJSCIAWYJSCIA_H
