/*
	Klasa: obraz
	Opis: Odczytanie wlasciwosci obrazka, usuniecie komentarzy z jego wnetrza oraz mozliwosc liczenia kolorow

	Adam Porembinski 7.12.2020

	09.12.2020	robienie czytania
	10.12.2020	zmiana koncepcji, robienie czytania
	12.12.2020	robienie czytania
	13.12.2020	robienie czytania, zmiana koncepcji
	14.12.2020	robienie czytania
	18.12.2020	ulepszanie klasy i pliku z sformatowanymi danymi
	19.12.2020	debug
	20.12.2020	komentarze
*/

#include "obraz.h"

obraz::obraz()
{
	wlasciwosci.x = 0;
	wlasciwosci.y = 0;
	wlasciwosci.rozdzielczoscKolorow = 0;
}

obraz::obraz(const obraz& o)
{
	wlasciwosci = o.wlasciwosci;
	nazwaObrazka = o.nazwaObrazka;

	if (o.otwartyObrazek == true)
	{
		otwarcieObrazka(nazwaObrazka);
		otwartyObrazek = true;
	}
	else
	{
		otwartyObrazek = false;
	}
}

obraz::~obraz()
{
	uchwytObrazka.close();
}

void obraz::otwarcieObrazka(std::string obrazek)
{
	uchwytObrazka.open(nazwaObrazka);
	otwartyObrazek = true;
	return;
}

void obraz::zamkniecieObrazka()
{
	uchwytObrazka.close();
	otwartyObrazek = false;
	return;
}

void obraz::formatowanie()
{
	if (otwartyObrazek == false)
	{
		return;
	}

	std::ofstream sformatowany;
	sformatowany.open(plikTMP);

	std::string linijka;
	int index;

	while (!uchwytObrazka.eof())
	{
		std::getline(uchwytObrazka, linijka);
		if (linijka[0] == '#' || linijka[0] == 'P')		//wyciecie pierwszej linijki
		{
			linijka = " ";
		}
		else
		{
			index = linijka.find("#");
			if (index != -1)
			{
				linijka = linijka.substr(0, index);		//wymazanie wszystkiego za # wlacznie
			}
		}
		sformatowany << linijka << " ";
	}

	sformatowany.close();
	return;
}

bool obraz::czyOtwartyObrazek()
{
	return otwartyObrazek;
}

void obraz::Set_nazwaObrazka(std::string nazwa)
{
	nazwaObrazka = nazwa;
	return;
}

std::string obraz::Get_nazwaObrazka()
{
	return nazwaObrazka;
}



int obraz::licznikKolorow()
{
	return -1;
}



int obraz::Get_x()
{
	return wlasciwosci.x;
}

void obraz::Set_x(int X)
{
	wlasciwosci.x = X;
	return;
}

int obraz::Get_y()
{
	return wlasciwosci.y;
}

void obraz::Set_y(int Y)
{
	wlasciwosci.y = Y;
	return;
}

int obraz::Get_rozdzielczoscKolorow()
{
	return wlasciwosci.rozdzielczoscKolorow;
}

void obraz::Set_rozdzielczoscKolorow(int roz)
{
	wlasciwosci.rozdzielczoscKolorow = roz;
	return;
}

std::string obraz::Get_pliktmp()
{
	return plikTMP;
}

obraz::wlasciwosciObraz obraz::Get_wlasciwosci()
{
	wlasciwosciObraz wlasc;
	wlasc.x = wlasciwosci.x;
	wlasc.y = wlasciwosci.y;
	wlasc.rozdzielczoscKolorow = wlasciwosci.rozdzielczoscKolorow;
	return wlasc;
}

void obraz::Set_wlasciwosci(obraz::wlasciwosciObraz wlasc)
{
	wlasciwosci.x = wlasc.x;
	wlasciwosci.y = wlasc.y;
	wlasciwosci.rozdzielczoscKolorow = wlasc.rozdzielczoscKolorow;
	return;
}

void obraz::Set_wlasciwosci(int X, int Y, int roz)
{
	wlasciwosci.x = X;
	wlasciwosci.y = Y;
	wlasciwosci.rozdzielczoscKolorow = roz;
	return;
}

const obraz& obraz::operator=(const obraz& drugiObraz)
{
	if (this == &drugiObraz)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	wlasciwosci = drugiObraz.wlasciwosci;
	nazwaObrazka = drugiObraz.nazwaObrazka;

	if (drugiObraz.otwartyObrazek == true)
	{
		otwarcieObrazka(nazwaObrazka);
		otwartyObrazek = true;
	}
	else
	{
		otwartyObrazek = false;
	}

	return *this;
}

int liczkolory(obraz &obrazek)
{
	int ilosc_kolorow;

	obrazek.formatowanie();
	ilosc_kolorow = obrazek.licznikKolorow();

	return ilosc_kolorow;
}