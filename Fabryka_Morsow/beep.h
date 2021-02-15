/*
*	Klasa: beep
*	Autor:	Adam Porembinski
*	Opis: Potrafi piszczec  w kodzie mors'a glosnikiem systemowym. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	22.01.2021	mozliwosc piszczenia
*/

#pragma once
#ifndef BEEP_H
#define BEEP_H

#include <windows.h>	//zeby bylo Beep() i Sleep()
#include "morse.h"

class beep
{
public:
	struct beepParametry
	{
		int czasKropki;
		int czestotliwosc;
	};

private:
	beepParametry parametry;

public:
	beep();
	~beep();
	beep(const beep& b);

	void piszczenie(std::string doWypiszczenia);
	beepParametry Get_parametry();
	void Set_parametry(int czasKropki, int czestotliwosc);

	const beep& operator = (const beep& drugi);
};


#endif // !BEEP_H