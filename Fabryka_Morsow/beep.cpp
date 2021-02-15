/*
*	Klasa: beep
*	Autor:	Adam Porembinski
*	Opis: Potrafi piszczec  w kodzie mors'a glosnikiem systemowym. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	22.01.2021	mozliwosc piszczenia, debug
*	23.01.2021	debug pobierania parametrow
*/

#include "beep.h"

beep::beep()
{
	parametry.czasKropki = 150;
	parametry.czestotliwosc = 500;
}

beep::~beep()
{
}

beep::beep(const beep& b)
{
	parametry.czasKropki = b.parametry.czasKropki;
	parametry.czestotliwosc = b.parametry.czestotliwosc;
}

void beep::piszczenie(std::string doWypiszczenia)
{
	std::string piski;
	morse Morsik;

	Morsik.setWynikDoStringa(true);
	piski = Morsik.Translator(doWypiszczenia);

	for (size_t i = 0; i < piski.size(); i++)
	{
		switch (piski[i])
		{
		case '.':
			Beep(parametry.czestotliwosc, parametry.czasKropki);
			break;
		case '-': 
			Beep(parametry.czestotliwosc, 3 * parametry.czasKropki);
			break;
		case '|': 
			Sleep(parametry.czasKropki * 7);
			break;
		case '_': 
			Sleep(18 * parametry.czasKropki);
			break;

			default: break;
		}
	}

	return;
}

beep::beepParametry beep::Get_parametry()
{
	return parametry;
}

void beep::Set_parametry(int czasKropki, int czestotliwosc)
{
	parametry.czasKropki = czasKropki;
	parametry.czestotliwosc = czestotliwosc;
	return;
}

const beep& beep::operator=(const beep& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	parametry.czasKropki = drugi.parametry.czasKropki;
	parametry.czestotliwosc = drugi.parametry.czestotliwosc;

	return *this;
}
