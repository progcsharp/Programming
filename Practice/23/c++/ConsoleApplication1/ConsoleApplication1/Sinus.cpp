#include "Sinus.h"
#include <cmath>
#include "Header.h"

float Sin(float o)
{
	float c = 0;
	for (int n = 0; n <= 4; n++) {
		c = c + pow(-1, n) * pow(o, 2 * n + 1) / Factorial(2 * n + 1);
	}
	return c;
}
