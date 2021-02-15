/*
    Klasa "macierz"
    Opis:   Obiektem jest macierz 2x2, wraz z mozliwoscia wpisywania do niej pojedynczo wartosci.
            Nie ma konstruktora parametrowego, a wszystkie nowo stworzone macierze maja wszedzie wartosci 0.

    Autor: Adam Porembinski
    Data utworzenia: 19.10.2020

    22.10 - konstruktory, desktruktory, funkcja set i tablica 2D
    23.10 - operator *
    01.11 - operator ==, zmiana koncepcji z tablicy na vector
    04.11 - poprawienie konstruktora kopiujacego, komentarze
*/

#ifndef MACIERZ_H
#define MACIERZ_H

#include <vector>

class macierz {
public:
    macierz();//konstruktor bezparam
    macierz(const macierz& m); //konstruktor kopiujacy
    ~macierz();//desktruktor

    void set(int x, int y, float w);//wiersz x, kolumna y
//    void Debug();//wypisuje  wartosci w macierzy

    //operatory
    /*macierz& operator=(const macierz& m) {
        tablicaMacierzy = m.tablicaMacierzy;
        return *this;
    }*/
    friend macierz operator*(const macierz& m1, const macierz& m2);
    friend bool operator == (macierz const& a, macierz const& b);

private:
    std::vector<std::vector<float>> tablicaMacierzy; //zawartosc macierzy  w postaci vector vectorow
};

#endif // MACIERZ_H