/*
    Klasa "macierz"
	Opis:   Obiektem jest macierz 2x2, wraz z mozliwoscia wpisywania do niej pojedynczo wartosci.
            Nie ma konstruktora parametrowego, a wszystkie nowo stworzone macierze maja wszedzie wartosci 0.

	Autor: Adam Porembinski
	Data utworzenia: 19.10.2020
	
    22.10 - konstruktory, desktruktory, set
    23.10 - operator * (zeby macierze sie wlasciwie mnozyly)
    01.11 - operator ==, debug, zmiana koncepcji
    04.11 - poprawienie konstruktora kopiujacego, polepszenie destruktora, komentarze
    05.11 - debug, czyszczenie
*/

#include <iostream>
#include <vector>
#include "macierz.h"

macierz::macierz()
{
    tablicaMacierzy.resize(2, std::vector<float>(2, 0)); //ustawiamy 2 rzedy po 2 kolumny, wszedzie wartosc 0
}

macierz::macierz(const macierz& m) //konstruktor kopiujacy
{
    this->tablicaMacierzy = m.tablicaMacierzy;
}

macierz::~macierz()
{
    tablicaMacierzy.clear(); //usuwa wszystkie elementy
    tablicaMacierzy.shrink_to_fit(); //zmienia rozmiar tablicy na 0 zeby nie zajmowala pamieci
}

void macierz::set(int x, int y, float w)
{
    if (x == 0 || x == 1 || y == 0 || y == 1) //x y musza byc albo 0 albo 1
        tablicaMacierzy[x][y] = w;
    else
        std::clog << "Jest to macierz 2x2, zly x albo y!\n";

    return;
}
/*
void macierz::Debug()
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::clog << tablicaMacierzy[i][j] << "  ";
        }
        std::clog << std::endl;
    }
    std::clog << std::endl;
}
*/
macierz operator * (const macierz& m1, const macierz& m2)
{
    macierz Wynik;
    //mnozenie macierzy
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            Wynik.tablicaMacierzy[i][j] = (m1.tablicaMacierzy[i][0] * m2.tablicaMacierzy[0][j]) + (m1.tablicaMacierzy[i][1] * m2.tablicaMacierzy[1][j]);//wzor na mnozenie
        }
    }

    return Wynik;
}

bool operator == (macierz const& a, macierz const& b)
{
    bool wynik = true; //zmienna kontrolna
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (a.tablicaMacierzy[i][j] != b.tablicaMacierzy[i][j]) {
                wynik = false; //jesli sie roznia w ktores wartosci to zmienna kontrolna jest ustawiana na false
            }
        }
    }
    return wynik;
}