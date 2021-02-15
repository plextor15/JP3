/*
*	Klasa: Console
*	Autor:	Adam Porembinski
*	Opis: Potrafi wypisywac do konsoli morsem. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	21.01.2021	mozliwosc pisania na ekran, debug
*	27.01.2021	zlikwidowanie parametru czasu
*	30.01.2021	cleanup
*/

#include "Console.h"

Console::Console()
{
	parametry.kropka = '.';
	parametry.kreska = '-';
}

Console::Console(char kropka, char kreska)
{
	this->parametry.kropka = kropka;
	this->parametry.kreska = kreska;
}

Console::~Console()
{
}

Console::Console(const Console& c)
{
	parametry.kropka = c.parametry.kropka;
	parametry.kreska = c.parametry.kreska;
}

void Console::wypisywanie(std::string doWypisania)
{
	std::string przejsciowy;
	std::string naEkran = "";
	morse Morsik;

	Morsik.setWynikDoStringa(true);
	przejsciowy = Morsik.Translator(doWypisania);

	for (size_t i = 0; i < przejsciowy.size(); i++)
	{
		if (przejsciowy[i] == '.')
		{
			naEkran.push_back(parametry.kropka);
		}
		else if (przejsciowy[i] == '-')
		{
			naEkran.push_back(parametry.kreska);
		}
		else if (przejsciowy[i] == '|')
		{
			naEkran.push_back(' ');
		}
		else if (przejsciowy[i] == '_')
		{
			naEkran.push_back(' ');
			naEkran.push_back(' ');
		}
	}
	
	std::cout << "\n" << naEkran << "\n";
	
	return;
}

Console::consoleParam Console::Get_parametry()
{
	consoleParam parametryObiektu = parametry;
	return parametryObiektu;
}

void Console::Set_parametry(char kropka, char kreska)
{
	parametry.kropka = kropka;
	parametry.kreska = kreska;
	return;
}

const Console& Console::operator=(const Console& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	parametry.kropka = drugi.parametry.kropka;
	parametry.kreska = drugi.parametry.kreska;

	return *this;
}
