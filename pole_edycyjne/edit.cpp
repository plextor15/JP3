/*
	Klasa: Edit
	Opis: Mozliwosc tworzenia w konsoli pola z tekstem, mozliwosc jego edytowania i zmiany jego kolorow.

	Adam Porembinski 16.11.2020

	20.11.2020	przygotowywanie konsoli do dzialania programu TO DO
	21.11.2020	funkcje obslugujace napis
	25.11.2020	robienie Display() i zeby dzialalo ReadConsoleOutputAttribute()
	28.11.2020	robienie getterow i setterow
	29.11.2020	dodanie zmiennych dotyczacych kolorow i odpowiednich funkcji, debug
	30.11.2020	poprawienie setterow
	01.12.2020  dodanie mozliwosci powroceni ado ustawien domyslnych w konsoli
	02.12.2020	debug, robienie interaktywnego wpisywania i wyswietlanie napisu, debug
	03.12.2020	debug, debug, poprawianie display(), cleanup
	01.02.2021	debug domyslnych kolorow, 
				debug ustawiania koloru tekstu, 
				debug wyswietlania tekstu,
				poprawienie metody getText(),
				zlikwidowanie zmiennej przechowujacej kolory,
				poprawienie metody userText(),
				poprawienie wygladu wyswietlania,
				cleanup
*/

#include "edit.h"

int Edit::licznik = 0;			//potrzebne, zeby od razu bylo ustawione na 0
HANDLE Edit::uchwytCMD = 0;
WORD Edit::defaultkolory = 2;	//DEBUG ONLY!! ma byc 7

Edit::Edit()
{
	//na poczatku sprawa domyslnych kolorow
	if (licznik == 0)
	{
		CONSOLE_SCREEN_BUFFER_INFO domyslne;	//tymczasowa zmienna potrzebna do GetConsoleScreenBufferInfo
		uchwytCMD = GetStdHandle(STD_OUTPUT_HANDLE);		//handle do konsoli
		GetConsoleScreenBufferInfo(uchwytCMD, & domyslne);	//pobieramy domyslne kolory
		defaultkolory = domyslne.wAttributes;
	}

	napis = "";

	foreground = 7;
	background = 0;

	pozycjaCMD.X = 2;
	pozycjaCMD.Y = 2;
	dlugosc = 20;

	licznik++;
}

Edit::Edit(const Edit& e)
{
	napis = e.napis;
	pozycjaCMD = e.pozycjaCMD;
	dlugosc = e.dlugosc;
	
	foreground = e.foreground;
	background = e.background;

	licznik++;
}

Edit::~Edit()
{
	licznik--;
	
	if ( licznik == 0)	//jesli to byl juz ostatni obiekt klasy
	{
		SetConsoleTextAttribute(uchwytCMD, defaultkolory);//ustawiamy kolory na domyslne
	}
}

void Edit::setPosition(int x, int y)
{
	if (x <= 0 || y <= 0)	//jakby uzytkownik wpisal niodpowiednie wartosci, zostana wpisane domyslne
	{
		pozycjaCMD.X = 1;
		pozycjaCMD.Y = 1;
		return;
	}

	pozycjaCMD.X = x;
	pozycjaCMD.Y = y;
	
	return;
}

void Edit::setLenght(int l)
{
	if (l <= 0)
	{
		dlugosc = 1;
		return;
	}
	else 
	{
		dlugosc = l;
	}
	
	return;
}

void Edit::setText(std::string wpisany)
{
	napis = wpisany;
	return;
}

void Edit::setTextColor(Edit::Kolor k)
{
	if ( !(k >= 0 && k <= 15) )	//zeby wartosc nie wyszla poza zakres mozliwych kolorow
		return;
	
	foreground = k;
	return;
}

void Edit::setBackgroundColor(Edit::Kolor k)
{
	if ( !(k >= 0 && k <= 15) )	//zeby wartosc nie wyszla poza zakres mozliwych kolorow
		return;

	background = k;
	return;
}

void Edit::display(std::string napisNaEkran)
{
	const int ileZnakowMaNapis = napisNaEkran.length();
	std::string pokazanyNapis = "";


	if (napisNaEkran.length() == dlugosc)
	{
		pokazanyNapis = napisNaEkran;
	}

	if (napisNaEkran.length() < dlugosc)
	{
		for (size_t iter = 0; iter < napisNaEkran.length(); iter++)
		{
			pokazanyNapis.push_back(napisNaEkran[iter]);
		}

		
		for (size_t j = dlugosc - (dlugosc - napisNaEkran.length()); j < dlugosc; j++)
		{
			pokazanyNapis.push_back(' ');
		}
	}
	
	if (napisNaEkran.length() > dlugosc)
	{
		size_t start = napisNaEkran.length() - dlugosc;
		for (size_t i = start; i < napisNaEkran.length(); i++)
		{
			pokazanyNapis.push_back(napisNaEkran[i]);
		}
	}

	
	czysczenie();
	SetConsoleCursorPosition(uchwytCMD, pozycjaCMD); //ustawianie kursora konsolowego
	std::cout << pokazanyNapis; 
	
	return;
}

void Edit::display()
{
	display(napis);
	return;
}

void Edit::restoreDefault()
{
	SetConsoleTextAttribute(uchwytCMD, defaultkolory);
	return;
}

void Edit::czysczenie()
{
	SetConsoleTextAttribute(uchwytCMD, defaultkolory);
	system("CLS");
	SetConsoleTextAttribute(uchwytCMD, ColorAtribute());
	return;
}

int Edit::ColorAtribute()
{
	return foreground + (background * 16);
}

std::string Edit::getText()
{
	std::string wynikowyString;

	SetConsoleTextAttribute(uchwytCMD, defaultkolory);
	std::getline(std::cin, wynikowyString);

	return wynikowyString;
}

void Edit::userText()
{
	czysczenie();

	std::string edytowanyString = "#";	//jest tylko kursor
	bool edytowanie = true;
	char znak;
	
	while (edytowanie)
	{
		std::cin.clear();	//czyszczenie bufora
		znak = _getch();
		
		if (znak == 13)
		{
			edytowanie = false;
			edytowanyString.pop_back();
			napis = edytowanyString;
			break;
		}

		if (znak == 8 && edytowanyString != "#")
		{
			edytowanyString.pop_back();
			edytowanyString.pop_back();
			edytowanyString.push_back('#');
		}


		if (znak >= 32 && znak <= 126)
		{
			edytowanyString.pop_back();
			edytowanyString.push_back(znak);
			edytowanyString.push_back('#');
		}
		
		display(edytowanyString);
	}

	return;
}

HANDLE Edit::getHandle()
{
	return uchwytCMD;
}

COORD Edit::getPosition()
{
	return pozycjaCMD;
}

size_t Edit::getLength()
{
	return napis.length();
}

WORD Edit::getDefaultWord()
{
	return defaultkolory;
}

int Edit::getLicznik()
{
	return licznik;
}

int Edit::getForegroundColor()
{
	return foreground;
}

int Edit::getBackgroundColor()
{
	return background;
}

const Edit& Edit::operator=(const Edit& drugiEdit)
{
	if (this == &drugiEdit)	//sprawdzenie czy ten drugi to nie jest ten
	{
		return *this;
	}

	napis = drugiEdit.napis;
	
	dlugosc = drugiEdit.dlugosc;
	pozycjaCMD = drugiEdit.pozycjaCMD;
	
	foreground = drugiEdit.foreground;
	background = drugiEdit.background;

	return *this;
}