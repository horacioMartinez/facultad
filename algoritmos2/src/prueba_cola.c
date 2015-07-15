#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cola.h"

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

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Pruebas que muestra como se pueden usar distintos tipos de datos */
void prueba_tipos() {

	// Declaro de variables
	cola_t* cola;
	alumno_t* alumno1;
	alumno_t* alumno2;
	alumno_t* alumno3;
	alumno_t* alumnoaux;
	int padron1=94111;
	int padron2=77777;
	int padron3=10104;

	// las inicializo
	cola = cola_crear();
	alumno1=alumno_crear(padron1);
	alumno2=alumno_crear(padron2);
	alumno3=alumno_crear(padron3);


	printf("---------------------------PRUEBAS---------------------------\n");

	// Pruebo que se inicialice vacía
	print_test("Pruebo que la cola se crea vacía", cola_esta_vacia(cola) );

	// Pruebo que desencolar y ver primero devuelven NULL, debido a que esta vacia
	print_test("Pruebo desencolar la cola devuelve NULL", NULL==cola_desencolar(cola) );
	print_test("Pruebo que ver primero devuelve NULL", NULL==cola_ver_primero(cola) );

	// Comienzo a encolar los alumnos
	print_test("Pruebo agregar alumno1", cola_encolar(cola,alumno1) );
	print_test("Pruebo agregar alumno2", cola_encolar(cola,alumno2) );
	print_test("Pruebo agregar alumno3", cola_encolar(cola,alumno3) );

	// veo primer elemento de la cola
	print_test("Veo que el primer elemento sea alumno1", alumno1==cola_ver_primero(cola));

	//saco a ese elemento y veo devuelta el primero
	print_test("Saco el primer elemento (alumno1)", alumno1==cola_desencolar(cola));
	destruir_dato(alumno1);
	print_test("Veo que el primer elemento ahora sea alumno2", alumno2==cola_ver_primero(cola));
	alumnoaux=cola_ver_primero(cola);
	print_test("Pruebo que el padron del primero sea el de alumno2", padron2==alumnoaux->padron);
	print_test("Pruebo que la tercer nota del primero sea la de alumno2", alumno2->notas[2]==alumnoaux->notas[2]);

	//saco a ese elemento y veo devuelta el primero
	print_test("Saco el primer elemento (alumno2)", alumno2==cola_desencolar(cola));
	destruir_dato(alumno2);
	print_test("Veo que el primer elemento ahora sea alumno3", alumno3==cola_ver_primero(cola));
	alumnoaux=cola_ver_primero(cola);
	print_test("Pruebo que el padron del primero sea el de alumno3", padron3==alumnoaux->padron);
	print_test("Pruebo que la cuarta nota del primero sea la de alumno3", alumno3->notas[3]==alumnoaux->notas[3]);


 	// Pruebo si esta vacia
	print_test("Pruebo que la cola no este vacía", !(cola_esta_vacia(cola)) );
	//Destruyo la cola
	cola_destruir(cola,destruir_dato);

}
int main(){
	prueba_tipos();
	return 0;
}

