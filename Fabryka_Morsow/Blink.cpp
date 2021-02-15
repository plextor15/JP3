/*
*	Klasa: Blink
*	Autor:	Adam Porembinski
*	Opis: Potrafi migac dioda w kodzie mors'a. Owa dioda to znak kursora migajacy w konsoli. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	23.01.2021	dodanie potrzebnych funkcji, testowanie kursora jako diody
*	24.01.2021	debug wyswietlania diody, powrot do zwyklych ustawien kursora
*/

#include "Blink.h"

Blink::Blink()
{
	parametry.czasKropki = 500;
	parametry.wielkoscDiody = 100;

	dioda.bVisible = false;
	dioda.dwSize = parametry.wielkoscDiody;

	uchwytCMD = GetStdHandle(STD_OUTPUT_HANDLE);

	pozycja.X = 2;
	pozycja.Y = 2;
}

Blink::~Blink()
{
	dioda.dwSize = 25;		//normalna wielkosc kursora
	dioda.bVisible = true;
	SetConsoleCursorInfo(uchwytCMD, &dioda);
}

Blink::Blink(const Blink& b)
{
	parametry.czasKropki = b.parametry.czasKropki;
	parametry.wielkoscDiody = b.parametry.wielkoscDiody;

	dioda.bVisible = b.dioda.bVisible;
	dioda.dwSize = b.dioda.dwSize;

	uchwytCMD = b.uchwytCMD;

	pozycja.X = b.pozycja.X;
	pozycja.Y = b.pozycja.Y;
}

void Blink::mruganie(std::string doWymrugania)
{
	std::string wymrugiwany;
	morse Morsik;

	Morsik.setWynikDoStringa(true);
	wymrugiwany = Morsik.Translator(doWymrugania);

	system("CLS");
	dioda.bVisible = false;
	dioda.dwSize = parametry.wielkoscDiody;
	SetConsoleCursorPosition(uchwytCMD, pozycja);
	SetConsoleCursorInfo(uchwytCMD, &dioda);
	std::cout << " ";	//zeby bylo widac diode

	for (size_t i = 0; i < wymrugiwany.size(); i++)
	{
		switch (wymrugiwany[i])
		{
		case '.':
			dioda.bVisible = true;
			SetConsoleCursorInfo(uchwytCMD, &dioda);
			Sleep(parametry.czasKropki);
			break;
		case '-':
			dioda.bVisible = true;
			SetConsoleCursorInfo(uchwytCMD, &dioda);
			Sleep(3 * parametry.czasKropki);
			break;
		case '|':
			Sleep(parametry.czasKropki * 6 - parametry.czasKropki);
			break;
		case '_':
			Sleep(15 * parametry.czasKropki - parametry.czasKropki);
			break;

		default: break;
		}

		dioda.bVisible = false;
		SetConsoleCursorInfo(uchwytCMD, &dioda);
		Sleep(parametry.czasKropki);
	}

	system("CLS");	//zeby wyswietlany tekst nie byl przesuniety
	return;
}

void Blink::Set_parametry(int czasKropki, int wielkoscDiody)
{
	parametry.czasKropki = czasKropki;

	if (wielkoscDiody > 100)
	{
		parametry.wielkoscDiody = 100;
	}
	else if (wielkoscDiody <= 0)
	{
		parametry.wielkoscDiody = 1;
	}
	else
	{
		parametry.wielkoscDiody = wielkoscDiody;
	}

	return;
}

void Blink::Set_parametry(int czasKropki)
{
	parametry.czasKropki = czasKropki;
	return;
}

Blink::blinkParam Blink::Get_parametry()
{
	return parametry;
}

void Blink::Set_pozycjaDiody(int x, int y)
{
	pozycja.X = x;
	pozycja.Y = y;
	return;
}

COORD Blink::Get_pozycjaDiody()
{
	return pozycja;
}

const Blink& Blink::operator=(const Blink& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	parametry.czasKropki = drugi.parametry.czasKropki;
	parametry.wielkoscDiody = drugi.parametry.wielkoscDiody;

	dioda.bVisible = drugi.dioda.bVisible;
	dioda.dwSize = drugi.dioda.dwSize;

	uchwytCMD = drugi.uchwytCMD;

	pozycja.X = drugi.pozycja.X;
	pozycja.Y = drugi.pozycja.Y;

	return *this;
}
