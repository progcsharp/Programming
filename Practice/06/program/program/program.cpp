
#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int a, b, c, d, x_1, x_2;
    std::cin >> a >> b >> c;
    d = b * b - 4 * a * c;
    if (d > 0)
    {
        x_1 = (-b + sqrt(d)) / 2 * a;
        x_2 = (-b - sqrt(d)) / 2 * a;
        std::cout << "x_1 = " << x_1 << "\n" << "x_2 = " << x_2;
    }
    else if (d == 0)
    {
        x_1 = -b / 2 * a;
        std::cout << "x = " << x_1;
    }
    else
    {
        std::cout << "нет корней";
    }


}