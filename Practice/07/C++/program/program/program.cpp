
#include <iostream>

int main()
{
	setlocale(LC_ALL, "RUS");
	int x;
	std::cout << "выберите способ 1 - по длинам сторон; 2 -по координатам ";
	std::cin >> x;
	if (x - 1)
	{
		double x1, x2, x3, y1, y2, y3;
		std::cin >> x1 >> y1;
		std::cin >> x2 >> y2;
		std::cin >> x3 >> y3;
		double s = 0.5 * abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
		std::cout << "S = " << s;
	}
	else
	{
		double a, b, c, p, s;
		std::cin >> a >> b >> c;
		p = (a + b + c) / 2;
		s = sqrt(p * (p - a) * (p - b) * (p - c));
		std::cout << "S = " << s;
	}
}
