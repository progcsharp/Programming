#include "Header.h"

int Factorial(int i)
{
	int n = 1;
	for (i; i > 0; i--) {
		n = n * i;
	}
	return n;
}
