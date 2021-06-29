/*! \file Figury.h
    \brief Plik nagłówkowy zawierający deklaracje wszystkich figur (struktur)
*/

#ifndef FIGURY_H
#define FIGURY_H

#include "Pozycja.h"
#include "SelekcjaRuchow.h"
/**
 * @brief Struktura PionB (biały pion) jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct PionB {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura PionC (czarny pion) jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct PionC {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura Goniec jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct Goniec {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura Skoczek jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct Skoczek {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura Wieza (wieża) jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct Wieza {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura Hetman jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct Hetman {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};
/**
 * @brief Struktura Krol (król) jest używana w jednokierunkowej liście figur. Zawiera pole na jakiej stoi ta figura oraz funkcję która zwraca listę pól na jakie może się poruszyć
 */
struct Krol {
    Pole pole;
    void zwrocKandydatowNaPola(ListaRuchow *&lr, Pozycja poz);
};

#endif // FIGURY_H
