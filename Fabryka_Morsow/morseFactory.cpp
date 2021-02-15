/*
*	Klasa: morseFactory
*	Autor: Adam Porembinski
*	Opis: Mozliwosc nadawania morsem do: glosnika, do pliku, na konsole, i miganie "dioda"
*
*	18.01.2021	stworzenie klasy, wstepne metody
*	20.01.2021	wykrywanie typu danych external i ich odczytywanie, robienie parsera, debug parsera
*	20.01.2021	dodanie obslugi urzadzenia beep
*	23.01.2021	dodanie obslugi urzadzenia blink
*	24.01.2021	debug ustawiania parametrow
*/

#include "morseFactory.h"

morseFactory::morseFactory()
{
	czyPlik = false;
	urzadzenieDocelowe = __EMPTY_;
	parametry.resize(0);
}

morseFactory::morseFactory(const morseFactory& mf)
{
	czyPlik = mf.czyPlik;
	urzadzenieDocelowe = mf.urzadzenieDocelowe;
	parametry = mf.parametry;
}

morseFactory::~morseFactory()
{
	parametry.clear();
	parametry.shrink_to_fit();
}

void morseFactory::_parser(std::string ciag)
{
	std::vector<std::string> skladaneParametry;
	std::string tmp = "";
	int naInta;

	for (size_t i = 0; i < ciag.size(); i++)
	{
		if ( std::isdigit(ciag[i]) )
		{
			tmp.push_back(ciag[i]);
		}
		else if (ciag[i] == ' ')
		{
			skladaneParametry.push_back(tmp);
			tmp = "";
		}
	}
	skladaneParametry.push_back(tmp);

	for (size_t i = 0; i < skladaneParametry.size(); i++)
	{
		naInta = std::stoi(skladaneParametry[i]);
		parametry.push_back(naInta);
	}

	return;
}

void morseFactory::_parametryZPliku(std::string pliczek)
{
	std::string daneZPliku = "";
	std::ifstream plikZParam;
	
	plikZParam.open(pliczek);

	if (plikZParam.good())
	{
		std::getline(plikZParam, daneZPliku);
	}
	
	plikZParam.close();

	_parser(daneZPliku);
	return;
}

void morseFactory::setExternalInfo(std::string param)
{
	if (parametry.size() != 0)	//trzeba przygotowac sie na nowe dane
	{
		czyPlik = false;

		parametry.clear();
		parametry.shrink_to_fit();
	}

	//sprawdzenie z czy ma do czynienia z plikiem
	for (size_t i = 0; i < param.size(); i++)
	{
		if (param[i] == '.')
		{
			czyPlik = true;
		}
	}

	if (czyPlik)
	{
		_parametryZPliku(param);
	}
	else
	{
		_parser(param);
	}

	return;
}

void morseFactory::setOutput(opcjeDocelowe wybraneUrzadzenie)
{
	urzadzenieDocelowe = wybraneUrzadzenie;
	return;
}

void morseFactory::convert(std::string doPrzekonwertowania)
{
	//jak sie uzyje switcha to VS wywala blad, ze bypass inicjalizacji
	//chodzi o to zeby tworzyv obiekt wtedy kiedy jest potrzebny

	if (urzadzenieDocelowe == 0)	//pusty
	{
		return;
	}

	if (urzadzenieDocelowe == 1)	//beep
	{
		beep bip;
		std::cout << parametry[0] << "  " << parametry[1];
		bip.Set_parametry(parametry[0], parametry[1]);
		bip.piszczenie(doPrzekonwertowania);
		return;
	}

	if (urzadzenieDocelowe == 2)	//Disk
	{
		Disk dysk;
		dysk.Set_parametry(parametry[2], parametry[3], parametry[4], parametry[5]);
		dysk.Set_plikWejsciowy("DiskWynikKonwert.txt");
		dysk.pisanieDoPliku(doPrzekonwertowania);
	}

	if (urzadzenieDocelowe == 3)	//Blink
	{
		Blink dioda;
		dioda.Set_parametry(parametry[0], parametry[6]);
		dioda.Set_pozycjaDiody(8, 5);
		dioda.mruganie(doPrzekonwertowania);
	}

	if (urzadzenieDocelowe == 4)	//Console
	{
		Console konsola;
		konsola.Set_parametry((char)parametry[2], (char)parametry[3]);
		konsola.wypisywanie(doPrzekonwertowania);
	}
		
	return;
}

void morseFactory::convert(int doPrzekonwertowania)
{
	std::string zIntdoString = std::to_string(doPrzekonwertowania);
	convert(zIntdoString);
	return;
}

void morseFactory::convert(float doPrzekonwertowania)
{
	std::string zFloatdoString = std::to_string(doPrzekonwertowania);
	convert(zFloatdoString);
	return;
}

void morseFactory::convert(double doPrzekonwertowania)
{
	std::string zDoubledoString = std::to_string(doPrzekonwertowania);
	convert(zDoubledoString);
	return;
}

std::string morseFactory::Get_parametry()
{
	std::string parametryString;
	return parametryString;
}

const morseFactory& morseFactory::operator=(const morseFactory& drugi)
{
	if (this == &drugi)
	{
		return *this;
	}

	czyPlik = drugi.czyPlik;
	parametry = drugi.parametry;
	urzadzenieDocelowe = drugi.urzadzenieDocelowe;
	
	return *this;
}
