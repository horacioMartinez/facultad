#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "lista.h"
#include "vector_dinamico.h"
typedef struct pedido pedido_t;
#define TAM 5

/*Crea un vector de tamaño TAM (5) y lo llena con listas
 * PRE: -
 * POST: Se creo un vector dinamico de TAM(5) posiciones y se les agrego una lista  a cada una.
 */
vector_t* crear_zonas(int tam);

/*Crea un vector de tamaño TAM (5) y lo llena con punteros a enteros
 * PRE: -
 * POST: Se creo un vector dinamico de TAM(5) posiciones y se les agrego un puntero a int a cada una.
 */
vector_t* crear_precios(int tam);

/*Crea un pedido
 * PRE: -
 * POST: Se creo un pedido
 */
pedido_t* pedido_crear(char n[],int cantidad,int zona);

/*Agrega un pedido al vector
 * PRE: El vector fre creado
 * POST: El pedido ingresado fue agregado a la lista correspondiente a su zona
 */
bool agregar_pedido(vector_t *vectorzonas, pedido_t* pedido);


/*Destruye el vector.
 * PRE: se creo el vector.
 * POST: se destruyo el vector.*/
void destruir(vector_t* vectorzonas, vector_t* vectorprecios, pila_t* pila);

//Muestra las opciones que tiene el menu principal
void mostrar_menu();

/*Prepara los pedidos registrados.
 * PRE: Se creo un vector y cada vector tiene una lista.
 * POST: Se cambio el valor de preparado a true para todos los pedidos registrados.
 * Devuelve FALSO en caso de que no haya ningun pedido en ninguna zona.*/
bool preparar_pedidos(vector_t * vectorzonas, vector_t * vectorprecios);

/*Toma los datos del pedido y lo registra en la zona correspondiente.
 * PRE: El vector zonas fue creado con sus respectivas listas.
 * POST: Se enlisto el pedido en la zona correspondiente*/
void registrar_pedido(vector_t* vectorzonas);

/*Agrega una zona mas a la lista de zonas en la que se pueden hacer pedidos.
 * PRE: Se creo el vector zonas con sus respectivas listas.
 * POST:Se agrego una zona mas, y se le asigno una lista. Devuelve falso en caso de error.*/
bool agregar_zona(vector_t *vectorzonas, vector_t *vectorprecios);

/*Modifica la cantidad de pizzas encargadas de un pedido existente.
 * PRE: SE creo el vector y se tomaron los datos del pedido a modificar.
 * POST: El pedido contiene la nueva cantidad asignada. Devuelve falso 
 * en caso de error o de no encotrarlo.*/
bool modificar_pedido(vector_t * vectorzonas, char n[], int cantidad);

/*Elimina el pedido que se especifica de la lista de registrados.
 * PRE: Se creo el vector y se tomaron los datos del pedido a borrar.
 * POST: Se borro el pedido de la lista de registrados. Devuelve falso en caso de
 * no encontrarlo*/
bool cancelar_pedido(vector_t * vectorzonas, char n[], int cantidad, int zona);

/*Procede a enviar todos los pedidos registrados, haciendo un viaje por zona, y apila
 * los enviados.
 * PRE: el vector fue creado junto con una pila.
 * POST: se envian los pedidos que esten preparados, haciendo la menor cantidad posible de viajes por zona
 * de no mas de 5 pizzas.*/
void enviar(vector_t * vectorzonas, pila_t* pila);

/*Muestra los pedidos enviados hasta el momento desde el mas nuevo al mas viejo.
 * PRE: Se creo el vector y apilaron los pedidos ya enviados.
 * POST: Se muestra por consola todos los pedidos que se enviaron y la 
 * recaudacion total.*/
pila_t* mostrar_enviados(pila_t* pila, vector_t *vectorzonas, vector_t* vectorprecios);

/*Define los precios unitarios (en pesos) de cada pizza dependiendo de la zona.
 * PRE: Se creo el vector.
 * POST: Se le asigno a cada zona un precio por pizza en pesos.*/
void definir_precios(vector_t *vectorprecios);

/*Muestra todos los pedidos registrados hasta el momento.
 * PRE: Se creo el vector.
 * POST: Se mostro por consola todos los pedidos registrados
 * hasta el momento, ordenados por zonas de manera ascendente.*/
void mostrar_registrados (vector_t *vectorzonas);
