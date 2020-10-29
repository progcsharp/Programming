#include <iostream>

int main()
{
	int y, x;
	std::cin >> x >> y;
	int c = x;
	for (int i = 1;i < y;i++) {
		x = x * c;
	}
	std::cout << x;
}