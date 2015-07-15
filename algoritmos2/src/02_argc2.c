#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("Uso:\n\t%s [numero]\n", argv[0]);
		return 1;
	}

	long suma = 0;
	for(char **p = argv + 1; *p != NULL; p++) {
		char *test;
		suma += strtol(*p, &test, 10);
		if(*test) {
			printf("El argumento \"%s\" no es un numero!\n", *p);
			return 1;
		}
	}

	printf("La suma es: %li\n", suma);

	return 0;
}
