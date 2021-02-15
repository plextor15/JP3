/*
	Klasa: pbm	(pochodna obraz)
	Opis: Specjalnie do obrazow typu .pbm  (czarno-biale), posiada wlasny licznik kolorow

	Adam Porembinski 20.12.2020

	20.12.2020	komentarze
*/

#pragma once
#ifndef PGM_H
#define PGM_H

#include "obraz.h"

class pbm : public obraz
{
private:
	bool czyTylkoJedenkolor;//czy obrazek jest tylko czarny/bialy, czy czarno-bialy	
	int pixel;				//1 - bialy, 0 - czarny

public:
	pbm();
	pbm(const pbm& p);
	~pbm();

	int licznikKolorow();	//wlasny licznik kolorow

	const pbm& operator = (const pbm& drugi_ppm);
};

#endif // !PGM_H
