#include <iostream>
#include "Header.h"
#include <iomanip>
#include "Sochetanie.h"
#include "Sinus.h"

int main()
{
    std::cout << "n" << "\t" << "n!\n";
    for (int n = 0;n <= 10;n++) {
        std::cout << n << "\t" << Factorial(n) << "\n";
    }
    std::cout << "\n";

    float pi = 3.14;
    for (float x = 0; x <= pi / 4;x = x + pi / 180)
    {
        std::cout << x << "\t" << std::setprecision(4) << Sin(x) << "\n";
    }
    std::cout << "\n";

    std::cout << "k" << "\t" << "c(k, 10)\n";

    for (int k = 1; k <= 10;k++)
    {
        std::cout << k << "\t" << Soch(k,10) << "\n";
    }
}

