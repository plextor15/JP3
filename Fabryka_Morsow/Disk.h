/*
*	Klasa: Disk
*	Autor: Adam Porembinski
*	Opis: Sluzy do zapisywania kodu mors'a do pliku. Na razie do uzycia z klasa morseFactory.
* 
*	20.01.2021	stworzenie klasy
*	21.01.2021	mozliwosc pisania do pliku
*/

#pragma once
#ifndef DISK_H
#define DISK_H

#include <fstream>
#include <iostream>
#include "morse.h"

class Disk
{
public:
	struct diskParam
	{
		char kropka;
		char kreska;
		char spacja;
		char przerwa;
	};
private:
	diskParam parametry;
	std::string plikWyjsciowy;

public:
	Disk();
	~Disk();
	Disk(const Disk& d);

	void pisanieDoPliku(std::string plik);
	diskParam Get_parametry();
	void Set_parametry(char kropka, char kreska, char spacja, char przerwa);
	void Set_plikWejsciowy(std::string plikWyjsciowy);
	std::string Get_plikWyjsciowy();

	const Disk& operator = (const Disk& drugi);
};


#endif // !DISK_H