/*
    Opis: Manipulatory do kolorowania tekstu w konsoli, mozliwosc przywrocenia ustawien domyslnych
		  z uzyciem obiektu klasy Edit

    Adam Porembinski 29.11.2020

    29.11.2020	tworzenie manipulatorow bezparametrowych do kolorow, debug
    03.12.2020  tworzenie manipulatora SetColor, debug
    01.02.2021  poprawienie metody defcolor
*/

#include "ccolor.h"

std::ostream& red(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    return out;
}

std::ostream& green(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    return out;
}

std::ostream& blue(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    return out;
}

std::ostream& white(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return out;
}

std::ostream& bold(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return out;
}

std::ostream& defcolor(std::ostream& out)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Edit::getDefaultWord());
    return out;
}

//na podastawie
//https://docs.microsoft.com/en-us/cpp/standard-library/output-stream-manipulators-with-one-argument-int-or-long?view=msvc-160
void SettingKolor(std::ios_base& os, int kolor)
{
    std::ostream* out = dynamic_cast<std::ostream*>(&os);
    (*out) << SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolor);
    return;
}
std::_Smanip<int> __cdecl SetColor(int kolorek)
{
    return (std::_Smanip<int>(&SettingKolor, kolorek));
}