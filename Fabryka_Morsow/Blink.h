/*
*	Klasa: Blink
*	Autor:	Adam Porembinski
*	Opis: Potrafi migac dioda w kodzie mors'a. Owa dioda to znak kursora migajacy w konsoli. Na razie do uzycia z klasa morseFactory.
* 
*	20.01.2021	stworzenie klasy
*	23.01.2021	dodanie potrzebnych funkcji, testowanie kursora jako diody
*	30.01.2021	cleanup
*/

#pragma once
#ifndef BLINK_H
#define BLINK_H

#include <windows.h>
#include <iostream>	//zeby bylo widac diode
#include "morse.h"

class Blink
{
public:
	struct blinkParam
	{
		int czasKropki;
		int wielkoscDiody;	//mozna interpretowac jako jasnosc
	};

private:
	blinkParam parametry;
	CONSOLE_CURSOR_INFO dioda;
	HANDLE uchwytCMD;
	COORD pozycja;

public:
	Blink();
	~Blink();
	Blink(const Blink& b);

	void mruganie(std::string doWymrugania);
	void Set_parametry(int czasKropki, int wielkoscDiody);
	void Set_parametry(int czasKropki);
	blinkParam Get_parametry();

	void Set_pozycjaDiody(int x, int y);
	COORD Get_pozycjaDiody();

	const Blink& operator = (const Blink& drugi);
};

#endif // !BLINK_H
