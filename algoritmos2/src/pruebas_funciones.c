#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"
#include "pila.h"
#include "lista.h"

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}


/* Pruebas */
void prueba_tipos() {

	// Declaro de variables
	vector_t *vector;
	lista_t* lista;
	pedido_t* pedido1;
	pedido_t* pedido2;
	pedido_t* pedido3;
	pedido_t* pedido4;
	pedido_t* pedido5;
	pila_t* pila;

	// las inicializo
	vector = vector_crear();
	pila=pila_crear();

	char a[20]="agustin";
	char b[20]="bernardo";
	char c[20]="carlos";
	char d[20]="damian";
	char e[20]="esteban";


	printf("---------------------------PRUEBAS---------------------------\n");

	//Creo un vector
	vector=vector_crear(vector);
	print_test("Creo un vector", vector!=NULL );

	//Creo 5 pedidos
	pedido1=pedido_crear(a,1,2);
	pedido2=pedido_crear(b,2,3);
	pedido3=pedido_crear(c,3,2);
	pedido4=pedido_crear(d,4,3);
	pedido5=pedido_crear(e,5,2);

	//Agrego los 4 primeros pedidos

	print_test("Agrego pedido 1", vector_agregar_pedido(vector,pedido1) );
	print_test("Agrego pedido 2", vector_agregar_pedido(vector,pedido2) );
	print_test("Agrego pedido 3", vector_agregar_pedido(vector,pedido3) );
	print_test("Agrego pedido 4", vector_agregar_pedido(vector,pedido4) );
	printf("asd");

	mostrar_registrados (vector);
	/*
	//inserto 1er elemento
	print_test("Inserto primer elemento alumno1", lista_insertar_primero(lista,alumno1) );

	//inserto ultimo
	print_test("Inserto ultimo elemento alumno2", lista_insertar_ultimo(lista,alumno2) );

	//inesrto un nuevo ultimo
	print_test("Inserto ultimo elemento alumno3", lista_insertar_ultimo(lista,alumno3) );

	//veo el primero
	print_test("Veo el primer elemento(alumno1)", alumno1==lista_ver_primero(lista));

	//borro el primero y veo devuelta
	print_test("Borro el primero", lista_borrar_primero(lista));
	print_test("Veo el primer elemento(alumno2)", alumno2==lista_ver_primero(lista));

	//veo el largo de la lista
	print_test("Veo el largo de la lista (2)", 2==lista_largo(lista));

	//creo iterador
	iter= lista_iter_crear(lista);

	//pruebas del iterador
	print_test("Hago avanza al iterador", lista_iter_avanzar(iter));
	print_test("Veo elemento actual del iterador (alumno3)", alumno3==lista_iter_ver_actual(iter));
	print_test("Hago avanza al iterador", lista_iter_avanzar(iter));
	print_test("Veo si esta al final", lista_iter_al_final(iter));

	//pruebas de lista junto con iterador
	print_test("Inserto de nuevo alumno1", lista_insertar(lista,iter,alumno1));
	print_test("Lo borro", alumno1==lista_borrar(lista,iter));

	//inserto 1er elemento
	print_test("Inserto primer elemento alumno1", lista_insertar_primero(lista,alumno1) );
	//destruyo el iterador
	lista_iter_destruir(iter);
	//creo iterador
	iter= lista_iter_crear(lista);
	print_test("Destruyo iterador,lo creo devuelta y borro el primer elemento (alumno1)", alumno1==lista_borrar(lista,iter));
	destruir_dato(alumno1);
	//destruyo lista e iterador
	lista_iter_destruir(iter);
	lista_destruir(lista,destruir_dato);
*/
}
int main(){
	prueba_tipos();
	return 0;
}
