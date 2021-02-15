/*
*	Klasa: morseFactory
*	Autor: Adam Porembinski
*	Opis: Mozliwosc nadawania morsem do: glosnika, do pliku, na konsole, i miganie "dioda"
* 
*	18.01.2021	stworzenie klasy, wstepne metody
*	20.01.2021	wykrywanie typu danych external i ich odczytywanie, robienie parsera
*	21.01.2021	przekazanie danych do translatora przez converter stringa, debug
*	27.01.2021	dodanie konwertowania int i float
*	30.01.2021	cleanup
*/

#pragma once
#ifndef MORSEFACTORY_H
#define MORSEFACTORY_H

#include <vector>	//do przechowywania parametrow
#include "Beep.h"
#include "Disk.h"
#include "Blink.h"
#include "Console.h"

class morseFactory
{
public:
	enum opcjeDocelowe
	{
		__EMPTY_ = 0	//do nikad
		,BEEP = 1		//do klasy Beep
		,DISK = 2		//do klasy Disk
		,BLINK = 3		//do klasy Blink
		,CONSOLE = 4	//do klasy Console
	};

private:
	
	bool czyPlik;
	
	//w przyszlosci moga byc kolejne parametry, teraz kolejnosc jest nastepujaca:
	//[czas kropki],[czestotliwosc],[znak kropki],[znak kreski],[znak spacji],[znak przerwy],[jasnosc diody]
	std::vector<int> parametry;

	opcjeDocelowe urzadzenieDocelowe;

	void _parser(std::string ciag);
	void _parametryZPliku(std::string pliczek);

public:
	morseFactory();
	morseFactory(const morseFactory& mf);
	~morseFactory();

	void setExternalInfo(std::string parametry);
	void setOutput(opcjeDocelowe wybraneUrzadzenie);

	void convert(std::string doPrzekonwertowania);
	void convert(int doPrzekonwertowania);
	void convert(float doPrzekonwertowania);
	void convert(double doPrzekonwertowania);

	std::string Get_parametry();

	const morseFactory& operator = (const morseFactory& drugi);
};


#endif // !MORSEFACTORY_H
