#include <stdio.h>
#include <stdlib.h>

int *leer_vector(FILE *archivo, int *numero_de_elementos);

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
		return 1;
	}

	FILE *f;
	f = fopen(argv[1], "rb");
	if(f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo.\n");
		return 1;
	}

	int n, *v;

	v = leer_vector(f, &n);

	fclose(f);

	if(v == NULL) {
		fprintf(stderr, "Hubo una falla al leer el archivo.\n");
		return 1;
	}

	printf("%d\n", n);
	for(int i = 0; i < n; i++)
		printf("%d\n", v[i]);

	free(v);

	return 0;
}

int *leer_vector(FILE *f, int *pn) {
	*pn = 0;
	int n;

	if(! fread(&n, sizeof(int), 1, f))
		return NULL;

	int *v = (int *)malloc(n * sizeof(int));
	if(v == NULL)
		return NULL;

	if(fread(v, sizeof(int), n, f) < n) {
		free(v);
		return NULL;
	}

	fgetc(f);
	if(! feof(f)) {
		free(v);
		return NULL;
	}

	*pn = n;
	return v;
}
