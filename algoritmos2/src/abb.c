#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "abb.h"
#include <stdio.h>
#include "pila.h"

struct abb_nodo {
	char* clave;
	struct abb_nodo* izq;
	struct abb_nodo* der;
	void* dato;
};

struct abb {
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
	pila_t* pila;
	abb_nodo_t* actual;
	};

char *copiarstring (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t *abb=malloc(sizeof(abb_t));
	if (abb==NULL) return NULL;

	abb->raiz=NULL;
	abb->cantidad=0;
	abb->cmp=cmp;
	abb->destruir_dato=destruir_dato;
	return abb;
	}

abb_nodo_t* crear_nodo(const char* clave, void* dato){

	if (!clave) return NULL;
	abb_nodo_t *nodo=malloc(sizeof(abb_nodo_t));
	char *aux=(char*)copiarstring(clave);
	nodo->clave=aux;
	nodo->dato=dato;
	nodo->izq=NULL;
	nodo->der=NULL;
	
	return (nodo);
	}

bool abb_guardar_r(abb_nodo_t **nodo, const char *clave, void* dato, abb_t *arbol) {

	if (*nodo == NULL) {
		*nodo= malloc(sizeof(abb_nodo_t));
		char *aux= (char*)copiarstring(clave);
		(*nodo)->clave=aux;
		(*nodo)->dato=dato;
		(*nodo)->izq=NULL;
		(*nodo)->der=NULL;

		if (*nodo!=NULL) {
			arbol->cantidad++;
			if ( (arbol->raiz)==NULL)
				arbol->raiz=*nodo;
			return true;
		}
		return false;
	}

	
	if (arbol->cmp(clave, (*nodo)->clave)==0) {
		if ( (*nodo)->dato != dato){
			if (arbol->destruir_dato)
				arbol->destruir_dato((*nodo)->dato);
		}
		(*nodo)->dato=dato;
		return true;
	}
	if (arbol->cmp(clave, (*nodo)->clave)<0)
		return abb_guardar_r(&((*nodo)->izq),clave,dato,arbol);

	return abb_guardar_r(&((*nodo)->der),clave,dato,arbol);
}



bool abb_guardar(abb_t *arbol, const char *clave, void* dato) {

	if (!arbol) return false;
	if (!clave) return false;
	return abb_guardar_r(&arbol->raiz,clave,dato,arbol);
}


bool abb_pertenece_r(abb_nodo_t **nodo, const char *clave,abb_comparar_clave_t cmp) {

	if (*nodo!=NULL) {
		if(cmp (clave, (*nodo)->clave)==0)  return true;

	}
	
	if (cmp((*nodo)->clave, clave)<0 && (*nodo)->der){
		return abb_pertenece_r(&((*nodo)->der), clave, cmp);
		}
		
	if (cmp((*nodo)->clave, clave)>0 && (*nodo)->izq){
		return abb_pertenece_r(&((*nodo)->izq), clave, cmp);
		}
			
	if(*nodo == NULL) return false;
	return false;
	
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {

	if (!arbol) return false;
	if (!clave) return false;
	if (arbol->cantidad==0) return false;
	abb_nodo_t* nodo= (arbol->raiz);
	return abb_pertenece_r(&nodo,clave, arbol->cmp);
}

size_t abb_cantidad(abb_t *arbol){
	if (!arbol) return 0;
	return (arbol->cantidad);	
	}

void* abb_obtener_r (abb_nodo_t** nodo,const char* clave,abb_comparar_clave_t cmp){
	
	if (*nodo==NULL) return NULL;
	
	if (cmp((*nodo)->clave, clave)==0) return ((*nodo)->dato);

	if (cmp((*nodo)->clave, clave)<0) return abb_obtener_r(&(*nodo)->der,clave,cmp);
	
	return abb_obtener_r(&(*nodo)->izq,clave,cmp);
}


void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo= (arbol->raiz);
	if (!arbol) return NULL;
	if (!clave) return NULL;
	if (arbol->cantidad==0) return NULL;
	
	return abb_obtener_r(&nodo,clave,arbol->cmp);
}


void abb_in_order(abb_t *arbol, bool funcion(const char *, void *, void *), void *extra){
	pila_t *pila =pila_crear();
	abb_nodo_t *nodo= (arbol->raiz);
	if (!arbol) return;
	if (!funcion) return;
	
	nodo=arbol->raiz;

	while (nodo!=NULL) {
		pila_apilar(pila,nodo);
		nodo=nodo->izq;
	}

	while (!pila_esta_vacia(pila)) {
		nodo=pila_desapilar(pila);
		funcion(nodo->clave, nodo->dato, extra);
		if (nodo->der != NULL) {
			nodo=nodo->der;
			pila_apilar(pila,nodo);
			while (nodo->izq != NULL) {
				pila_apilar(pila,nodo->izq);
				nodo=nodo->izq;
			}
		}
	}
	pila_destruir(pila);
}

void* reemplazar(abb_t* arbol, abb_nodo_t **actual, abb_nodo_t **nodo, abb_nodo_t **anterior){

	if ((*actual)->der == NULL){

		abb_nodo_t *nodoaux =malloc(sizeof(abb_nodo_t));
		abb_nodo_t *actualaux=*actual;
		void* dato_aux;

		nodoaux->clave=(*nodo)->clave;
		dato_aux=(*nodo)->dato;
		nodoaux->izq=(*nodo)->izq;
		(*nodo)->clave=(*actual)->clave;
		(*nodo)->dato=(*actual)->dato;

		if ( (*anterior)== (*nodo))
			(*anterior)->izq=(*actual)->izq;
		else
			(*anterior)->der=(*actual)->izq;
		free(nodoaux->clave);
		free(actualaux);
		free(nodoaux);

	    arbol->cantidad--;
	    return dato_aux;
	}

	else
		return reemplazar(arbol, &(*actual)->der, nodo, actual);
}

void* abb_borrar_r(abb_nodo_t **nodo,const char* clave, abb_t* arbol){
  abb_nodo_t *aux;
  void* dato_aux;
  abb_nodo_t *raiz;

  if ( (*nodo) == NULL)
    return NULL;
  if (arbol->cmp((*nodo)->clave, clave)<0 ){
    return abb_borrar_r(&(*nodo)->der, clave, arbol);}
  else if ( arbol->cmp((*nodo)->clave, clave)>0 ){
    return abb_borrar_r(&(*nodo)->izq,clave, arbol);}

  else if (arbol->cmp((*nodo)->clave, clave)==0)
  {
	raiz=arbol->raiz;
	dato_aux=(*nodo)->dato;
	aux = *nodo;

	if ((*nodo)->izq == NULL) {
		*nodo = (*nodo)->der;
		if (  (aux) == raiz )
			arbol->raiz=*nodo;
	}

	else if ((*nodo)->der == NULL) {
		*nodo = (*nodo)->izq;
	    if ( (aux) == raiz  )
	      	  arbol->raiz=*nodo;
	}

	else {
		return reemplazar(arbol, &((*nodo)->izq), nodo, nodo);
	}

	free(aux->clave);
    free(aux);
    arbol->cantidad--;
    return dato_aux;
  }
  return NULL;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	if (!arbol) return NULL;
	return (abb_borrar_r(&(arbol->raiz),clave, arbol));
	}


abb_iter_t* abb_iter_in_crear(const abb_t *arbol){
	if(!arbol) return NULL;
	
	abb_nodo_t* nodo;
	abb_iter_t* iter=malloc(sizeof(abb_iter_t));
		if(!iter) return NULL;
	
	pila_t* pila=pila_crear();
	nodo=arbol->raiz;

	while (nodo!=NULL) {
		pila_apilar(pila,nodo);
		nodo=nodo->izq;
	}
	iter->pila=pila;
	iter->actual=pila_ver_tope(pila);
	return iter;	
	}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	abb_nodo_t* nodoaux;
	if (!iter) return false;
	if (!iter->actual) return false;

	nodoaux=pila_desapilar(iter->pila);
	if (nodoaux->der != NULL) {
		nodoaux=nodoaux->der;
		pila_apilar(iter->pila,nodoaux);
		while (nodoaux->izq != NULL) {
			pila_apilar(iter->pila,nodoaux->izq);
			nodoaux=nodoaux->izq;
		}
	}
	iter->actual=pila_ver_tope(iter->pila);

	return true;
}
	

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	abb_nodo_t* nodo;
	if (!iter) return NULL;
	if (iter->actual==NULL) return NULL;
	nodo=iter->actual;
	return nodo->clave;
	}
	

bool abb_iter_in_al_final(const abb_iter_t *iter){

	if(!iter) return true;
	if(pila_esta_vacia(iter->pila)) return true;
	
	return false;
	}
	
void abb_iter_in_destruir(abb_iter_t* iter){
	if (!iter) return;
	pila_destruir(iter->pila);
	free(iter);
	}

void abb_destruir_r (abb_nodo_t **nodo) {
	abb_nodo_t* nodoizq;
	abb_nodo_t* nododer;
	nodoizq= (*nodo)->izq;
	nododer= (*nodo)->der;
	free( (*nodo)->clave);
	free( (*nodo));
	if (nodoizq) abb_destruir_r(&nodoizq);
	if (nododer) abb_destruir_r(&nododer);
}

void abb_destruir(abb_t *arbol) {
	if (!arbol) return;
	if (! (arbol->raiz) ) return;
	abb_destruir_r (& (arbol->raiz) );
	free(arbol);
}
