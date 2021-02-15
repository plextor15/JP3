/*
*	Klasa: Console
*	Autor:	Adam Porembinski
*	Opis: Potrafi wypisywac do konsoli morsem. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	21.01.2021	mozliwosc pisania na ekran
*	27.01.2021	zlikwidowanie parametru czasu
*/

#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include "morse.h"

class Console
{
public:
	struct consoleParam
	{
		char kropka;
		char kreska;
	};
private:
	consoleParam parametry;

public:
	Console();
	Console(char kropka, char kreska);
	~Console();
	Console(const Console& c);

	void wypisywanie(std::string doWypisania);
	consoleParam Get_parametry();
	void Set_parametry(char kropka, char kreska);

	const Console& operator = (const Console& drugi);
};

#endif // !CONSOLE_H