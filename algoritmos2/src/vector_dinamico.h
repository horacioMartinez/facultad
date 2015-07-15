#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct vector vector_t;

// Crea un vector de tama�o tam
// Post: vector es una vector vac�o de tama�o tam
vector_t* vector_crear(size_t tam);

// Destruye el vector
// Pre: el vector fue creado
// Post: se eliminaron todos los elementos del vector
void vector_destruir(vector_t *vector);

// Cambia el tama�o del vector
// Pre: el vector fue creado
// Post: el vector cambi� de tama�o a nuevo_tam y devuelve true
// o el vector queda intacto y devuelve false si no se pudo cambiar el tama�o
// a nuevo_tam
bool vector_redimensionar(vector_t *vector, size_t nuevo_tam);

// Almacena en valor el dato guardado en la posici�n pos del vector
// Pre: el vector fue creado
// Post: se almacen� en valor el dato en la posici�n pos. Devuelve false si la
// posici�n es inv�lida (fuera del rango del vector, que va de 0 a tama�o-1)
void* vector_obtener(vector_t *vector, size_t pos);

// Almacena el valor en la posici�n pos
// Pre: el vector fue creado
// Post: se almacen� el valor en la posici�n pos. Devuelve false si la posici�n
// es inv�lida (fuera del rango del vector, que va de 0 a tama�o-1) y true si
// se guard� el valor con �xito.
bool vector_guardar(vector_t *vector, int pos, void* valor);

// Devuelve el tama�o del vector
// Pre: el vector fue creado
size_t vector_obtener_tamanio(vector_t *vector);

// Devuelve la cantidad de elementos del vector
size_t vector_obtener_cantidad(vector_t *vector);

#endif // VECTOR_DINAMICO_H
