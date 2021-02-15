/*
	Klasa: morse
	Opis: Wszystko co mozna zrobic zeby pikalo razem z translatorem.
	Adam Porembinski 2.11.2020

	02.11.2020	wstepne napisanie funkcji
	05.11.2020	ustawienie zmiennej WordPause, ustawienie domyslnych wartosci w konstruktorze bezparam
	08.11.2020	konstruktor kopiujacy, wstepnie operator<<
	09.11.2020	dodanie funkcji Piski() i Pisk()
	21.01.2021	dodanie mozliwosci piszczenia do stringa - kropki i kreski sa reprezentowane przez znaki "." i "-", spacja miedzy miedzy slowami to "_", przerwa miedzy literami to "|"
				ulepszenie translatora - teraz poznaje duze litery, debug detekcji przerwy miedzy literami
	22.01.2021	debug tlumaczenia do uniwersalnego stringa
	30.01.2021	cleanup
*/

#include "morse.h"

morse::morse()
{
	//wartosci wedlug standardu
	Frequency = 500;
	DotTime = 100;
	DashTime = 3 * DotTime;
	Pause = DotTime;
	CharPause = 3 * DashTime;
	WordPause = 7 * DotTime;
	wynikDoStringa = false;
	przetlumaczony = "";
}
morse::morse(const morse& m)
{
	this->Frequency = m.Frequency;
	this->DotTime = m.DotTime;
	this->DashTime = m.DashTime;
	this->Pause = m.Pause;
	this->CharPause = m.CharPause;
	this->WordPause = m.WordPause;
	this->wynikDoStringa = m.wynikDoStringa;
	this->przetlumaczony = m.przetlumaczony;
}
morse::~morse()
{
}

void morse::setFrequency(int Frequency)
{
	this->Frequency = Frequency;
	return;
}
void morse::setDotTime(int DotTime)
{
	this->DotTime = DotTime;
	return;
}
void morse::setDashTime(int DashTime)
{
	this->DashTime = DashTime;
	return;
}
void morse::setPause(int Pause)	//pauza miedzy kropka a kreska
{
	this->Pause = Pause;
	return;
}
void morse::setCharPause(int CharPause)	//pauza miedzy znakami
{
	this->CharPause = CharPause;
	return;
}
void morse::setWordPause(int WordPause)	//ustawia czas przerwy miedzy wyrazami
{
	this->WordPause = WordPause;
	return;
}

void morse::setWynikDoStringa(bool x)
{
	wynikDoStringa = x;
	return;
}

bool morse::getWynikDoStringa()
{
	return wynikDoStringa;
}


void morse::PiskString(char x)
{
	if (wynikDoStringa)
	{
		przetlumaczony.push_back(x);
	}
	else
	{
		Beep(Frequency, DashTime);
	}

	return;
}

void morse::Pisk(char a, bool koniec) // koniec - true gdy jest to ostatnia kropka/kreska znaku
{
	switch (a)
	{
	case '-':
		PiskString('-');
		break;
	case '.':
		PiskString('.');
		break;
	default:
		Beep(200, 1000);//buczenie
		break;
	}

	if (koniec)//(!(koniec))
	{
		if (wynikDoStringa)
		{
			przetlumaczony.push_back('|');
		}
		else
		{
			Sleep(Pause);
		}
	}

	return;
}

void morse::Piski(char x)
{
	Pisk(x, true);

	if ( !(wynikDoStringa) )
		Sleep(CharPause);

	return;
}
void morse::Piski(char x, char y)
{
	Pisk(x, false);
	Pisk(y, true);

	if (!(wynikDoStringa))
		Sleep(CharPause);

	return;
}
void morse::Piski(char x, char y, char z)
{
	Pisk(x, false);
	Pisk(y, false);
	Pisk(z, true);

	if (!(wynikDoStringa))
		Sleep(CharPause);

	return;
}
void morse::Piski(char x, char y, char z, char w)
{
	Pisk(x, false);
	Pisk(y, false);
	Pisk(z, false);
	Pisk(w, true);

	if (!(wynikDoStringa))
		Sleep(CharPause);

	return;
}
void morse::Piski(char x, char y, char z, char w, char v) //potrzebne przy cyfrach
{
	Pisk(x, false);
	Pisk(y, false);
	Pisk(z, false);
	Pisk(w, false);
	Pisk(v, true);

	if (!(wynikDoStringa))
		Sleep(CharPause);

	return;
}
void morse::Piski(char x, char y, char z, char w, char v, char u) //potrzebne przy . i ,
{
	Pisk(x, false);
	Pisk(y, false);
	Pisk(z, false);
	Pisk(w, false);
	Pisk(v, false);
	Pisk(u, true);

	if (!(wynikDoStringa))
		Sleep(CharPause);

	return;
}

void morse::Translator(char x)
{
	x = std::tolower(x);
	
	switch (x)
	{
	case 'a': Piski('.', '-'); break;
	case 'b': Piski('-', '.', '.', '.'); break;
	case 'c': Piski('-','.','-','.'); break;
	case 'd': Piski('-','.','.'); break;
	case 'e': Piski('.'); break;
	case 'f': Piski('.','.','-','.'); break;
	case 'g': Piski('-','-','.'); break;
	case 'h': Piski('.','.','.','.'); break;
	case 'i': Piski('.','.'); break;
	case 'j': Piski('.','-','-','-'); break;
	case 'k': Piski('-','.','-'); break;
	case 'l': Piski('.','-','.','.'); break;
	case 'm': Piski('-','-'); break;
	case 'n': Piski('-','.'); break;
	case 'o': Piski('-','-','-'); break;
	case 'p': Piski('.','-','-','.'); break;
	case 'q': Piski('-','-','.','-'); break;
	case 'r': Piski('.','-','.'); break;
	case 's': Piski('.','.','.'); break;
	case 't': Piski('-'); break;
	case 'u': Piski('.','.','-'); break;
	case 'v': Piski('.','.','.','-'); break;
	case 'w': Piski('.','-','-'); break;
	case 'x': Piski('-','.','.','-'); break;
	case 'y': Piski('-','.','-','-'); break;
	case 'z': Piski('-','-','.','.'); break;
	
	case '1': Piski('.','-','-','-','-'); break;
	case '2': Piski('.','.','-','-','-'); break;
	case '3': Piski('.','.','.','-','-'); break;
	case '4': Piski('.','.','.','.','-'); break;
	case '5': Piski('.','.','.','.','.'); break;
	case '6': Piski('-','.','.','.','.'); break;
	case '7': Piski('-','-','.','.','.'); break;
	case '8': Piski('-','-','-','.','.'); break;
	case '9': Piski('-','-','-','-','.'); break;
	case '0': Piski('-','-','-','-','-'); break;

	case '.': Piski('-', '-', '.', '.', '-', '-'); break;
	case ',': Piski('.', '-', '.', '-', '.', '-'); break;
	case ' ': 
		if (wynikDoStringa)
		{
			przetlumaczony.push_back('_');
		}
		else
		{
			Sleep(WordPause);
		}
		break;
	default: Beep(200, 1000); break;
	}

	return;
}

//Uniwersalny string morsa
// kreska - '-', kropka - '.', przerwa - '|', spacja - '_'
std::string morse::Translator(std::string textDoPrzetlumaczenia)
{
	przetlumaczony = "";

	for (size_t i = 0; i < textDoPrzetlumaczenia.size(); i++)
	{
		if ( textDoPrzetlumaczenia[i] == ' ' ||
			!( std::isalnum(textDoPrzetlumaczenia[i]) || std::ispunct(textDoPrzetlumaczenia[i]) ) )
		{
			przetlumaczony.push_back(' ');
		}

		Translator(textDoPrzetlumaczenia[i]);
	}
	przetlumaczony.pop_back();	//na koncu zawsze jest niepotrzebny '|'

	for (size_t i = 0; i < przetlumaczony.size(); i++)
	{
		if (i+1 != przetlumaczony.size())
		{
			if (przetlumaczony[i] == '|')
			{
				i++;
				if (przetlumaczony[i] == ' ')
				{
					przetlumaczony.erase(przetlumaczony.begin() + i);
					i--;
					przetlumaczony.erase(przetlumaczony.begin() + i);
				}
			}
		}
	}

	return przetlumaczony;
}

const morse& morse::operator=(const morse& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	Frequency = drugi.Frequency;
	DotTime = drugi.DotTime;
	DashTime = drugi.DashTime;
	Pause = drugi.Pause;
	CharPause = drugi.CharPause;
	WordPause = drugi.WordPause;
	wynikDoStringa = drugi.wynikDoStringa;
	przetlumaczony = drugi.przetlumaczony;

	return *this;
}