#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

//TIPOS DE DATOS
typedef struct nodo nodo_t;
typedef struct lista lista_t;
typedef struct iter lista_iter_t;


//Primitivas básicas

/*Crea una lista vacia
 * Post:devuelve una lista vacia
 * o devuelve NULL en caso de error.*/
lista_t *lista_crear();

/*Verifica el estado de la lista:si esta vacia o no.
 * Pre: recibe una lista.
 * Post: devuelve verdadero si no hay elementos en la lista
 * y falso en caso contrario.*/
bool lista_esta_vacia(const lista_t *lista);

/*Pone al principio de la lista un elemento.
 * Pre: recibe una lista y el dato que hay que poner al principio.
 * Post: devuelve verdadero si salio todo bien, o falso si hubo
 * un error.*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/*Pone al final de la lista un elemento.
 * Pre:recibe una lista y un dato que hay que poner al final.
 * Post: devuelve verdadero si salio todo bien, o falso si hubo
 * un error.*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/*Borra el primer elemento de la lista.
 * Pre: recibe una lista.
 * Post: borra el primer elemento de la lista en caso
 * de que en la lista haya algo. Caso contrario, devuelve NULL.*/
void *lista_borrar_primero(lista_t *lista);

/*Muestra el primer elemento de la lista.
 * Pre: recibe una lista.
 * Post: devuelve el primer elemento de la lista. Si esta vacia,
 * devuelve NULL.*/
void *lista_ver_primero(const lista_t *lista);


/*Responde cuantos elementos hay en la lista.
 * Pre:recibe una lista.
 * Post: devuelve cuantos elementos hay enlistados.*/
size_t lista_largo(const lista_t *lista);

/*Destruye completamente la lista.
 * Pre: recibe una lista y una funcion que se encarga de 
 * destruir los elementos, o NULL si no es necesaria.
 * Post: la lista ya no existe mas.*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

//Primitivas de iteración

/*Crea una iteracion.
 * Pre: recibe una lista.
 * Post: devuelve una iteracion.*/
lista_iter_t *lista_iter_crear(const lista_t *lista);

/*Avanza una posicion en la lista.
 * Pre: recibe una lista.
 * Post: se avanzo una posicion en la lista y devuelve verdadero.
 * Caso contrario, devuelve falso.*/
bool lista_iter_avanzar(lista_iter_t *iter);

/*Muestra el elemento de la posicion actual.
 * Pre: recibe una interacion.
 * Post: devuelve el elemento que hay en la posicion actual o
 * NULL en caso en que no haya elementos.*/
void *lista_iter_ver_actual(const lista_iter_t *iter);

/*NO SE QUE HACE*/
bool lista_iter_al_final(const lista_iter_t *iter);

/*Destruye la iteracion.
 * Pre: recibe una iteracion.
 * Post: destruye la iteracion totalmente.*/
void lista_iter_destruir(lista_iter_t *iter);

//Primitivas de listas junto con iterador

/*Inserta el elemento en la posicion anterior.
 * Pre:recibe una lista, una iteracion y un dato.
 * Post:se enlisto el elemento despues de la posicion actual.
 * Devuelve verdadero si lo inserto, falso si hubo algun problema.*/
bool lista_insertar(lista_t *lista, lista_iter_t *iter, void *dato);

/*Borra uel elemento de la posicion actual.
 * Pre: recibe una lista y una iteracion.
 * Post: borra el elemento que esta en la posicion actual.
 * En caso de error devuelve NULL.*/
void *lista_borrar(lista_t *lista, lista_iter_t *iter);


#endif // LISTA_H
