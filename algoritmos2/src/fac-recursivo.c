#include <stdio.h>
#include <stdlib.h>

int fac(int n)
{
	if (n == 0) return 1;
	return n * fac(n - 1);
}

int main(int argc, char** argv)
{
	printf("fac recursivo: %d\n", fac(atoi(argv[1])));
}

