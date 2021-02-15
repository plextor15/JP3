/*
	Opis: Manipulatory do kolorowania tekstu w konsoli, mozliwosc przywrocenia ustawien domyslnych
		  z uzyciem obiektu klasy Edit

	Adam Porembinski 16.11.2020

	29.11.2020	tworzenie manipulatorow bezparametrowych do kolorow, debug
	03.12.2020  tworzenie manipulatora SetColor, debug
	01.02.2021	dodanie includa z klasa Edit
*/

#ifndef CCOLOR_H
#define CCOLOR_H

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "edit.h"

std::ostream& red(std::ostream& out);
std::ostream& green(std::ostream& out);
std::ostream& blue(std::ostream& out);
std::ostream& white(std::ostream& out);
std::ostream& bold(std::ostream& out);

std::ostream& defcolor(std::ostream& out);


void SettingKolor(std::ios_base& os, int kolor);
std::_Smanip<int> __cdecl SetColor(int kolorek);

#endif	// !CCOLOR_H