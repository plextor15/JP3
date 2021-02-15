/*
	Klasa: ppm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .ppm, posiada wlasny licznik kolorow

	Adam Porembinski 7.12.2020

	16.12.2020	zliczanie kolorow
	18.12.2020	struktora kolor
	19.12.2020	debug
	20.12.2020	komentarze
*/

#pragma once
#ifndef PPM_H
#define PPM_H

#include "obraz.h"

class ppm : public obraz
{
private:
	struct Kolor{
		int R;
		int G;
		int B;
	} kolor;

public:
	ppm();
	ppm(std::string);		//konstruktor z main
	ppm(const ppm& p);
	~ppm();

	int licznikKolorow();	//wlasny licznik kolorow

	const ppm& operator = (const ppm& drugi_ppm);
};

#endif // !PPM_H
