#include <stdio.h>
#include <stdlib.h>

int fib(int n)
{
	int f_i = 1;
	int f_i_menos_1 = 1;
	for (int i = 2; i <= n; i++) {
		int aux = f_i + f_i_menos_1;
		f_i_menos_1 = f_i;
		f_i = aux;
	}

	return f_i;
}

int main(int argc, char** argv)
{
	printf("fib iterativo: %d\n", fib(atoi(argv[1])));
}

