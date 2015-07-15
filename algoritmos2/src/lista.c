#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
	void* dato;
	nodo_t*siguiente;
};

struct iter {
	nodo_t *actual;
	nodo_t *anterior;
};

struct lista{
	nodo_t *primero;
	nodo_t *ultimo;
	size_t cantidad;
};


lista_t *lista_crear(){
	lista_t *lista=malloc(sizeof(lista_t));
	if (lista==NULL){
		free(lista);
		return NULL;
		}
		
	lista->primero=NULL;
	lista->ultimo=NULL;
	lista->cantidad=0;
	
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	
	if (lista->cantidad==0) return true;

	return false;
	}
	
bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* n_nodo=malloc(sizeof(nodo_t));
	if(n_nodo==NULL){
		return false;
		}
	
	if(lista_esta_vacia(lista)==true){
		n_nodo->dato=dato;
		n_nodo->siguiente=NULL;
		lista->primero=n_nodo;
		lista->ultimo=n_nodo;
		lista->primero->siguiente=NULL;
		lista->cantidad++;
		return true;
		}
	n_nodo->dato=dato;
	n_nodo->siguiente=lista->primero;
	lista->primero=n_nodo;
	lista->cantidad++;
	return true;
	}
	
bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t *n_nodo=malloc(sizeof(nodo_t));
		if (n_nodo==NULL){
			return false;
			}

	if(lista_esta_vacia(lista)==true){
		n_nodo->dato=dato;
		n_nodo->siguiente=NULL;
		lista->primero=n_nodo;
		lista->ultimo=n_nodo;
		lista->primero->siguiente=NULL;
		lista->cantidad++;
		return true;
		}
	
	lista->ultimo->siguiente=n_nodo;
	n_nodo->dato=dato;
	n_nodo->siguiente=NULL;
	lista->ultimo=n_nodo;
	lista->cantidad++;
	return true;
	}
	
void *lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista)==true) return NULL;
	void *aux;
	if (lista->primero->siguiente==NULL){
		aux=lista->primero->dato;
		free(lista->primero);
		lista->primero=NULL;
		lista->ultimo=NULL;
		lista->cantidad--;
		return aux;
		}
	
	nodo_t *segundo;
	segundo=lista->primero->siguiente;
	aux=lista->primero->dato;
	free(lista->primero);
	lista->primero=segundo;
	lista->cantidad--;
	return aux;	
	}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)==true) return NULL;
	
	return (lista->primero->dato);	
	}
	
void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	nodo_t *aux;
	if (!lista_esta_vacia(lista))
	{
		while(lista->primero!=NULL){
			if (destruir_dato!=NULL){
				if (lista->primero->dato!=NULL)
					destruir_dato(lista->primero->dato);
			}
			aux=lista->primero->siguiente;
			free(lista->primero);
			lista->primero=aux;
			lista->cantidad--;
			}
	}
	free(lista);
	}	
	
lista_iter_t *lista_iter_crear(const lista_t *lista){
	
	lista_iter_t * l_iter=malloc(sizeof(lista_iter_t));
		if (l_iter==NULL){
			return NULL;
			}
			
	if (lista_esta_vacia(lista)==true){
		l_iter->actual=NULL;
		l_iter->anterior=NULL;
		return l_iter;
		}
			
	l_iter->anterior=NULL;
	l_iter->actual=lista->primero;
	return l_iter;
	}
	
bool lista_iter_avanzar(lista_iter_t *iter){
	
	if (iter->actual==NULL) return false;
	
	iter->anterior=iter->actual;
	iter->actual=iter->actual->siguiente;
	return true;
	}
	
void *lista_iter_ver_actual(const lista_iter_t *iter){
	
	if (iter->actual==NULL) return NULL;
	return (iter->actual->dato);
	}

bool lista_iter_al_final(const lista_iter_t *iter){
	if (iter==NULL)
		return false;
	if ( (iter->anterior==NULL) && (iter->actual==NULL) )
		return true;
	if ( (iter->anterior!=NULL) && (iter->actual==NULL) )
			return true;
	return false;
	}
	
void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
	}


//Primitivas de listas junto con iterador

bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato){
	nodo_t *n_nodo=malloc(sizeof(nodo_t));
		if (n_nodo==NULL){
			return false;
		}
	n_nodo->dato=dato;
	if ( (iter->actual==lista->primero) && (iter->anterior==NULL) ){
		lista->primero=n_nodo;
		n_nodo->siguiente=iter->actual;
		iter->actual=n_nodo;
		iter->anterior=NULL;
		lista->primero=n_nodo;
		lista->cantidad++;
		return true;
	}
	iter->anterior->siguiente=n_nodo;
	n_nodo->siguiente=iter->actual;
	iter->actual=n_nodo;
	lista->cantidad++;
	if (iter->actual->siguiente==NULL)
		lista->ultimo=n_nodo;
	return true;
    }
//Supongo que la idea de esta funcion es borrar el dato actual del iterador y devolverlo
void *lista_borrar(lista_t *lista, lista_iter_t *iter){
	void *auxdato;
	nodo_t *auxsig;
	if (iter->actual==NULL)
		return NULL;
	if (iter->actual->dato==NULL){
		auxsig=iter->actual->siguiente;
		free(iter->actual);
		iter->actual=auxsig;
		if (iter->anterior !=NULL)
				iter->anterior->siguiente=iter->actual;
		lista->cantidad--;
		if ( (iter->anterior!=NULL) && (iter->actual==NULL) )
			lista->ultimo=iter->anterior;
		if ( (iter->anterior==NULL) && (iter->actual!=NULL) )
			lista->primero=iter->actual;
		return NULL;
	}
	auxsig=iter->actual->siguiente;
	auxdato=iter->actual->dato;
	free(iter->actual);
	iter->actual=auxsig;
	if (iter->anterior !=NULL)
		iter->anterior->siguiente=iter->actual;
	if ( (iter->anterior!=NULL) && (iter->actual==NULL) )
		lista->ultimo=iter->anterior;
	if ( (iter->anterior==NULL) && (iter->actual!=NULL) )
		lista->primero=iter->actual;
	lista->cantidad--;
	return auxdato;
}
