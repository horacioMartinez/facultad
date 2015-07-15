#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {
	if(argc < 2 || argc > 3) {
		fprintf(stderr, "Uso: %s (<origen>) <destino>\n", argv[0]);
		return 1;
	}

	FILE *fi, *fo;

	if((fo = fopen(argv[argc - 1], "wb")) == NULL) {
		fprintf(stderr, "Fallo abrir \"%s\"\n", argv[argc - 1]);
		return 1;
	}

	if(argc == 2)
		fi = stdin;
	else if((fi = fopen(argv[1], "rt")) == NULL) {
		fprintf(stderr, "Fallo abrir \"%s\"\n", argv[1]);
		return 1;
	}

	char buffer[MAX_BUF];
	int n;

	if(fi == stdin)
		printf("Ingrese la cantidad de elementos: ");
	fgets(buffer, MAX_BUF, fi);
	n = atoi(buffer);	// Deberíamos validar tanto que sea numérico como que sea >0.

	fwrite(&n, sizeof(int), 1, fo);

	for(int i = 0; i < n; i++) {
		if(fi == stdin)
			printf("Ingrese el valor numero %d: ", i + 1);

		int val = atoi(fgets(buffer, MAX_BUF, fi));
		fwrite(&val, sizeof(int), 1, fo);
	}

	if(fi != stdin)
		fclose(fi);

	if(fclose(fo) == EOF) {
		fprintf(stderr, "Ocurrio algun error!\n");
		return 1;
	}

	return 0;
}

