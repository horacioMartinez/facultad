#include <stdio.h>
#include <stdlib.h>
#include "parseador.h"
#include "parametros.h"
#include "es.h"

int main(int argc, char *argv[]) {
	FILE* archivoEntrada;
	FILE* archivoSalida;
	int aux, c;
	parametros_t parametros;
	valores_iniciales_t valoresIniciales;

	int retorno = es_validar_y_abrir(argc, argv, &archivoEntrada,
			&archivoSalida);
	if (retorno != EJECUCION_EXITOSA) {
		es_cerrar_archivos(archivoEntrada, archivoSalida);
		return retorno;
	}

	aux = parseador_cargar_valores_iniciales(&valoresIniciales, archivoEntrada);
	if (aux == -1)
		return ES_ERRONEOS;

	int largoSenial = valoresIniciales.largo;
	int* senial = malloc(sizeof(int) * largoSenial);
	int* senialAux = malloc(sizeof(int) * largoSenial);
	parseador_parsear_senial(archivoEntrada, senial, largoSenial);
	parseador_parsear_senial(archivoEntrada, senialAux, largoSenial);

	parametros_crear(&parametros, valoresIniciales.largo,
			valoresIniciales.pCero, valoresIniciales.pUno,
			valoresIniciales.varianza, senial, senialAux);
	free(senialAux);

	while (!parseador_fin_de_archivo(archivoEntrada)) {
		c = parseador_parsear_senial(archivoEntrada, senial, largoSenial);
		aux = parametros_calcular_senial(senial, &parametros);
		fprintf(archivoSalida, "%d%c", aux, c);
	}

	es_cerrar_archivos(archivoEntrada, archivoSalida);
	parametros_destruir(&parametros);
	free(senial);
	return retorno;
}
