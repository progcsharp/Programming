#include <iostream>

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	std::cin >> n;
	bool t = true;

	for (int i = 2;i <= sqrt(n);i++)
		if (n % i == 0) t = false;



	if (t)std::cout << "простое";
	else std::cout << "не простое";

}

