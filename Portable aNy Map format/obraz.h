/*
	Klasa: obraz
	Opis: Odczytanie wlasciwosci obrazka, usuniecie komentarzy z jego wnetrza oraz mozliwosc liczenia kolorow

	Adam Porembinski 7.12.2020

	16.12.2020	zliczanie kolorow
	18.12.2020	ulepszanie klasy, dodanie seterow i geterow
	19.12.2020	debug
	20.12.2020	komentarze
*/

#pragma once
#ifndef OBRAZ_H
#define OBRAZ_H

#include <string>
#include <fstream>

class obraz
{
private:
	bool otwartyObrazek = false;		//Zeby pozniej nie bylo problemow
	std::string plikTMP = "__tmp._dat";	//tekst bez komentarzy, raczej niczego nie nadpisze
	std::string nazwaObrazka;
	std::ifstream uchwytObrazka;		//uchwyt di pliku obrazka

	struct wlasciwosciObraz {
		int x;
		int y;
		int rozdzielczoscKolorow;
	} wlasciwosci;						//zeby byl porzadek

public:
	obraz();
	obraz(const obraz& o);
	virtual ~obraz();

	void otwarcieObrazka(std::string);
	void zamkniecieObrazka();
	void formatowanie();				//usuwanie komentarzy, nie kasuje oryginalu

	bool czyOtwartyObrazek();
	void Set_nazwaObrazka(std::string);
	std::string Get_nazwaObrazka();

	int virtual licznikKolorow();		//dla klas pochodnych
	
	int Get_x();
	void Set_x(int);
	int Get_y();
	void Set_y(int);
	int Get_rozdzielczoscKolorow();
	void Set_rozdzielczoscKolorow(int);
	std::string Get_pliktmp();

	wlasciwosciObraz Get_wlasciwosci();
	void Set_wlasciwosci(wlasciwosciObraz);
	void Set_wlasciwosci(int, int, int);

	const obraz& operator = (const obraz&);
};

int liczkolory(obraz &obrazek);				//funkcja z main

#endif // !OBRAZ_H