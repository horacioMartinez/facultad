#include <stdio.h>
#include <stdlib.h>
#include "parseador.h"

int parseador_cargar_valores_iniciales(valores_iniciales_t* valoresIniciales,
		FILE* entrada) {
	int n;
	int aux = 0;
	float pCero, pUno, varianza;

	aux = fscanf(entrada, "%d,%f,%f,%f", &n, &pCero, &pUno, &varianza);
	if (aux == -1)
		return aux;
	valoresIniciales->largo = n;
	valoresIniciales->pCero = pCero;
	valoresIniciales->pUno = pUno;
	valoresIniciales->varianza = varianza;
	return aux;
}

char parseador_parsear_senial(FILE* entrada, int* senial, int n) {
	int c = 0;
	int aux = 0;
	int i = 0;
	while (i < n) {
		aux = fscanf(entrada, "%d", &senial[i]);
		if (aux != 1)
			perror("ERROR: ");
		c = fgetc(entrada);
		i++;
	}
	return c;
}

int parseador_fin_de_archivo(FILE * archivo) {
	int c = getc(archivo);
	ungetc(c, archivo);
	if (c == EOF)
		return 1;
	return 0;
}
