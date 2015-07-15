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

	int alloc = 16;
	int size = 0;

	int *v = (int *)malloc(alloc * sizeof(int));
	if(v == NULL)
		return NULL;

	int n;
	while((n = fread(v + size, sizeof(int), alloc - size, f)) == alloc - size) {
		size = alloc;
		alloc *= 2;
		int *aux = (int *)realloc(v, alloc * sizeof(int));
		if(aux == NULL) {
			free(v);
			return NULL;
		}
		v = aux;
	}

	*pn = n + size;
	return v;
}
