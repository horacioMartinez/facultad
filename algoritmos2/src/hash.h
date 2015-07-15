#include <stdlib.h>
#include <stdbool.h>

typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;
typedef void (*hash_destruir_dato_t)(void *);
typedef struct hash_dato hash_dato_t;

//Primitivas del hash abierto
/*Crea una nueva tabla de hash
 * PRE: se crea la funcion destruir_dato.
 * POST: se creo una tabla de hash, con listas asignadas a cada
 * casillero*/
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

/*Se guarda el dato en la posicion correspondiente a la clave.
 * PRE: se crea un hash, y se cuenta con una funcion de hash.
 * POST: se puso el dato en la posicion y en la lista correspondiente.
 * Devuelve true si se guardo, false si hubo un error.*/
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

/*Borra la clave que se pasa por parametro y su correspondiente dato de la tabla.
 * PRE: se crea un hash, y se cuenta con la funcion de hash y la clave a borrar.
 * POST: se borro la clave (si es que existe) con su correspondiente dato 
 * de la tabla. Devuelve el dato borrado o NULL si no existia la clave.*/
void *hash_borrar(hash_t *hash, const char *clave);

/*Devuelve el dato que le corresponde a la clave que se pasa por parametro.
 * PRE :se creo un hash, y se cuenta con la funcion de hash y la clave.
 * POST: devuelve el dato correspondiente a la clave, si es que existe.
 * Si no existe la clave en el hash, devuelve NULL.*/
void *hash_obtener(const hash_t *hash, const char *clave);

/*Evalua si existe o no la clave en la tabla.
 * PRE: se creo un hash y se le pasa una clave a evaluar.
 * POST: devuelve verdadero en caso en que exista la clave en la tabla
 * o falso en caso contrario.*/
bool hash_pertenece(const hash_t *hash, const char *clave);

/*Devuelve la cantidad de claves-datos guardados en la tabla.
 * PRE:se creo un hash.
 * POST: devuelve un entero que corresponde a la cantidad de claves-datos
 * que se guardaron en la tabla.*/
size_t hash_cantidad(const hash_t *hash);

/*Destruye completamente la tabla.
 * PRE: Se creo un hash.
 * POST: se elimino el hash con sus listas correspondientes.*/
void hash_destruir(hash_t *hash);

/*Devuelve un entero que le corresponde a la clave pasada en la tabla.
 * PRE: se le pasa la clave, y el tamanio de la tabla.
 * POST: devuelve un entero que data de la posicion que ocupara la clave-dato
 * en la tabla.*/
size_t fhash(const char* clave, size_t tam);

//Primitivas del iterador


/*Crea un iterador en la primer posicion no vacia del hash
 * PRE: Se creo un hash.
 * POST: Se creo un iterador.*/
hash_iter_t *hash_iter_crear(const hash_t *hash);

/*Avanza el iterador una posicion, si esta al final devuelve NULL
 * PRE: Se creo un hash y un iterador
 * POST: Se avanzo el iterador una posicion.*/
bool hash_iter_avanzar(hash_iter_t *iter);

/*Devuelve el elemento al que se encuentran apuntando el iterador
 * PRE: Se creo un hash y un iterador
 * POST: Se devolvio el elemento al cual apunta el iterador*/
const char *hash_iter_ver_actual(const hash_iter_t *iter);

/*Devuelve true si el iterador esta al final, sino false
 * PRE: Se creo un hash y un iterador
 * POST: Devuelve true si el iterador esta al final*/
bool hash_iter_al_final(const hash_iter_t *iter);

/*Destruye el iterador del hash
 * PRE: Se creo un hash y un iterador
 * POST: Se destruyo el iterador.*/
void hash_iter_destruir(hash_iter_t* iter);
