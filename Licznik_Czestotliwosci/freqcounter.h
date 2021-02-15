/*
Klasa "freqcounter"
Opis:	Mozliwosc zliczania wystapien roznych rzeczy, zapisania wyniku oraz eksport do csv lub ppm w postaci histogramu.
		Aktualnie wspierane sa: ppm::color, string, int, char
Autor: Adam Porembinski
Data utworzenia: 14.12.2020

28.12.2020	dodanie includow i templatow, czytanie i zliczanie znakow
29.12.2020	zapisywanie wyniku zliczania, debug
30.12.2020	debug rozmiaru vectora
02.01.2021	ulepszanie czytania z pliku dla innych jezykow, debug
03.01.2021	zmiana koncepcji - wszystko w kodzie ASCII, czytanie stringow, debug
04.01.2021	debug czytania stringow, debug, mala zmiana w templatach, debug, dodanie do klasy vectorow na dane, wyswietlanie danych
05.01.2021	zabezpieczanie plikow
07.01.2021	debug wczytywania znakow, debug wykrywania spacji
08.01.2021	wczytywanie i liczenie liczb oraz kolorow
10.01.2021	debug wczytywania stringow
11.01.2021	debug wczytywania stringow i jego ulepszenie
12.01.2021	komentarze, ulepszenie addData z kolorem
15.01.2021	dodanie mozliwosci posortowania danych, debug
			eksport do pbm, debug
16.01.2021	ulepszenie sortowania, ulepszenie wyswietlania wynikow, debug, debug kolorow, export do pbm, debug
17.01.2021	ulepszenie rysowania pbm i histogramu, likwidowanie powtarzalnosci kodu, zmiana z pbm na ppm (wyglada tak samo ale obrazek ma wiekszy rozmiar), debug
*/

#ifndef FREQCOUNTER_H
#define FREQCOUNTER_H

//#include <string>
//#include <iostream>
//#include <fstream>
#include <vector>
//#include <sstream>		//do string stream
#include "ppm.h"
#include "MapaZnakow.h"	//potrzebne do exportu do PPM
//#include <stdlib.h>	//DEBUG ONLY do czyszczenia ekranu
//#include <cctype> //potrzebne do tolower() RACZEJ DO WYWALENIA

template <typename T>
class Freqcounter {
protected:					//jakby miala byv jakas klasa pochodna
	bool czyOtwartyPlik;
	std::ifstream handlePliku;
	std::string nazwaPliku;

	std::vector<T> dane;
	std::vector<int> ilosc;
	int ileDanych;

public:
	Freqcounter();
	Freqcounter(std::string);
	Freqcounter(const Freqcounter& _F);
	~Freqcounter();

	void addData();		//wczytuje z zaladowanego pliku dane typu obiektu

	void create(int ile, int ileHashy);	//tworzy histogram z danymi, nalezy podac ile danych ma wyswietlic i max ilosc hashy w pasku histogramu

	//moje metody
	void createTable(int);	//tworzy tabele z wypisanymi danymi, nalezy podac ile danych ma wyswietlic, dobry do DEBUG
	void createTable();		//tworzy tabele z wypisanymi danymi, wyswietla wszystko
	void czyszczenie();		//usuwa dane z vectorow
	void zaladowaniePliku(std::string);
	void zamknieciePliku();
	void posortuj();	//od najwiekszego do najmniejszego

	int Get_ileDanych();//uzytkownik nie powinien zmieniac ilosci danych
	std::vector<T> Get_Dane(int ile);	//uzytkownik moze sobie skopiowac dane
	std::vector<int> Get_Ilosc(int ile);//lub ilosc i dzialac dalej na takiej kopji

	//nazwa pliku, ile kolejnych danych brac pod uwage, (PBM) najwieksza szerokosc paska histogramu w pixelach
	void exportCSV(std::string nazwa);			//zwykly export do CSV wszystkich danych
	void exportCSV(std::string nazwa, int ile);
	void exportPPM(std::string nazwaPPM, int ile, int ileHashy);

	const Freqcounter& operator = (const Freqcounter&);

private:	//nie ma potrzeby aby uzytkownik z nich korzystal i lepiej ich nie dotykac
	void _zamiana(int, int);	//potrzebne do sortowania, i poza sortowaniem nie dotykac
	int _dziel(int, int);
	void _sortuj(int, int);		//(quicksort) sortuje od najmniejszego do najwiekszego

	std::string _doStringa(int);	//nalezy traktowac jak domyslny std::to_string();
	
	//potrzebne do robienia histogramu
	bool dzielenieZero;
	int _policzStep(int, int);	//liczy step w histogramie, //dynamiczne okreslanie ile ma symbolizowac jeden step
	int _dlugoscPaska(int, int, int);
};


template <typename T>
Freqcounter<T>::Freqcounter()
{
	czyOtwartyPlik = false;
	ileDanych = 0;
	nazwaPliku = "";

	dzielenieZero = false;
}

template<typename T>
Freqcounter<T>::Freqcounter(std::string nazwaPliku)
{
	handlePliku.open(nazwaPliku);
	if (!handlePliku.good())
	{
		czyOtwartyPlik = false;
		return;
	}

	czyOtwartyPlik = true;
	ileDanych = 0;
	this->nazwaPliku = nazwaPliku;

	dzielenieZero = false;
}

template <typename T>
Freqcounter<T>::Freqcounter(const Freqcounter& _F)
{
	czyOtwartyPlik = _F.czyOtwartyPlik;
	if (czyOtwartyPlik == true)
	{
		handlePliku = _F.handlePliku;
	}

	dane = _F.dane;
	ilosc = _F.ilosc;
	ileDanych = _F.ileDanych;

	dzielenieZero = _F.dzielenieZero;
}

template <typename T>
Freqcounter<T>::~Freqcounter()
{
	if (czyOtwartyPlik==true)
	{
		handlePliku.close();
	}

	dane.clear();
	dane.shrink_to_fit();
	ilosc.clear();
	ilosc.shrink_to_fit();
}



template <>
void Freqcounter<char>::addData()
{
	if (!czyOtwartyPlik)	//zabezpieczenie
	{
		return;
	}

	char znak;
	
	int tmp;	//potrzebne do zwiekszania wartosci ilosci o jeden
	bool znaleziony = false;

	while (!handlePliku.eof())
	{
		handlePliku >> znak;
		znak = std::tolower(znak);

		if(znak >= 33 && znak <= 254)//126)	//jesli znak jest drukowalny w ASCII
		//if (znak >= 33)
		{
			for (int i = 0; i < ileDanych; i++)
			{
				if (dane[i] == znak)
				{
					tmp = ilosc[i];
					tmp++;
					ilosc[i] = tmp;

					znaleziony = true;
					break;
				}
				else
				{
					znaleziony = false;
				}
			}

			if (!znaleziony)
			{
				dane.push_back(znak);
				ilosc.push_back(1);

				ileDanych++;
			}
		}
	}

	posortuj();	//zeby dane byly uporzadkowane
	return;
}

template <>
void Freqcounter<std::string>::addData()
{
	if (!czyOtwartyPlik)	//zabezpieczenie
	{
		return;
	}

	std::string skladanywyraz;
	char znak;
	
	int tmp;	//potrzebne do zwiekszania wartosci ilosci o jeden
	bool znaleziony = false;

	while (!handlePliku.eof())
	{
		handlePliku >> std::noskipws >> znak;	//zeby wykrywal biale znnaki
		znak = std::tolower(znak);	//wplywa tylko na litery przerabiajac je na male

		//wykrywanie tylko malych liter (bo nie ma juz duzych) i cyfr
		//if((znak>=48 && znak<=57) || (znak >= 97 && znak <= 122))	//oryginal
		if (znak >= 33 && znak <= 254)	//jesli znak jest drukowalny w ASCII
		{
			skladanywyraz.push_back(znak);
		}
		
		//wysatrczy ze enter i spacje beda konczyly dokladanie liter, bo wystepuja po znakach interpunkcyjnych
		//a jesli wystapilaby cyfra albo litera po znaku interpunkcyjnym, to znaczy ze tworza jedno slowo
		if (znak == 32 || znak == 10) //spacja, enter
		{
			for (int i = 0; i < ileDanych; i++)
			{
				if (dane[i] == skladanywyraz)
				{
					tmp = ilosc[i];
					tmp++;
					ilosc[i] = tmp;

					znaleziony = true;
					break;
				}
				else
				{
					znaleziony = false;
				}
			}

			if ( skladanywyraz.empty() )	//wykrywanie pustego stringa
			{
				znaleziony = true;	//zeby nie poszedl dalej
			}

			if (!znaleziony)
			{
				dane.push_back(skladanywyraz);
				ilosc.push_back(1);

				ileDanych++;
			}

			//usuwanie znakow z wyrazu
			skladanywyraz.clear();
			skladanywyraz.shrink_to_fit();
		}
	}

	posortuj();	//zeby dane byly uporzadkowane
	return;
}

template <>
void Freqcounter<int>::addData()
{
	if (!czyOtwartyPlik)	//zabezpieczenie
	{
		return;
	}

	int liczba;

	int tmp;	//potrzebne do zwiekszania wartosci ilosci o jeden
	bool znaleziony = false;

	while (!handlePliku.eof())
	{
		handlePliku >> liczba;

		for (int i = 0; i < ileDanych; i++)
		{
			if (dane[i] == liczba)
			{
				tmp = ilosc[i];
				tmp++;
				ilosc[i] = tmp;

				znaleziony = true;
				break;
			}
			else
			{
				znaleziony = false;
			}
		}

		if (!znaleziony)
		{
			dane.push_back(liczba);
			ilosc.push_back(1);

			ileDanych++;
		}
	}

	posortuj();	//zeby dane byly uporzadkowane
	return;
}

template <>
void Freqcounter<ppm::color>::addData()
{
	if (!czyOtwartyPlik)	//zabezpieczenie
	{
		return;
	}

	bool sformatowany = false;	//flaga do sprawdzenia czy obrazek byl sformatowany
	
	//std::cout << "\nLOL\n";

	//sprawdzenie czy istnieje obrazek sformatowany za pomoca klasy obraz "__tmp._dat", 
	//zeby nie tracic czasu jesli juz byl formatowany
	std::ifstream* sprawdzenie = new std::ifstream;
	sprawdzenie->open(obraz::plikTMP);
	if (sprawdzenie->good())
	{
		//std::cout << _obiekcik.Get_pliktmp();//DEBUG ONLY
		sformatowany = true; 
		
		//std::cout << "\nSFORMATOWANY\n";
		sprawdzenie->close();	//zeby byl porzadek zamykamy bezpiecznie sformatowany obrazek
	}
	delete sprawdzenie;	//kasujemy bo nie jest nam juz potrzebny

	if (!sformatowany)	//jesli nie jest sformatowany to bedzie sformatowany
	{
		obraz _obiekcik;	//obiekcik do sformatowania obrazka

		std::cout << "\nFORMATOWANIE... (moze trwac nawet do kilku minut)";
		_obiekcik.otwarcieObrazka(nazwaPliku); //std::cout << "\n_obiekcik opened\n";//DEBUG ONLY!!
		_obiekcik.formatowanie();	//std::cout << "\n_obiekcik formated\n";//DEBUG ONLY!!
		_obiekcik.zamkniecieObrazka(); //std::cout << "\n_obiekcik closed\n";//DEBUG ONLY!!
		std::cout << "\nSFORMATOWANO\n";
	}
	
	//zaladowanie sormatowanej wersji
	handlePliku.close();	//std::cout << "\nhandle close\n";//DEBUG ONLY!!
	handlePliku.open(obraz::plikTMP); //std::cout << "\nhandle open\n";//DEBUG ONLY!!
	
	if (!(handlePliku.good()))
	{
		//std::cout << "\nFAIL\n";//DEBUG ONLY!!
		return;
	}

	//DEBUG ONLY
	//handlePliku.close();
	//handlePliku.open(_obiekcik.Get_pliktmp());
	//

	ppm::color kolorek = {0,0,0};
	ppm::color kolorTMP = {0,0,0};	//tymczasowy kolor ulatwiajacy porownywanie

	int tmp;	//potrzebne do zwiekszania wartosci ilosci o jeden
	bool znaleziony = false;

	//na poczatku sa niepotrzebne dla nas informacje: rozdzielczosc i wymiary
	handlePliku >> tmp;
	handlePliku >> tmp;
	handlePliku >> tmp; //std::cout << "\nWASKOL\n";//DEBUG ONLY!!

	while (!handlePliku.eof())
	{
		//dane beda bezposrednio wczytywane do struktury color
		handlePliku >> kolorek.R;
		handlePliku >> kolorek.G;
		handlePliku >> kolorek.B;
		//std::cout << kolorek<<"\n"; //DEBUG ONLY!!!

		for (int i = 0; i < ileDanych; i++)
		{
			kolorTMP = dane[i];
			//po kolei porownywane wszystkie zmienne struktury
			if ((kolorTMP.R == kolorek.R)&&(kolorTMP.G == kolorek.G)&&(kolorTMP.B == kolorek.B))
			{
				//std::cout << "I";//DEBUG ONLY!!!
				tmp = ilosc[i];
				tmp++;
				ilosc[i] = tmp;

				znaleziony = true;
				break;
			}
			else
			{
				//std::cout << "O";//DEBUG ONLY!!!
				znaleziony = false;
			}
		}

		if (!znaleziony)
		{
			dane.push_back(kolorek);
			ilosc.push_back(1);

			ileDanych++;
		}
		//std::cout << kolorek<< "  " << kolorTMP;//DEBUG ONLY!!!
		//system("PAUSE");
	}
	//std::cout << "\nXD\n";//DEBUG ONLY
	posortuj();	//zeby dane byly uporzadkowane
	return;
}




template <typename T>
void Freqcounter<T>::create(int ile, int ileHashy)	//glowny cel to proby przed exportem do pbm
{
	if (ileDanych == 0 || ile <= 1)	//zabezpieczenie
	{
		return;
	}

	int max = ilosc[0];			//max wartosc w przedziale
	int min = ilosc[ile-1];		//min wartosc w przedziale (Visual moze sie czepiac ale jest OK)

	int step = _policzStep((max - min), ileHashy);

	int maxDlugoscDane = 0;	//potrzebne do wyrownania do prawej
	int tmp;				//zmienna tymczasowa
	std::string skladanie = "";	//string w ktorym beda skladane czesci linijki
	
	std::vector<std::string> wyswietlenieHashy;	//taki screenshot z wszystkimi linijkami #
	std::vector<std::string> wyswietlenieDanych;//taki screenshot z wszystkimi linijkami danych

	

	//int gh = 0;
	
	int porownawczaIlosc = 0;
	for (int i = 0; i < ile; i++)
	{
		//skladanie lewej czesci linijki
		skladanie.insert(0, _doStringa(i));

		porownawczaIlosc = ilosc[i];
		while (i < ile)
		{
			i++;	//krok do porzodu
			//potrzebne zeby nie wyszedl poza tablice gdy ma narysowac wszystkie wyniki
			if (i == ile)
			{
				i--;
				break;
			}

			if (porownawczaIlosc == ilosc[i])
			{
				skladanie.insert(0, "|");						//dodajemy od lewej
				skladanie.insert(0, _doStringa(i));	//
			}
			else
			{
				//aktualizacja max rozmiaru czesci z danymi
				tmp = (int) skladanie.size();	//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
				if (tmp > maxDlugoscDane)
				{
					maxDlugoscDane = tmp;
				}

				//wyjscie
				i--;	//jesli nie znaleziono kolejnego takiego samego to cofamy sie
				break;	//wychodzimy bo juz nie ma co dalej szukac
			}
		}

		wyswietlenieDanych.push_back(skladanie);
			//std::cout << "\n  "<< ile<< "    " << skladanie << "  " << wyswietlenieDanych.size()<< "  "<<i<<" - "<<gh; gh++;//DEBUG ONLY
		skladanie = "";

		//skladanie prawej czesci z ####
		tmp = _dlugoscPaska(ilosc[i], min, step);
		
		for (int j = 0; j < tmp; j++)	//dodawanie hashy
		{
			skladanie = skladanie + "#";
		}
		wyswietlenieHashy.push_back(skladanie);
		skladanie = "";
	}
	
	//robienie wyrownania do prawej
	for (int i = 0; i < wyswietlenieDanych.size(); i++)
	{
		tmp = (int) wyswietlenieDanych[i].size();	//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
		if (tmp < maxDlugoscDane)
		{
			for (int j = 0; j < (maxDlugoscDane - tmp); j++)
			{
				wyswietlenieDanych[i].insert(0, " ");
			}
		}
	}

	//wyswietlanie na ekran
	for (int i = 0; i < wyswietlenieDanych.size(); i++)
	{
		std::cout << wyswietlenieDanych[i] << " " << wyswietlenieHashy[i] << "\n";
	}
	
	return;
}

template <typename T>
void Freqcounter<T>::createTable(int ile)
{
	if (ileDanych == 0 || ile == 0)	//zabezpieczenie
	{
		return;
	}

	
	
	std::string linijka = "";	//linijka musi byc pusta
	int porownawczaIlosc = 0;
	for (int i = 0; i < ile; i++)
	{
		linijka = "";	//na poczatek czyszczenie stringa
		
		linijka.append(_doStringa(i));
		linijka.append(" - ");
		linijka.append(std::to_string(ilosc[i]));

		porownawczaIlosc = ilosc[i];
		while (i < ile)
		{
			i++;	//krok do porzodu
			
			//potrzebne zeby nie wyszedl poza tablice gdy ma narysowac wszystkie wyniki
			if (i == ile)
			{
				i--;
				break;
			}

			if (porownawczaIlosc == ilosc[i])
			{
				linijka.insert(0, "|");						//dodajemy od lewej
				linijka.insert(0, _doStringa(i));			//
			}
			else
			{
				i--;	//jesli nie znaleziono kolejnego takiego samego to cofamy sie
				break;	//wychodzimy bo juz nie ma co dalej szukac
			}
		}

		std::cout << linijka << "\n";
	}

	return;
}

template<typename T>
void Freqcounter<T>::createTable()
{
	if (ileDanych == 0)	//zabezpieczenie
	{
		return;
	}

	createTable(ileDanych);		//(ileDanych-1);
	return;
}

template<typename T>
void Freqcounter<T>::zaladowaniePliku(std::string doOtwarcia)
{
	if (czyOtwartyPlik)	//zabezpieczenie przed rownoczesnym otworzeniem dwoch plikow
	{
		handlePliku.close();
	}

	handlePliku.open(doOtwarcia);
	if (!(handlePliku.good()))
	{
		std::cout << "\nCRITICAL FAIL\n";
		czyOtwartyPlik = false;
		nazwaPliku = "";
		return;
	}

	czyOtwartyPlik = true;
	nazwaPliku = doOtwarcia;

	return;
}

template<typename T>
void Freqcounter<T>::zamknieciePliku()
{
	if (!czyOtwartyPlik)
	{
		return;
	}
	handlePliku.close();
	czyOtwartyPlik = false;
	return;
}

template<typename T>
void Freqcounter<T>::czyszczenie()
{
	if (ileDanych == 0)	//zabezpieczenie przed czysczeniem pustki
	{
		return;
	}

	dane.clear();
	dane.shrink_to_fit();
	ilosc.clear();
	ilosc.shrink_to_fit();

	ileDanych = 0;
	return;
}

template<typename T>
void Freqcounter<T>::_zamiana(int i, int j)	//zamiana i na j oraz j na i
{
	T tmpT;			//do przechowania wartosci z dane
	int tmpint;		//do przechowania jej ilosci

	tmpT = dane[i];
	tmpint = ilosc[i];

	dane[i] = dane[j];
	ilosc[i] = ilosc[j];

	dane[j] = tmpT;
	ilosc[j] = tmpint;

	return;
}

template<typename T>
int Freqcounter<T>::_dziel(int l, int p)
{
	int lewy = l;
	int prawy = p;

	int granicaIndex = lewy + (prawy - lewy) / 2;
	int granicaWart = ilosc[granicaIndex];

	while (lewy <= prawy)
	{
		while (ilosc[lewy] < granicaWart)
		{
			lewy++;
		}
		while (ilosc[prawy] > granicaWart)
		{
			prawy--;
		}

		if (lewy <= prawy)
		{
			_zamiana(lewy, prawy);
			lewy++;
			prawy--;
		}
	}

	return lewy;
}

template<typename T>
void Freqcounter<T>::_sortuj(int lewy, int prawy)	//sortowanie quicksortem
{
	if (ileDanych == 0)	//zabezpieczenie
	{
		return;
	}

	if (lewy < prawy)
	{
		int granicznyIndex = _dziel(lewy, prawy);
		_sortuj(lewy, granicznyIndex-1);
		_sortuj(granicznyIndex, prawy);
	}

	return;
}

template<typename T>
std::string Freqcounter<T>::_doStringa(int index)
{
	std::string wynik = "";
	std::stringstream bufor;

	bufor << dane[index];
	wynik = bufor.str();

	return wynik;
}

template<typename T>
int Freqcounter<T>::_policzStep(int delta, int ileHashy)
{
	int step = delta / ileHashy;	//ma byc max 100x # w linijce
	if (step == 0)
	{
		dzielenieZero = true;
		step = ileHashy / delta;	//zeby nie bylo dzielenia przez zero
	}

	return step;
}

template<typename T>
int Freqcounter<T>::_dlugoscPaska(int aktualnaWartosc, int min, int step)
{
	int dlugosc;
	if (dzielenieZero)
	{
		dlugosc = (aktualnaWartosc - min) * step;
	}
	else
	{
		dlugosc = (aktualnaWartosc - min) / step;
	}


	if (dlugosc < 1)
	{
		dlugosc = 1;	//zeby bylo cos widac
	}

	return dlugosc;
}

template<typename T>
void Freqcounter<T>::posortuj()
{
	if (ileDanych == 0)	//zabezpieczenie
	{
		return;
	}

	_sortuj(0, ileDanych - 1);

	int zamiany = ileDanych/2;
	for (int i = 0; i < zamiany; i++)
	{
		_zamiana(i, ileDanych-1-i);
	}

	return;
}

template<typename T>
int Freqcounter<T>::Get_ileDanych()
{
	return ileDanych;
}

template<typename T>
std::vector<T> Freqcounter<T>::Get_Dane(int ile)
{
	std::vector<T> wynikowy;

	if (ile > ileDanych)
	{
		return wynikowy;
	}

	wynikowy = dane;
	return wynikowy;
}

template<typename T>
std::vector<int> Freqcounter<T>::Get_Ilosc(int ile)
{
	std::vector<int> wynikowy;

	if (ile > ileDanych)
	{
		return wynikowy;
	}

	wynikowy = ilosc;
	return wynikowy;
}

template<typename T>
void Freqcounter<T>::exportCSV(std::string nazwa, int ile)
{
	if (ileDanych == 0)	//zabezpieczenie
	{
		return;
	}

	std::string sufix = ".csv";
	std::ofstream doexportu;
	doexportu.open(nazwa + sufix, std::ofstream::binary);
	
	if (doexportu.good())
	{
		for (int i = 0; i < ile; i++)
		{
			doexportu << dane[i] << "|" << ilosc[i] << "\n";
		}
	}
	else
	{
		std::cout << "\nCOS POSZLO NIE TAK Z ZAPISANIEM DO PLIKU\n";//Razej nie  powinno
	}

	doexportu.close();
	return;
}

template<typename T>
void Freqcounter<T>::exportCSV(std::string nazwa) //WIP						RACZEJ DO WYWALENIA
{
	exportCSV(nazwa, ileDanych);
	return;
}

template <typename T>
const Freqcounter<T>& Freqcounter<T>::operator=(const Freqcounter& drugi)
{
	if (this == &drugi)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	czyOtwartyPlik = drugi.czyOtwartyPlik;
	if (czyOtwartyPlik == true)
	{
		handlePliku = drugi.handlePliku;
	}

	dane = drugi.dane;
	ilosc = drugi.ilosc;
	ileDanych = drugi.ileDanych;

	dzielenieZero = drugi.dzielenieZero;

	return *this;
}

template<typename T>
void Freqcounter<T>::exportPPM(std::string nazwaPPM, int ile, int ileHashy)
{
	if (ileDanych == 0 || ile <= 1)	//zabezpieczenie
	{
		return;
	}
	
	//ile--;	//max index jest o 1 mnijszy od ilosci wszystkich elementow

	std::vector<std::string> test;	//nazwa moze byc mylaca, bedzie tu lewa czesc obrazka z danymi
	std::vector<int> zapelnienie;	//bedzie tu prawa czesc z paskami

	//poczatek jak przy histogramie
	std::string skladanie = "";

	int max = ilosc[0];			//max wartosc w przedziale
	int min = ilosc[ile - 1];		//min wartosc w przedziale (Visual moze sie czepiac ale jest OK)

		//int gh = 0;//DEBUG ONLY
	
	//dynamiczne okreslanie ile ma symbolizowac jeden step
	int step = _policzStep((max - min), ileHashy);

	int maxDlugoscDane = 0;	//potrzebne do wyrownania do prawej
	int porownawczaIlosc = 0;
	int tmp = 0;

	int units = 0;	//okresla ile pixeli szerokosci bedzie mial gruby czarny pasek okreslajacy ilosc 

	for (int i = 0; i < ile; i++)
	{
		//skladanie lewej czesci linijki
		skladanie.insert(0, _doStringa(i));

		porownawczaIlosc = ilosc[i];
		while (i < ile)
		{
			i++;	//krok do porzodu

			//potrzebne zeby nie wyszedl poza tablice gdy ma narysowac wszystkie wyniki
			if (i == ile)
			{
				i--;
				break;
			}

			if (porownawczaIlosc == ilosc[i])
			{
				skladanie.insert(0, "|");						//dodajemy od lewej
				skladanie.insert(0, _doStringa(i));				//
			}
			else
			{
				//aktualizacja max rozmiaru czesci z danymi
				tmp = (int) skladanie.size(); 	//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
				if (tmp > maxDlugoscDane)
				{
					maxDlugoscDane = tmp;
				}

				//wyjscie
				i--;	//jesli nie znaleziono kolejnego takiego samego to cofamy sie
				break;	//wychodzimy bo juz nie ma co dalej szukac
			}
		}

		test.push_back(skladanie);
			//std::cout << "\n  " << skladanie;//DEBUG ONLY!!
		skladanie = "";

			
		//skladanie prawej czesci (pasek)
		tmp = _dlugoscPaska(ilosc[i], min, step);
		
		for (int j = 0; j < tmp; j++)	//dodawanie hashy
		{
			units++;
		}
		zapelnienie.push_back(units);
			//std::cout << "\n  "<< ile<< "    " << zapelnienie.size()<< "  " << test.size()<< "  "<<i<<" - "<<gh; gh++;//DEBUG ONLY
		units = 0;
			//std::cout << "      "<<gh; gh++;//DEBUG ONLY
	}

	int ileLinijek = (int) test.size();		//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
		
	int najdluzszyString = 1;
	for (int i = 0; i < ileLinijek; i++)
	{
		tmp = (int) test[i].size();		//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
		if (tmp > najdluzszyString)
		{
			najdluzszyString = tmp;
		}
	}

		//std::cout << " 5";//DEBUG ONLY
	int szerokosc = 2 + ((najdluzszyString * 6) + najdluzszyString - 1) + 7 + (max - min)/step + 2;
	int wysokosc = 2 + (ileLinijek * 8 + (ileLinijek - 1) * 2) + 2;

	int jeszczeDoPrawej = 0;	//ile narysowanemu paskowi brakuje pixeli do prawego marginesu

	std::string O = "255 255 255 ";	//bialy
	std::string I = "0 0 0 ";	//czarny
	//std::string s = "";

	//jak dane sformatowane to mozna rysowac obrazek
	std::ofstream image;
	nazwaPPM.append(".ppm");
	image.open(nazwaPPM);
	image << "P3 \n";
	image << szerokosc << "\n";
	image << wysokosc << "\n";
	image << 255 << "\n";
	
	

	std::string zawartoscLinijkiTextu = "";
	int rzadPixeli = 0;
	int wierszeZnaku = 8;
	int kolumnyZnaku = 6;
	//int dlugoscMapyZnakow = 38;
	int ileLiterWstawic = 0;
	int offset = 0;	//bedzie wyrownanie do prawej
	int indexWyciagnietego = 0;
	char wyciagnietyZnak;
	char wlasciwyZnak;
	int ktoraLiteraZKolei = 0;

	for (int aktualnaLinijkaTextu = 0; aktualnaLinijkaTextu < ileLinijek; aktualnaLinijkaTextu++)//for od linijek textu
	{
		for (int szerok = 0; szerok < szerokosc; szerok++)																		//przerwa
		{																															//miedzy wierszami
			image << O << O;	//dwa pixele przerwy																				//
		}																															//

		rzadPixeli = 0;
		zawartoscLinijkiTextu = test[aktualnaLinijkaTextu];
		ileLiterWstawic = (int) test[aktualnaLinijkaTextu].size();	//castowanie na int zeby warnigow nie bylo, az tak iwelu elementow nie ma
		offset = najdluzszyString - ileLiterWstawic;

		//std::cout << zapelnienie[aktualnaLinijkaTextu] << "\n"; system("PAUSE");//DEBUG ONLY

		for (int pasek = 0; pasek < wierszeZnaku; pasek++)//for od rzedu pixeli			j to pasek
		{
			image << O << O;										//lewy margines
			//std::cout << "\n2px przerwy" << "\n"; system("PAUSE");
			
			ktoraLiteraZKolei = 0;

			for (int l = 0; l < offset; l++)//for do offsetu																			// wyrownanie do lewej
			{																															//
				for (int i = 0; i < 7; i++)//7 bo kolumny znaku +1																		//
				{																														//
					image << O;																											//
				}																														//
																																		//
			}																															//

			for (int nrZnaku = 0; nrZnaku < ileLiterWstawic; nrZnaku++)//for od wstawiania paskow z znakow								//wpisywanie znakow
			{																															//z przestrzeniami
				wlasciwyZnak = test[aktualnaLinijkaTextu][ktoraLiteraZKolei];															//
				indexWyciagnietego = 0;																									//
																																		//
				for (int m = 0; m < dlugoscMapyZnakow; m++)//for od poszukiwania wlasciwego znaku					//indexu litery		//
				{																									//do wpisania		//
					wyciagnietyZnak = mapaZnakow[m][0];																//znajdowanie		//	
																													//					//
					if (wyciagnietyZnak == wlasciwyZnak)															//					//
					{																								//					//
						indexWyciagnietego = m;		//zapisanie indexu												//					//
						//std::cout << wyciagnietyZnak << " " << pasek << "\n"; system("PAUSE");					//					//
						break;																						//					//
					}
					
					if (m == dlugoscMapyZnakow-1)//znak nieokreslony
					{
						indexWyciagnietego = 0;																		//					//
					}																								//					//
				}																									//					//
																																		//
				for (int pixel = 0; pixel < 6; pixel++)															//wpisany pasek			//
				{									// V--- 1+ bo pierwszy char jest kluczem//znaku				//						//
					if (mapaZnakow[indexWyciagnietego][1 + 6 * pasek + pixel] == '1')		//wpisanie			//						//
					{																		//0 albo 1			//						//
						image << I;															//					//						//
					}																		//					//						//
					else																	//					//						//
					{																		//					//						//			
						image << O;															//					//						//		
					}																		//					//						//
				}																								//						//
																																		//
				image << O;	//wpisanie spacji miedzy znakami																			//
				ktoraLiteraZKolei++;																									//
				//std::cout << wyciagnietyZnak;//DEBUG ONLY
			}																															//

										//przerwa miedzy znakami a paskiem
			for (int przerwa = 0; przerwa < 6; przerwa++)
			{
				image << O;
			}

										//rysowanie plaskiego wycinka paska
			for (int i = 0; i < zapelnienie[aktualnaLinijkaTextu]; i++)
			{
				image << I;
			}
			//std::cout << zapelnienie[aktualnaLinijkaTextu] << "\n"; system("PAUSE");//DEBUG ONLY
			jeszczeDoPrawej = zapelnienie[0] - zapelnienie[aktualnaLinijkaTextu];
			for (int i = 0; i < jeszczeDoPrawej; i++)
			{
				image << O;
			}

			image << O << O;	//prawy margines
			//std::cout << "\n2px przerwy" << "\n"; system("PAUSE");
			rzadPixeli++;
		}
		//std::cout << "\n";	//mozliwy DEBUG ONLY!!
	}

	for (int szerok = 0; szerok < szerokosc; szerok++)																		//margines
	{																															//dolny
		image << O << O;	//dwa pixele przerwy																				//
	}																															//

	image.close();
	return;
}

#endif // !FREQCOUNTER_H