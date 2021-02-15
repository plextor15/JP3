#include "ppm.h"
/*
	Klasa: ppm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .ppm, posiada wlasny licznik kolorow

	Adam Porembinski 7.12.2020

	16.12.2020	zliczanie kolorow
	18.12.2020	struktora kolor
	19.12.2020	debug
	20.12.2020	komentarze
	08.01.2021	dodanie operatora << i do struktury, debug
*/

#include "ppm.h"

ppm::ppm()
{
	kolor.R = 0;
	kolor.G = 0;
	kolor.B = 0;
}

ppm::ppm(std::string nazwaObraz)
{
	Set_nazwaObrazka(nazwaObraz);
	otwarcieObrazka(nazwaObraz);
}

ppm::ppm(const ppm& p) : obraz(p)
{
	kolor = p.kolor;
}

ppm::~ppm()
{
	//nie ma zdanych tablic dynamicznych
}

const ppm& ppm::operator = (const ppm& drugi_ppm)
{
	if (this == &drugi_ppm)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	this->obraz::operator=(drugi_ppm);
	kolor = drugi_ppm.kolor;

	return *this;
}


int ppm::licznikKolorow() 
{
	obraz::licznikKolorow();

	std::string nazwaDoPliku;
	long int rozmiarTablicy;
	int x = 0, y = 0, rozKolorow = 0, ileKolorow = 0;	//tymczasowe zmienne
	
	nazwaDoPliku = Get_pliktmp();
	
	std::ifstream wlasciwe;
	wlasciwe.open(nazwaDoPliku);
	
	//wczytywanie wlasciwosci obrazu
	wlasciwe >> x;
	wlasciwe >> y;
	wlasciwe >> rozKolorow;
	rozKolorow++;			//bo jest jeszcze 0
	
	Set_wlasciwosci(x, y, rozKolorow);	//zapisanie wartosci do struktury wlasciwosci
	
	rozmiarTablicy = rozKolorow * rozKolorow * rozKolorow;	//objetosc kostki
	bool* tablica = new bool[rozmiarTablicy];	//wnetrze kostki RGB jako jeden ciag

	for (int k = 0; k < rozmiarTablicy; k++)
	{
		tablica[k] = false;		//wszystkie pola domyslnie na false
	}
	
	while (!wlasciwe.eof())
	{
	    wlasciwe >> kolor.R;
	    wlasciwe >> kolor.G;
	    wlasciwe >> kolor.B;
				    
	    tablica[kolor.B + rozKolorow * (kolor.G + rozKolorow * kolor.R)] = true;
		//wartosci RGB to wspolrzedne, kolory moga sie powtarzac
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

std::ostream& operator<<(std::ostream& out, ppm::color c)
{
	out << c.R << "," << c.G << "," << c.B;
	return out;
}

std::stringstream& operator<<(std::stringstream& out, ppm::color c)
{
	out << c.R << "," << c.G << "," << c.B;
	return out;
}

//std::istream& operator>>(std::istream& input, ppm::color c)
//{
//	input >> c.R;
//	input >> c.G;
//	input >> c.B;
//	return input;
//}

//std::istream& operator>>(std::istream& input, ppm::color& c)
//{
//	input >> c.R >> c.G >> c.B;
//	return input;
//}
