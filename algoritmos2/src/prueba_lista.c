#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Estructura que modela un alumno sólo con notas y padrón. */
typedef struct alumno {
	int* notas;
	int padron;
}alumno_t ;


/* Crea un alumno con el padron elegido y le asigna 10 notas random. */
alumno_t* alumno_crear(int pad) {
	alumno_t* alumno = malloc(sizeof(alumno_t));
	if (alumno==NULL)
			return NULL;
	alumno->notas=malloc(10*sizeof(int));
	if (alumno->notas==NULL)
			return NULL;
	alumno->padron=pad;
	srand(time(NULL));
	for (int i=0; i<10; i++)
		alumno->notas[i]=( 1+ (int) (10.0 * rand() / (RAND_MAX + 1.0)) );
	return alumno;
}

void destruir_dato(alumno_t* alumno){
	free(alumno->notas);
	free(alumno);
}


/* Pruebas */
void prueba_tipos() {

	// Declaro de variables
	lista_iter_t *iter;
	lista_t* lista;
	alumno_t* alumno1;
	alumno_t* alumno2;
	alumno_t* alumno3;
	int padron1=94111;
	int padron2=77777;
	int padron3=10104;

	// las inicializo
	lista = lista_crear();
	alumno1=alumno_crear(padron1);
	alumno2=alumno_crear(padron2);
	alumno3=alumno_crear(padron3);

	printf("---------------------------PRUEBAS---------------------------\n");

	//pruebo que este vacia
	print_test("Pruebo que la lista se crea vacía", lista_esta_vacia(lista) );

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

}
int main(){
	prueba_tipos();
	return 0;
}



