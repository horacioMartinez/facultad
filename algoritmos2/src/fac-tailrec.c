#include <stdio.h>
#include <stdlib.h>

int _fac(int n, int accum)
{
	if (n == 0) return accum;
	return _fac(n - 1, n * accum);
}

int fac(int n)
{
	return _fac(n, 1);
}

int main(int argc, char** argv)
{
	printf("fac recursivo: %d\n", fac(atoi(argv[1])));
}

