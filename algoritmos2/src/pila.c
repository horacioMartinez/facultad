#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

#define TAM 10
#define TAMB 5

struct _pila {
    void** datos;
    size_t tamanio;
    size_t cantidad;
};


pila_t *pila_crear(){
	pila_t *pila= malloc(sizeof(pila_t));
	if (pila==NULL)
		return NULL;
	pila->datos= malloc(TAM*sizeof(void*));
	pila->tamanio=0;
	pila->cantidad=0;
	return pila;
}

void pila_destruir(pila_t *pila) {

	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	if (pila->cantidad==0)
			return true;
	return false;
}

bool pila_apilar(pila_t *pila, void* valor){
	void** datos_nuevos;
	(pila->cantidad) ++;
	if ( (pila->cantidad ) > (pila->tamanio) ){
		datos_nuevos= realloc( (pila->datos) , ( (pila->cantidad) + TAM) * sizeof(void*));
		if (datos_nuevos==NULL)
			return false;
		(pila->tamanio)=( (pila->cantidad) + TAM );
		pila->datos=datos_nuevos;
	}

	pila->datos[pila->cantidad-1] =valor;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if (pila->cantidad==0)
		return NULL;
	return (pila->datos[(pila->cantidad)-1]);
}

void* pila_desapilar(pila_t *pila){
	void *aux,**datos_nuevos;
	if (pila->cantidad==0)
		return NULL;

	aux=pila->datos[pila->cantidad-1];
	pila->datos[pila->cantidad-1]=NULL;
	pila->cantidad--;

	if ( (pila->cantidad) < (pila->tamanio -TAMB -TAM) )
		(pila->tamanio)=( (pila->cantidad) + TAMB );
		datos_nuevos= realloc( (pila->datos) , ( (pila->cantidad) + TAMB) * sizeof(void*));
		if (datos_nuevos==NULL)
			return NULL;
		pila->datos=datos_nuevos;
	return aux;
}
