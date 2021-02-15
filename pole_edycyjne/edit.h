/*
	Klasa: Edit
	Opis: Mozliwosc tworzenia w konsoli pola z tekstem, mozliwosc jego edytowania i zmiany jego kolorow.

	Adam Porembinski 16.11.2020

	18.11.2020	enumeratory TO DO
	20.11.2020	dodawanie zmiennych konsolowych
	21.11.2020	debug, dodanie licznika
	25.11.2020	przechowywanie kolorow
	27.11.2020	enumeratory
	28.11.2020	robienie getterow i setterow, poprawianie enumeratorow
	29.11.2020	dodanie zmiennych dotyczacych kolorow i odpowiednich funkcji
	01.12.2020  dodanie uchwytu typu input do konsoli
	02.12.2020	debug, robiebie interaktywnego wyswietlania
	03.12.2020	debug, debug, cleanup
	01.02.2021	debug domyslnych kolorow,
				dodanie przeciazenia do wyswietlania,
				zlikwidowanie zmiennej przechowujacej kolory,
				zlikwidowanie niepotrzebnych zmiennych
*/

#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>


class Edit
{
private:
	std::string napis;				//to co ma sie wyswietlac w "kolorowym polu"
	size_t dlugosc;
	COORD pozycjaCMD;
	int foreground, background;		//kolor znaku i kolor tla - jako liczba

	static HANDLE uchwytCMD;		//uchwyt do konsoli, jeden dla wszystkich
	static WORD defaultkolory;		//kolory wczytane z konsoli
	static int licznik;				//liczy ile objektow, gdy ostatni objekt z klasy zostanie zniszczony ustawia defaultkolory

public: 
	enum Kolor : int {	//warosci jak z przyklad.cpp
		Black = 0
		, Blue = 1
		, Green = 2
		, Aqua = 3
		, Red = 4
		, Purple = 5
		, Yellow = 6
		, White = 7
		, Gray = 8
		, Light_Blue = 9
		, Light_Green = 10
		, Light_Aqua = 11
		, Light_Red = 12
		, Light_Purple = 13
		, Light_Yellow = 14
		, Bright_White = 15
	};

public:
	Edit();							//konstruktor bezparam
	Edit(const Edit& e);			//konstruktor kopiujacy
	~Edit();

	void display(std::string);		//pole z napisem nie zostanie wyswietlone poki nie bedzie tej funkcji
	void display();

	void czysczenie();				//czyszczenie konsoli domyslnymi kolorami
	void restoreDefault();			//ustawia domyslne kolory
	int ColorAtribute();			//bierze foreground i background i oblicza wartosc dla WORD
	
	void userText();				//dziala jak interaktywnie jak cin

	void setPosition(int, int);
	void setLenght(int);
	void setText(std::string);		//ustawia napis do wyswietlenia w polu
	void setTextColor(Kolor);
	void setBackgroundColor(Kolor);

	COORD getPosition();			//zwraca pozycje startowa tekstu
	size_t getLength();				//zwraca dlugosc napisu
	HANDLE getHandle();				//zwraca uchwyt do konsoli
	std::string getText();			//bierze napis, ktory jest w polu
	int getForegroundColor();
	int getBackgroundColor();
	
	static WORD getDefaultWord();	//zwraca domyslne wartosci kolorow jako WORD
	int getLicznik();				//zwraca licznik obiektow klasy edit

	const Edit& operator = (const Edit&);
};


#endif	// !EDIT_H