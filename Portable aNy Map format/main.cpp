#include <iostream>
#include "ppm.h"

int main()
{
	obraz* obraz1;
	obraz1 = new ppm("lena.ppm");

	int kolor;

	kolor = liczkolory(*obraz1);

	std::cout << "Liczba unikalnych kolorow w obrazie ";
	std::cout << kolor;

	delete obraz1;

	return 0;
}

//Trzeba tez zrobic osobne klasy dla innych formatow