/*
Klasa: Random
Opis:	Losuje wartosci roznego typu i zachowuje wyniki losowania.
		TERAZ DO UZYCIA W LICZNIKU CZESTOTLIWOSCI ZEBY BYLO PROSCIEJ JEST TYLKO MINIMUM

08.01.2021	stworzenie klasy
18.01.2021	zablokowanie mozliwosci kopiowania objektow tej klasy (bo ma byc tylko jeden)
*/

#include "Random.h"

Random::Random()
{
	ile = 0;
}

Random::Random(const Random& _R){}	//nie ma potrzeby, bo objekt bedzie istnial tylko jeden

Random::~Random()
{
	wynikowy.clear();
	wynikowy.shrink_to_fit();
}

void Random::wylosuj(int start, int koniec, int ilelos) {
	int c;
	ile = ilelos;

	for (int i = 0; i < ile; i++)
	{
		c = rand() % (koniec - start + 1) + start;
		wynikowy.push_back(c);
	}

	return;
}

void Random::czyszczenie() {
	wynikowy.clear();
	wynikowy.shrink_to_fit();
	return;
}

void Random::zapis(std::string nazwapliku) {
	std::ofstream wyniki;
	wyniki.open(nazwapliku);

	for (int i = 0; i < ile; i++)
	{
		wyniki << wynikowy[i] << " ";
	}
	wyniki.close();

	return;
}

const Random& Random::operator=(const Random& drugi)	//nie ma potrzeby, bo objekt bedzie istnial tylko jeden
{
	return *this;
}	
