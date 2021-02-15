/*
	Klasa: pgm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .pgm (odcienie szarosci), posiada wlasny licznik kolorow

	Adam Porembinski 20.12.2020

	20.12.2020	komentarze
*/

#include "pgm.h"

pgm::pgm()
{
	odcien = 0;
}

pgm::pgm(const pgm& p)
{
	odcien = p.odcien;
}

pgm::~pgm()
{
}

int pgm::licznikKolorow()
{
	obraz::licznikKolorow();

	std::string nazwaDoPliku;
	int rozmiarTablicy;
	int x = 0, y = 0, rozKolorow = 0, ileKolorow = 0;	//tymczasowe zmienne

	nazwaDoPliku = Get_pliktmp();

	std::ifstream wlasciwe;
	wlasciwe.open(nazwaDoPliku);

	//wczytywanie wlasciwosci obrazu
	wlasciwe >> x;
	wlasciwe >> y;
	wlasciwe >> rozKolorow;	//w tym przypadku odcienie szarosci
	rozKolorow++;			//bo jest jeszcze 0

	Set_wlasciwosci(x, y, rozKolorow);	//zapisanie wartosci do struktury wlasciwosci

	rozmiarTablicy = rozKolorow;	//objetosc kostki
	bool* tablica = new bool[rozmiarTablicy];
	for (int k = 0; k < rozmiarTablicy; k++)
	{
		tablica[k] = false;
	}

	while (!wlasciwe.eof())
	{
		wlasciwe >> odcien;

		tablica[odcien] = true;
	}

	//zliczanie kolorow
	for (int k = 0; k < rozmiarTablicy; k++)
	{
		if (tablica[k] == true)
		{
			ileKolorow++;
		}
	}

	wlasciwe.close();
	delete[] tablica;	//po odczytaniu kolorow tablca nie jest nam juz potrzebna
	tablica = NULL;
	return ileKolorow;
}

const pgm& pgm::operator=(const pgm& drugi_pgm)
{
	if (this == &drugi_pgm)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	this->obraz::operator=(drugi_pgm);
	odcien = drugi_pgm.odcien;

	return *this;
}
