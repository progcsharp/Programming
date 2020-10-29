#include <iostream>

int main()
{
	int x, y, z;
	std::string s;
	std::cin >> x >> s >> y;
	if (s == "+") z = x + y;
	else if (s == "-") z = x - y;
	else if (s == "*") z = x * y;
	else if (s == "/") z = x / y;
	else std::cout << "error";
	std::cout << z;
}