/*! \file SelekcjaRuchow.h
    \brief Plik nagłówkowy zawierający deklarację struktur i funkcji mających na celu dokonania selekcji ruchów możliwych do wykonania w danej pozycji
*/

#ifndef SELEKCJARUCHOW_H
#define SELEKCJARUCHOW_H

#include "Pozycja.h"

/**
 * @brief Struktura ListaFigur jest jednokierunkową listą dynamiczną zawierającą możliwe do wykonania ruchy pobrane od figur znajdujących się na planszy
 */
struct ListaRuchow {
    Ruch ruch;
    ListaRuchow * next;
};

/**
 * @brief dodajRuch Funkcja ta dodaje zadany ruch do wskazanej listy ruchów
 * @param r Ruch do dodania
 * @param l Lista do której dodajemy ruch
 */
void dodajRuch(Ruch r, ListaRuchow *&l);
/**
 * @brief wypiszLR Funkcja ta wypisuje ruchy zawarte w zadanej liście ruchów (są to wszystkie możliwe ruchy w pozcyji na której podstawie powstała lista)
 * @param lr Lista ruchów do wypisania
 */
void wypiszLR(ListaRuchow * lr);
/**
 * @brief dodajKR Funkcja ta w zasadzie chyba robiła to co funkcja dodajRuch i chyba już jej nie używam, ale boję się ją usunąć
 * @param lf ...
 * @param lr ...
 * @param czyjRuch Nie wiem po co ta zmienna miała by tu wogóle być
 */
void dodajKR(ListaFigur * lf, ListaRuchow *& lr, bool czyjRuch);
/**
 * @brief wczytajWszystkieKNaR Funkcja ta rząda zwrócenia od wszystkich figur w zadanej pozycji ruchów które mogą one wykonać, a następnie łączy jej w jedną listę
 * @param poz Pozycja w której szukamy ruchów
 * @return Zwraca listę ruchów możliwych do wykonania w danej pozycji
 */
ListaRuchow * wczytajWszystkieKNaR(Pozycja poz);
/**
 * @brief zwrocTypFigNaPolu Funkcja ta zwraca typ figury (jej oznaczenie w postaci znaku) na zadanym polu w zadanej liście figur
 * @param p Pole na którym interesuje nas figura
 * @param l Lista figur w której poszukujemy
 * @return Zwraca oznaczenie poszukiwanej figury w formie odpowiadającego jej znaku
 */
char zwrocTypFigNaPolu(Pole p, ListaFigur * l);
/**
 * @brief czyRuchJestNaLiscie Funkcja ta sprawdza czy zadany ruch jest na zadanej liście możliwych do wykonania ruchów
 * @param r Ruch do sprawdzenia
 * @param lr Lista ruchów w której go poszukujemy
 * @return Prawda jeśli ruch jest na liście
 */
bool czyRuchJestNaLiscie(Ruch r, ListaRuchow * lr);

#endif // SELEKCJARUCHOW_H
