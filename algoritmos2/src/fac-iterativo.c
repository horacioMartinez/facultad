#include <stdio.h>
#include <stdlib.h>

int fac(int n)
{
	int result = 1;
	while (n > 1) {
		result *= n;
		n--;
	}
	return result;
}

int main(int argc, char** argv)
{
	printf("fac iterativo: %d\n", fac(atoi(argv[1])));
}

