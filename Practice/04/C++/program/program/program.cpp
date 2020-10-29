
#include <iostream>
int main()
{
    int a, b;
    std::cin >> a >> b;
    int c = b;
    b = a;
    a = c;
    std::cout << a << " " << b;

    int n, k;
    std::cin >> n >> k;


}

int exch(int x, int y) {
    x = y;
    y = x;
}
