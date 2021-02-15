/*
	Klasa: ppm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .ppm, posiada wlasny licznik kolorow

	Adam Porembinski 7.12.2020

	16.12.2020	zliczanie kolorow
	18.12.2020	struktora kolor
	19.12.2020	debug
	20.12.2020	komentarze
	08.01.2021	struktura Kolor a od teraz color jest publiczna zeby mozna bylo ja latwo stworzyc i porownac
				dodanie operatora << (i >>) do struktury, debug
	10.01.2021	zmienna kolor jest prywatna, a struktura color publiczna, debug operatora >>
	16.01.2021	dodanie operatora << dla string stream
*/

#pragma once
#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <string>
#include <sstream>

#include "obraz.h"

class ppm : public obraz
{
public:
	struct color{
		int R;
		int G;
		int B;
	};

private:
	color kolor{};

public:
	ppm();
	ppm(std::string);		//konstruktor z main
	ppm(const ppm& p);
	~ppm();

	int licznikKolorow();	//wlasny licznik kolorow
	
	
	const ppm& operator = (const ppm& drugi_ppm);

	friend std::ostream& operator << (std::ostream& out, ppm::color c);
	//friend std::istream& operator >> (std::istream& input, ppm::color c);
	friend std::stringstream& operator << (std::stringstream& out, ppm::color c);
};

#endif // !PPM_H