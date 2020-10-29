#include <iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b;
    std::cout << a + b << "\n" << a - b << "\n" << a * b << "\n" << a / b;

    double k, n;
    std::cin >> k >> n;
    std::cout << k + n << "\n" << k - n << "\n" << k * n << "\n" << k / n;

    std::cin >> k >> c;
    std::cout << k + c << "\n" << k - c << "\n" << k * c << "\n" << k / c;

    std::cin >> c >> n;
    std::cout << c + n << "\n" << c - n << "\n" << c * n << "\n" << c / n;

}
