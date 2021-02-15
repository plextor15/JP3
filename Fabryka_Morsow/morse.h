/*
	Klasa: morse
	Opis: Wszystko co mozna zrobic zeby pikalo razem z translatorem.
	Adam Porembinski 2.11.2020
	
	02.11.2020	ustawienie zarysu, obmyslanie tablicy znakow
	05.11.2020	ustawienie zmiennej WordPause
	08.11.2020	wstepnie operator<<
	09.11.2020	zmiana koncepcji dzialania - usuniecie TablicaKropek i dodanie funkcji Piski() i Pisk()
	21.01.2021	dodanie mozliwosci piszczenia do stringa - kropki i kreski sa reprezentowane przez znaki "." i "-", spacja miedzy miedzy slowami to "_" 
				dodanie zmiennej klasy trzymajacej prztlumaczony string
*/

#ifndef MORSE_H
#define MORSE_H

#include <string>
#include <windows.h>

class morse {
public:
	morse();		//konstruktor bezparam
	morse(const morse& m);		//konstruktor kopiujacy
	~morse();		//destruktor

	//funkcje ustawiajace zmienne
	void setFrequency(int);
	void setDotTime(int);
	void setDashTime(int);
	void setPause(int);		//ustawia pauze miedzy kropka a kreska
	void setCharPause(int); //ustawia pauze miedzy znakami
	void setWordPause(int);	//ustawia czas przerwy miedzy wyrazami
	void setWynikDoStringa(bool);
	bool getWynikDoStringa();

	//Ilosc char okresla ile ./- jest w znaku
	void PiskString(char);	//w zaleznosci od tego czy wynik ma wyrzucac do string aczy na glosnik
	void Pisk(char a, bool koniec); // jako 'a' wpisuje sie '-' albo '.' , koniec - true gdy jest to ostatni znak wyrazu
	void Piski(char);
	void Piski(char, char);
	void Piski(char, char, char);
	void Piski(char, char, char, char);
	void Piski(char, char, char, char, char); //potrzebne przy cyfrach
	void Piski(char, char, char, char, char, char); //potrzebne przy . i ,

	void Translator(char);
	std::string Translator(std::string);

	const morse& operator = (const morse& drugi);
//	friend std::ostream& operator<< (long);
//	friend std::ostream& operator<< (float);
//	friend std::ostream& operator<< (char);

private:
	int Frequency, DotTime, DashTime, Pause, CharPause;
	int WordPause;	//czas przerwy miedzy wyrazami
	
	bool wynikDoStringa;
	std::string przetlumaczony;
};

#endif // !MORSE_H

