#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>
	
typedef struct nodo {
	void* datos;
	struct nodo* siguiente;
	} nodo_t;
	
struct cola {
	nodo_t* primero;
	nodo_t* ultimo;
	
	};
	
cola_t* cola_crear(){

	cola_t *cola=malloc(sizeof(cola_t));
		if (cola==NULL) return NULL;
		
	cola->primero=NULL;
	cola->ultimo=NULL;
	
	return cola;		
}

bool cola_esta_vacia(const cola_t *cola){
	if (cola->primero==NULL && cola->ultimo==NULL) return true;
		
	return false;	
	}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	nodo_t *p,*aux;
	p=cola->primero;
	while (p!=NULL){
		if (destruir_dato!= NULL){

			if ( (p->datos) != NULL)
				destruir_dato(p->datos);
		}
		aux=p->siguiente;
		free(p);
		p=aux;
	}
	free(cola);
	}
	
bool cola_encolar(cola_t *cola, void* valor){
	
	nodo_t *n_nodo=malloc(sizeof(nodo_t));
		if (n_nodo==NULL) return false;

	if (cola_esta_vacia(cola)==true){
		cola->primero=n_nodo;
		cola->ultimo=n_nodo;
		n_nodo->datos=valor;
		n_nodo->siguiente=NULL;
		return true;		
		}
		
	cola->ultimo->siguiente=n_nodo;
	cola->ultimo=n_nodo;
	n_nodo->datos=valor;
	n_nodo->siguiente=NULL;
	
	return true;
	}
	
void* cola_ver_primero(const cola_t *cola){
	if (cola->primero == NULL)
		return NULL;
	return (cola->primero->datos);
	}

void* cola_desencolar(cola_t *cola){
	
	void* aux;
	nodo_t* segundo;
	if(cola_esta_vacia(cola)==true) return NULL;
	
	aux=cola->primero->datos;
	segundo=cola->primero->siguiente;
	free(cola->primero);
	cola->primero=segundo;
	if (cola->primero==NULL)
		cola->ultimo=NULL;
	return aux;
	}	

