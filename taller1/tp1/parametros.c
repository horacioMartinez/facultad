#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parametros.h"

float calcularGamma(int n, float pCero, float pUno, float varianza,
		int*senialCero, int* senialUno);
float productoEscalar(int vector1[], int vector2[], int n);
void resta(int vector1[], int vector2[], int vectorRes[], int n);

void parametros_crear(parametros_t* parametros, int n, float pCero, float pUno,
		float varianza, int*senialCero, int* senialUno) {
	if (parametros == NULL)
		return;
	parametros->largo = n;
	parametros->gamma = calcularGamma(n, pCero, pUno, varianza, senialCero,
			senialUno);
	int* senialAux = malloc(sizeof(int) * n);
	resta(senialUno, senialCero, senialAux, n);
	parametros->senialResta = senialAux;
}

void parametros_destruir(parametros_t* parametros) {
	if (parametros->senialResta != NULL)
		free(parametros->senialResta);
}

int parametros_calcular_senial(int* senial, parametros_t *parametros) {
	int res = productoEscalar(senial, parametros->senialResta,
			parametros->largo);
	if (res > parametros->gamma)
		return 1;
	else
		return 0;
}

float calcularGamma(int n, float pCero, float pUno, float varianza,
		int*senialCero, int* senialUno) {
	float gamma;
	gamma = varianza * log(pCero / pUno)
			+ (productoEscalar(senialUno, senialUno, n)
					- productoEscalar(senialCero, senialCero, n)) / 2;
	return gamma;
}

float productoEscalar(int vector1[], int vector2[], int n) {
	int resultado = 0;
	int i;
	for (i = 0; i < n; i++) {
		resultado = resultado + vector1[i] * vector2[i];
	}
	return resultado;
}

void resta(int vector1[], int vector2[], int vectorRes[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		vectorRes[i] = vector1[i] - vector2[i];
	}
	return;
}
