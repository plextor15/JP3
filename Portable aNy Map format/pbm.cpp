/*
	Klasa: pbm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .pbm  (czarno-biale), posiada wlasny licznik kolorow

	Adam Porembinski 20.12.2020

	20.12.2020	komentarze
*/

#include "pbm.h"

pbm::pbm()
{
	czyTylkoJedenkolor = true;
	pixel = false;
}

pbm::pbm(const pbm& p)
{
	czyTylkoJedenkolor = p.czyTylkoJedenkolor;
	pixel = p.pixel;
}

pbm::~pbm()
{
}

int pbm::licznikKolorow()
{
	obraz::licznikKolorow();

	std::string nazwaDoPliku;
	int rozmiarTablicy = 2;		//moze byc albo czarne albo biale
	int x = 0, y = 0, rozKolorow = 2, ileKolorow = 0;	//tymczasowe zmienne

	nazwaDoPliku = Get_pliktmp();

	std::ifstream wlasciwe;
	wlasciwe.open(nazwaDoPliku);

	//wczytywanie wlasciwosci obrazu
	wlasciwe >> x;
	wlasciwe >> y;
	//rozdzielczosc kolorow jest zawsze 2

	Set_wlasciwosci(x, y, rozKolorow);	//zapisanie wartosci do struktury wlasciwosci

	bool* tablica = new bool[rozmiarTablicy];
	for (int k = 0; k < rozmiarTablicy; k++)
	{
		tablica[k] = false;
	}

	while (!wlasciwe.eof())
	{
		wlasciwe >> pixel;

		tablica[pixel] = true;
	}

	//zliczanie kolorow
	for (int k = 0; k < rozmiarTablicy; k++)
	{
		if (tablica[k] == true)
		{
			ileKolorow++;
		}
	}

	if (ileKolorow != 1)
	{
		czyTylkoJedenkolor = false;
	}
	else
	{
		czyTylkoJedenkolor = true;
	}

	wlasciwe.close();
	delete[] tablica;	//po odczytaniu kolorow tablca nie jest nam juz potrzebna
	tablica = NULL;
	return ileKolorow;
}

const pbm& pbm::operator=(const pbm& drugi_pbm)
{
	if (this == &drugi_pbm)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	this->obraz::operator=(drugi_pbm);
	czyTylkoJedenkolor = drugi_pbm.czyTylkoJedenkolor;
	pixel = drugi_pbm.pixel;

	return *this;
}
