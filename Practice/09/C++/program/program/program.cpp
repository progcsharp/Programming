
#include <iostream>

int main()
{
a:
	setlocale(LC_ALL, "RUS");
	int h1, m1, h2, m2;
	std::cin >> h1 >> m1;
	std::cin >> h2 >> m2;
	if (abs(h1 - h2) > 0)
	{
		if (abs(h1 - h2) > 1)
		{
			std::cout << "встреча не состоится";
		}
		else
		{
			if (m1 > m2)
			{
				if (m2 + 60 - 15 <= m1)
				{
					std::cout << "встреча состоится";
				}
				else
				{
					std::cout << "встреча не состоится";

				}
			}
			else
			{
				if (m1 + 60 - 15 <= m2)
				{
					std::cout << "встреча состоится";
				}
				else
				{
					std::cout << "встреча не состоится";
				}
			}
		}

	}
	else if (h1 == h2)
	{
		if (abs(m1 - m2) <= 15) {
			std::cout << "встреча состоится";
		}
		else
		{
			std::cout << "встреча не состоится";
		}
	}

}