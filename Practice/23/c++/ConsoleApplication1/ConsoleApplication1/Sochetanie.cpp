#include "Sochetanie.h"
#include "Header.h"

int Soch(int k, int n)
{
	int c = 0;
	c = Factorial(n) / (Factorial(k) * Factorial(n - k));
	return c;
}
