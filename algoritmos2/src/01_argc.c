#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("Uso:\n\t%s [numero]\n", argv[0]);
		return 1;
	}

	long suma = 0;
	for(int i = 1; i < argc; i++)
		suma += atoi(argv[i]);

	printf("La suma es: %li\n", suma);

	return 0;
}
