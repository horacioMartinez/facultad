#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_dinamico.h"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
struct vector
{
	size_t cantidad;
    size_t tam;
    void **datos;
};


/* ******************************************************************
 *                        IMPLEMENTACION
 * *****************************************************************/

// Crea un vector de tama�o tam
vector_t* vector_crear(size_t tam)
{
    vector_t* vector = malloc(sizeof(vector_t));
    if (vector == NULL) return NULL;

    vector->datos = malloc(tam * sizeof(void*));
    if (vector->datos == NULL)
    {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    vector->cantidad=0;
    return vector;
}

// Destruye el vector
void vector_destruir(vector_t *vector)
{
	free(vector->datos);
	free(vector);
}

// Cambia el tama�o del vector
bool vector_redimensionar(vector_t *vector, size_t tam_nuevo)
{
	//vector_t* vectoraux=*vector;
    void* datos_nuevo = realloc( (vector)->datos, tam_nuevo * sizeof(void*));

    if (tam_nuevo > 0 && datos_nuevo == NULL)
    {
        return false;
    }
    (vector)->datos = datos_nuevo;
    (vector)->tam = tam_nuevo;
    return true;
}

// Almacena en valor el dato guardado en la posici�n pos del vector
void* vector_obtener(vector_t *vector, size_t pos)
{
	if ( pos<0 || pos>(vector->tam)-1 || vector->tam == 0)
	{
		return false;
	}
	return (vector->datos)[pos];
}

// Almacena el valor en la posici�n pos, si pos es menor que 0 considera la ultima posicion no ocupada
bool vector_guardar(vector_t *vector, int pos, void* dato)
{
	if (pos<0)
		pos = vector->cantidad;
	if (pos > (vector->tam-1) )
		vector_redimensionar(vector, (pos+vector->tam));
    (vector->datos)[pos]=dato;
    vector->cantidad++;
    return true;
}

// Devuelve el tama�o del vector
size_t vector_obtener_tamanio(vector_t *vector)
{
    return vector->tam;
}

// Devuelve la cantidad de elementos del vector
size_t vector_obtener_cantidad(vector_t *vector)
{
    return vector->cantidad;
}
