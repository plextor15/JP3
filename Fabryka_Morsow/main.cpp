#include "morseFactory.h"					//--- includujemy jedną swoją klasę ---
#include <winuser.h>

int main() {
	morseFactory f; 						//--- tworzymy jeden obiekt ---
	int czyDalej;

	czyDalej = MessageBox(NULL, L"Uzycie BEEP", L"Fabryka Morsow", MB_YESNO);
	if (czyDalej == 6)
	{
		f.setExternalInfo("150 600");			//--- wprowadzamy ustawienia dla BEEP w jednym stringu ---	
		f.setOutput(morseFactory::BEEP); 	    //--- ustawiamy co ma być wykonywane -- tutaj na głośnikach systemowych ---
		f.convert("Ala ma kota"); 				//--- odtwarzany ciąg znaków ---
	}
	
	czyDalej = MessageBox(NULL, L"Uzycie DISK", L"Fabryka Morsow", MB_YESNO);
	if (czyDalej == 6)
	{
		f.setExternalInfo("parametry.txt");		//--- ustawienie parserem nazwy pliku/ścieżki ---
		f.setOutput(morseFactory::DISK); 		//--- ustawienie zapisu w kodzie morsa do pliku ---
		f.convert("Ala ma kota"); 				//--- zapisywany ciąg znaków ---
	}

	czyDalej = MessageBox(NULL, L"i jeszcze liczby", L"Fabryka Morsow", MB_YESNO);
	if (czyDalej == 6)
	{
		f.convert(257); 						//--- zapisana liczba ---
		f.convert(1.23); 						//--- zapisywana liczba dziesiętna ---
	}
	
	czyDalej = MessageBox(NULL, L"Uzycie BLINK", L"Fabryka Morsow", MB_YESNO);
	if (czyDalej == 6)
	{
		f.setExternalInfo("150 0 0 0 0 0 50");	//--- ustawienie parserem dla BLINK ---
		f.setOutput(morseFactory::BLINK); 		//--- ustawienie migania diody na klawiaturze, przy braku diody na klawiaturze zapalanie kursora w konsoli ---
		f.convert("Ala ma kota"); 				//--- odtwarzany ciąg znaków ---
	}

	czyDalej = MessageBox(NULL, L"Uzycie CONSOLE", L"Fabryka Morsow", MB_YESNO);
	if (czyDalej == 6)
	{
		f.setExternalInfo("0 0 42 45");			//--- ustawienie parserem dla CONSOLE ---
		f.setOutput(morseFactory::CONSOLE); 	//--- ustawienie morsa na wyświetlenie na konsoli ---
		f.convert("Ala ma kota"); 				//--- wyświetlany ciąg znaków ---
	}

	MessageBox(NULL, L"Koniec", L"Fabryka Morsow", MB_OK | MB_ICONINFORMATION);
	return 0;
}