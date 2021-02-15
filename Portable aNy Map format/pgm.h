/*
	Klasa: pgm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .pgm  (odcienie szarosci), posiada wlasny licznik kolorow

	Adam Porembinski 20.12.2020

	20.12.2020	komentarze
*/

#pragma once
#ifndef PGM_H
#define PGM_H

#include "obraz.h"

class pgm : public obraz
{
private:
	int odcien;

public:
	pgm();
	pgm(const pgm& p);
	~pgm();

	int licznikKolorow();	//wlasny licznik kolorow

	const pgm& operator = (const pgm& drugi_ppm);
};

#endif // !PGM_H