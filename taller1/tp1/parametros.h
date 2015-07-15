#ifndef PARAMETROS_H
#define PARAMETROS_H

typedef struct {
	int largo;
	float gamma;
	int* senialResta;
} parametros_t;

// Crea el struct parametros a partir de los valores iniciales y
// las seniales S0 y S1. Si se excuta exitosamente retorna 0,
// si se produce un error retorna -1
void parametros_crear(parametros_t* parametros, int n, float pCero, float pUno,
		float varianza, int*senialCero, int* senialUno);

// Calcula si la señal resultante es un 0 o un 1 a partir de la señal pasada
// y los parametros y la devuelve
int parametros_calcular_senial(int* senial, parametros_t *parametros);

// Libera la memoria de senialResta
void parametros_destruir(parametros_t* parametros);

#endif
