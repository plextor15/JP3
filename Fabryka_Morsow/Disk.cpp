/*
*	Klasa: Disk
*	Autor: Adam Porembinski
*	Opis: Sluzy do zapisywania kodu mors'a do pliku. Na razie do uzycia z klasa morseFactory.
*
*	20.01.2021	stworzenie klasy
*	21.01.2021	mozliwosc pisania do pliku
*	24.01.2021	debug zapisywania do pliku
*	27.01.2021	drobne poprawki w klasie, poprawienie zapisu do pliku
*	30.01.2021	cleanup
*/

#include "Disk.h"

Disk::Disk()
{
	parametry.kropka = '.';
	parametry.kreska = '_';
	parametry.spacja = ' ';
	parametry.przerwa = '/';

	plikWyjsciowy = "Disk_wynikowy.txt";
}

Disk::~Disk()
{
}

Disk::Disk(const Disk& d)
{
	parametry.kropka = d.parametry.kropka;
	parametry.kreska = d.parametry.kreska;
	parametry.spacja = d.parametry.spacja;
	parametry.przerwa = d.parametry.przerwa;

	plikWyjsciowy = d.plikWyjsciowy;
}

void Disk::pisanieDoPliku(std::string doWpisania)
{
	std::ofstream doPliku;
	std::string przejsciowy;
	std::string tekst = "";
	morse Morsik;
	
	Morsik.setWynikDoStringa(true);
	przejsciowy = Morsik.Translator(doWpisania);

	for (size_t i = 0; i < przejsciowy.size(); i++)
	{
		if (przejsciowy[i] == '.')
		{
			tekst.push_back(parametry.kropka);
		}
		else if (przejsciowy[i] == '-')
		{
			tekst.push_back(parametry.kreska);
		}
		else if (przejsciowy[i] == '|')
		{
			tekst.push_back(parametry.przerwa);
		}
		else if (przejsciowy[i] == '_')
		{
			tekst.push_back(parametry.spacja);
		}
	}
	
	doPliku.open(plikWyjsciowy, std::ios::app);
	if (doPliku.good())
	{
		doPliku << tekst << "\n";
	}
	else
	{
		std::cerr << "\nProblem z zapisem do pliku\n";
	}
	
	doPliku.close();
	return;
}

Disk::diskParam Disk::Get_parametry()
{
	return parametry;
}

void Disk::Set_parametry(char kropka, char kreska, char spacja, char przerwa)
{
	parametry.kropka = kropka;
	parametry.kreska = kreska;
	parametry.spacja = spacja;
	parametry.przerwa = przerwa;
	return;
}

void Disk::Set_plikWejsciowy(std::string plikWyjsciowy)
{
	this->plikWyjsciowy = plikWyjsciowy;
	return;
}

std::string Disk::Get_plikWyjsciowy()
{
	return plikWyjsciowy;
}

const Disk& Disk::operator=(const Disk& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	parametry.kropka = drugi.parametry.kropka;
	parametry.kreska = drugi.parametry.kreska;
	parametry.spacja = drugi.parametry.spacja;
	parametry.przerwa = drugi.parametry.przerwa;

	plikWyjsciowy = drugi.plikWyjsciowy;

	return *this;
}
