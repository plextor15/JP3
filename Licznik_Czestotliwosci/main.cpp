/*
Opis:	Glowny plik do zliczania czestotliwosci
Autor: Adam Porembinski
Data utworzenia: 14.12.2020

28.12.2020  dodanie opisu, includy
29.12.2020  testowanie
03.01.2021  testowanie
07.01.2021  testowanie
08.01.2021  testowanie losowania i kolorow
12.01.2021  komentarze
16.01.2021  testowanie, komentarze
17.01.2021  debug, dodanie interaktywnosci, debug
*/

//#include <iostream>
#include <windows.h>//potrzebne do message boxow
#include "freqcounter.h"
#include "Random.h" //potrzebne do losowania
//#include "ppm.h"    //potrzebne do kolorow

void policzono()    //glownym celem byl debug
{
    MessageBox(NULL, L"Pomyslnie zebrano dane i\nzapisano wyniki.", L"Sukces!", MB_OK | MB_ICONINFORMATION);
    system("CLS");

    return;
}

int main()
{
    srand(time(NULL));      //potrzebne do losowania, zeby przy kazdym uruchomieniu programu wychodzily inne liczby
                            //kompilator moze sie czepiac, ze moze wystapic przeklamanie wartosci, ale chodzi tylko o to zeby wychodzily rozne liczby

    Freqcounter <char> fc_ch_en;
    Freqcounter <char> fc_ch_it;
    Freqcounter <char> fc_ch_pl;
    Freqcounter <std::string> fc_s;
    Freqcounter <ppm::color> fc_kol;
    Freqcounter <int> fc_i;

    //zeby bylo prosciej nazwy plikow sa przekazywane jako stringi
    std::string it = "biblia-it.txt";
    std::string en = "biblia-en.txt";
    std::string pl = "biblia-pl_ksiega_rdzaju.txt";
    std::string pl_3 = "biblia-pl_ksiega_rdzaju_3.txt";
    std::string lena = "lena.ppm";

    std::string liczbyPlik = "wylosowane_liczby._data";
    
    int wyswietlaneRzedy = 20;  //rzedy w exporcie do ppm

    int en_char, it_char, pl_char, pl_string, kolory, losowanie, liczby;

    MessageBox(NULL, 
        L"Zliczanie wystapienia roznego rodzaju danych. \nWyniki sa na biezaco zapisywane.\n\nCancel - zamkniecie programu", 
        L"Licznik czestotliwosci", MB_OK);


    en_char = MessageBox(NULL, L"Czy zliczac znaki dla wersji angielskiej?", L"Zliczanie znakow", MB_YESNOCANCEL);
    switch (en_char)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES
            
        fc_ch_en.zaladowaniePliku(en);
        std::cout << "LICZENIE...";
        fc_ch_en.addData();
        fc_ch_en.zamknieciePliku();
        std::cout << "\nEXPORT...";
        fc_ch_en.exportCSV("CharEN");
            //fc_ch_en.createTable();
            //std::cout << "\nEXPORT PPM\n";//DEBUG ONLY
        fc_ch_en.exportPPM("CharEN", fc_ch_en.Get_ileDanych(), 50);
            //std::cout << "\nHISTOGRAM\n";//DEBUG ONLY
            //fc_ch_en.create(fc_ch_en.Get_ileDanych(), 20);
            //system("PAUSE"); system("CLS");//zeby mie ucieklo
        policzono();
    }
    
    it_char = MessageBox(NULL, L"Czy zliczac znaki dla wersji wloskiej?", L"Zliczanie znakow", MB_YESNOCANCEL);
    switch (it_char)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES
            //std::cout << "\nIT ";
        fc_ch_it.zaladowaniePliku(it);
        std::cout << "LICZENIE...";
        fc_ch_it.addData();
        fc_ch_it.zamknieciePliku();
        std::cout << "\nEXPORT...";
        fc_ch_it.exportCSV("CharIT");
            //fc_ch_it.createTable(); system("PAUSE");
        fc_ch_it.exportPPM("CharIT", fc_ch_it.Get_ileDanych(), 50);
            //fc_ch_it.create(fc_ch_it.Get_ileDanych(), 20);
            //system("PAUSE"); system("CLS");//zeby mie ucieklo
        policzono();
    }
    
    pl_char = MessageBox(NULL, L"Czy zliczac znaki dla wersji polskiej?", L"Zliczanie znakow", MB_YESNOCANCEL);
    switch (pl_char)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES
            //std::cout << "\nPL";
        fc_ch_pl.zaladowaniePliku(pl);
        std::cout << "LICZENIE...";
        fc_ch_pl.addData();
        fc_ch_pl.zamknieciePliku();
        std::cout << "\nEXPORT...";
        fc_ch_pl.exportCSV("CharPL");
            //fc_ch_pl.createTable();
        fc_ch_pl.exportPPM("CharPL", fc_ch_pl.Get_ileDanych(), 50);
            //fc_ch_pl.create(fc_ch_pl.Get_ileDanych(), 20);
            //system("PAUSE"); system("CLS");//zeby mie ucieklo
        policzono();
    }
    
    pl_string = MessageBox(NULL, L"Czy zliczac slowa dla wersji polskiej?", L"", MB_YESNOCANCEL);
    switch (pl_string)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES
            //std::cout << "\n\nZliczanie wystapienia kazdego slowa w biblii PL";
        fc_s.zaladowaniePliku(pl);
        std::cout << "LICZENIE...";
        fc_s.addData();
        fc_s.zamknieciePliku();
            //std::cout << "EXPORT\n\n";
        //fc_s.exportCSV("StringPL");
            //fc_s.createTable(100);   //poczatkowe daja czytelny wynik NIE ZWIEKSZAC, NIE POLEPSZY TO WIDOCZNOSCI
        //fc_s.create(20, 10);        //im dalej tym wiecej slow wystepuje tyle samo razy
        //fc_s.exportPBM("StringPL.pbm", 20, 100);
            //system("PAUSE"); system("CLS");//zeby mie ucieklo
        policzono();
    }

    //Najlepiej miec obrazek bez komentarzy, co zaoszczedzi czas na formatowanie
    kolory = MessageBox(NULL, L"Czy zliczac kolory?", L"", MB_YESNOCANCEL);
    switch (kolory)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES
            //std::cout << "\nZliczanie wystapienia kazdego koloru w lena.ppm";
        fc_kol.zaladowaniePliku(lena);
        std::cout << "LICZENIE... (caly proces trwa ok 3 min dla lena.ppm)";
        fc_kol.addData();
        fc_kol.zamknieciePliku();
        //std::cout << "\nEXPORT\n\n";
            //fc_kol.exportCSV("kolory");     //proby wyswietlenia wyniku nie wygladaja zbyt dobrze,
                                        //bo duzo kolorow wystepuje podobna ilosc razy
            //fc_kol.createTable();
        //system("PAUSE"); //system("CLS");//zeby mie ucieklo
        policzono();
    }

    liczby = MessageBox(NULL, L"Czy zliczac liczby?", L"", MB_YESNOCANCEL);
    switch (liczby)
    {
    case 7:     //NO
        break;
    case 2:     //CANCEL
        return 0;

    case 6:     //YES

        //Osobno losowanie, zeby zapelnic plik liczbami
        losowanie = MessageBox(NULL, L"Czy wylosowac liczby?\nNie ma potrzeby lowowac jesli\nistnieje plik \"wylosowane_liczby._data\'.", L"Losowanie", MB_YESNOCANCEL);
        switch (losowanie)
        {
        case 7:     //NO
            break;
        case 2:     //CANCEL
            return 0;

        case 6:     //YES
            std::cout << "Losowanie liczb...\n";
            Random los;
            los.wylosuj(0, 1000, 1000000);  //ustawianie ile powtorzen
            los.zapis(liczbyPlik);
            los.czyszczenie();
        }

        //Najpierw musi byc plik z losowymi liczbami
        //  std::cout << "\n\nZliczanie wystapienia wylosowanych liczb";   //export
        fc_i.zaladowaniePliku(liczbyPlik);
        std::cout << "LICZENIE...";
        fc_i.addData();
        fc_i.zamknieciePliku();
        std::cout << "\nEXPORT...";
        fc_i.exportCSV("liczby");
            //fc_i.createTable();             //tutaj sa wyswietlane wszystkie
            //fc_i.create(100, 10);
        fc_i.exportPPM("Liczby", 100, 60);
        //system("PAUSE"); system("CLS");//zeby mie ucieklo
        policzono();
    }
    


    //histogramy, bardziej poreczne sa wygenerowane pliki CSV
        //std::cout << "\n\nRobienie histogramow:";
    int tabelki = MessageBox(NULL, L"Czy wyswietlic tabele z danymi?\nPowiekszenie okna w pionie moze polepszyc widocznosc.", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
    int tabelka;
    int exit = true;

    if (tabelki == 6)
    {
        exit = false;

        tabelka = MessageBox(NULL, L"Czy wyswietlic tabele z danymi\nwystapienia kazdego znaku PL?", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
        if (tabelka == 6)
        {
            std::cout << "\nWystapienia kazdego znaku PL:\n\n";
            fc_ch_pl.createTable();
        }
        
        tabelka = MessageBox(NULL, L"Czy wyswietlic tabele z danymi\nz wystapienia kazdego znaku IT?", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
        if (tabelka == 6)
        {
            system("CLS");
            std::cout << "\nWystapienia kazdego znaku IT:\n\n";
            fc_ch_it.createTable();
        }

        tabelka = MessageBox(NULL, L"Czy wyswietlic tabele z danymi\nz wystapienia kazdego znaku EN?", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
        if (tabelka == 6)
        {
            system("CLS");
            std::cout << "\nWystapienia kazdego znaku EN:\n\n";
            fc_ch_en.createTable();
        }

        tabelka = MessageBox(NULL, L"Czy wyswietlic tabele z danymi\nz wystapienia kazdego slowa PL?\n\n(Nie wyglada to zbyt dobrze pod koniec)", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
        if (tabelka == 6)
        {
            system("CLS");
            std::cout << "\nWystapienia kazdego slowa PL:\n\n";
            fc_s.createTable();
        }

        tabelka = MessageBox(NULL, L"Czy wyswietlic tabele z danymi\nz losowania liczb?", L"Tabele", MB_YESNO | MB_ICONINFORMATION);
        if (tabelka == 6)
        {
            system("CLS");
            std::cout << "\nIle raz wylosowana zostanie liczba 1-1000:\n\n";
            fc_i.createTable();
        }

        std::cout << "\n\nKONIEC";
        MessageBox(NULL, L"Pomyslnie zakonczono dzialanie", L"Sukces!", MB_OK | MB_ICONINFORMATION);
    }
    
    if (exit)
    {
        system("CLS");
        std::cout << "\nKONIEC\n";
        MessageBox(NULL, L"Pomyslnie zakonczono dzialanie", L"Sukces!", MB_OK | MB_ICONINFORMATION);
    }
    
    return 0;
}

/*
Zliczamy wystapienia kazdego znaku w biblii PL, IT, EN
Zliczamy wystapienie kazdego slowa w biblii PL
Zliczamy wystapienie kazdego koloru w Lenie
Zliczamy ile raz wylosowana zostanie liczba 1-1000 przy losowaniu 1000000 liczb z tego zakresu


Do zrealizowania jest szablon pozwalajacy na stworzenie ponizszych obiektow:

freqcounter <color> fc_c;
freqcounter <char> fc_ch;
freqcounter <string> fc_s;
freqcounter <int> fc_i;

oraz metody:

addData(int);
addData(char);
addData(string);
addData(color);

create();
*/