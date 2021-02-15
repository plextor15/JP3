/*
Klasa: Random
Opis:	Losuje wartosci roznego typu i zachowuje wyniki losowania.
		TERAZ DO UZYCIA W LICZNIKU CZESTOTLIWOSCI ZEBY BYLO PROSCIEJ JEST TYLKO MINIMUM

08.01.2021	stworzenie klasy
18.01.2021	zablokowanie mozliwosci kopiowania objektow tej klasy (bo ma byc tylko jeden)
*/

#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <fstream>
#include <vector>
#include <string>

class Random
{
private:
	std::vector<int> wynikowy;
	int ile;
public:
	Random();
	Random(const Random&);
	~Random();

	void wylosuj(int,int,int);
	void czyszczenie();
	void zapis(std::string);

	const Random& operator = (const Random&);
};

#endif // !RANDOM_H

