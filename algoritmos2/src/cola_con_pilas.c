#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

//----------------------------------------------------------------------

typedef struct {
    pila_t* pila_sacar;   // Pila que se usa para almacenar los dato
    pila_t* pila_reserva; // Pila para hacer el traspaso de elementos
} cola_con_pilas_t;

//----------------------------------------------------------------------

// Saca todos los elementos de la pila1 y los mete en la pila2.
// Pre: pila1 y pila2 fueron creadas.
// Post: pila1 queda vacia, pila 2 ahora tiene los elementos de pila1
//       en orden inverso al que tenian.
void traspasar_elementos(pila_t *pila1, pila_t *pila2) {
    void* aux;
    while(!pila_esta_vacia(pila1)) {
        aux = pila_desapilar(pila1);
        pila_apilar(pila2, aux);
    }
}

//----------------------------------------------------------------------

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_con_pilas_t* cola_crear() {
    cola_con_pilas_t* cola = (cola_con_pilas_t*)malloc(sizeof(cola_con_pilas_t));
    pila_t* pila_aux;

    pila_aux = pila_crear();
    if(pila_aux == NULL) {
        return NULL;
    }
    cola->pila_sacar = pila_aux;
    pila_aux = pila_crear();
    if(pila_aux == NULL) {
        return NULL;
    }
    cola->pila_reserva = pila_aux;

    return cola;

}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_con_pilas_t *cola) {

	void* aux = NULL;

	if (pila_esta_vacia(cola->pila_sacar)) {
		return NULL;
	}
	// Paso todo a la otra pila, de manera que el primer elemento
	// insertado quede en el tope de esta. Luego de sacarlo, vuelvo
	// a poner todos los elementos en la pila principal para que queden
	// en el mismo orden que estaban, que es como se insertaron.
	traspasar_elementos(cola->pila_sacar, cola->pila_reserva);
	aux = pila_desapilar(cola->pila_reserva);
	traspasar_elementos(cola->pila_reserva, cola->pila_sacar);
	return aux;
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_con_pilas_t *cola, void* valor) {
	return pila_apilar(cola->pila_sacar, valor);
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(cola_con_pilas_t *cola) {
    return pila_esta_vacia(cola->pila_sacar);
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(cola_con_pilas_t *cola) {
    return pila_ver_tope(cola->pila_sacar);
}

// Destruye la cola.
// Pre: la cola fue creada.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_con_pilas_t *cola) {
    if(cola != NULL) {
        free(cola->pila_sacar);
        free(cola->pila_reserva);
        free(cola);
    }
}
