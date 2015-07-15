#include <stdio.h>
#include <string.h>
#include "es.h"

int es_validar_y_abrir(int argc, char* argv[], FILE** entrada, FILE** salida) {
	(*entrada) = stdin;
	(*salida) = stdout;
	int i = 1;
	int retorno = EJECUCION_EXITOSA;
	while (i < argc - 1) {
		if ((strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "-o") == 0)) {
			if (strcmp(argv[i], "-i") == 0) {
				if (((*entrada) = fopen(argv[i + 1], "r")) == NULL)
					retorno = ES_ERRONEOS;
			}
			if (strcmp(argv[i], "-o") == 0) {
				if (((*salida) = fopen(argv[i + 1], "w")) == NULL)
					retorno = ES_ERRONEOS;
			}
		} else {
			retorno = ARGUMENTOS_INVALIDOS;
		}
		i = i + 2;
	}
	return retorno;
}

void es_cerrar_archivos(FILE*entrada, FILE*salida) {
	if (entrada != stdin && entrada != NULL)
		fclose(entrada);
	if (salida != stdout && salida != NULL)
		fclose(salida);
}
