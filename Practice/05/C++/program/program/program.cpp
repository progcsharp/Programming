
#include <iostream>

int main()
{
    double x, t, v, a = 9.8;
    std::cin >> x >> v >> t;

    double s = x + v * t + a * t * t / 2;
    std::cout << s;
}
