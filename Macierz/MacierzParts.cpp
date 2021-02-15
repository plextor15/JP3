#include <iostream>
#include "macierz.h"

int main()
{
    macierz A, B, C, D;

    A.set(0, 0, 1.0);
    A.set(0, 1, 2.0);
    A.set(1, 0, 3.0);
    A.set(1, 1, 4.0);

    B = A;

    B.set(0, 0, 5.0);


    C = A * B;
    D = B * A;

    if (!(C == D)) std::clog << "rowne";

    //MOJ DEBUG
    std::clog << "Macierz A";
    A.Debug();
    std::clog << "Macierz B";
    B.Debug();
    std::clog << "Macierz C";
    C.Debug();
    std::clog << "Macierz D";
    D.Debug();

    if (C == D) {
        std::clog << "rowne";
    }
    else {
        std::clog << "nierowne";
    }

    std::getchar();
    return 0;
}