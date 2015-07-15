#include <stdio.h>
#include <stdlib.h>
#include <string.h>	 // Para copiar cadenas con strcpy

#include "pila.h"

/* Estructura que modela un alumno sólo con nombre y padrón. */
struct alumno {
	char nombre[50];
	int padron;
};


/* Devuelve un puntero a un alumno con los datos pasados por parámetro. */
struct alumno* alumno_crear(const char* nom, int pad) {
	struct alumno* al = malloc(sizeof(struct alumno));
	if ( ! al) return NULL;
	strcpy(al->nombre, nom);
	al->padron = pad;
	return al;
}


/* Devuelve un puntero el valor pasado por parametro almacenado. */
int* val(int n) {
	int* aux = malloc(sizeof(int));
	if (! aux) return NULL;
	*aux = n;
	return aux;
}


/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}


/* Prueba que muestra como se pueden usar distintos tipos de datos
 * con la misma pila, gracias a su implementación con void*.   */
void prueba_tipos() {
	
	// Inicializacion de variables
	int *uno = val(1);
	float e = 2.718281;
	double pi = 3.1415926535;
	char* cad = "AlgoII";
	
	// 'alumno' en memoria estática
	struct alumno fran;
	strcpy(fran.nombre, "Francisco");
	fran.padron = 74288;
	
	// 'alumno' en memoria dinámica
	struct alumno* cami = alumno_crear("Camila", 82492);	

	// Creo la pila
	pila_t* pila = pila_crear();
	
	printf("PRUEBA DE TIPOS\n");

	// Pruebo que se inicialice vacía
	print_test("Pruebo que la pila se crea vacía", pila_esta_vacia(pila) );
	
	// Pruebo que no pueda desapilar ni ver el tope, debido a que esta vacia
	print_test("Pruebo NO poder ver el tope de la pila vacía", ! pila_ver_tope(pila) );
	print_test("Pruebo NO poder desapilar la pila vacía", ! pila_desapilar(pila) );

	// Comienzo a apilar las variables de distinto tipo
	print_test("Pruebo apilar 'uno'", pila_apilar(pila, uno) );
	print_test("Pruebo apilar 'e'", pila_apilar(pila, &e) );
	print_test("Pruebo apilar 'pi'", pila_apilar(pila, &pi) );
	print_test("Pruebo apilar 'cad'", pila_apilar(pila, cad) );
	print_test("Pruebo apilar 'fran'", pila_apilar(pila, &fran) );
	print_test("Pruebo apilar 'cami'", pila_apilar(pila, cami) );
   	
	// Pruebas de desapilado en sentido inverso al que fueron apilados
	print_test("Pruebo ver el tope y que sea 'cami'", cami == pila_ver_tope(pila));
	print_test("Pruebo desapilar y que sea 'cami'", cami == pila_desapilar(pila));
	print_test("Pruebo ver tope y que sea 'fran'", &fran == pila_ver_tope(pila));
	
	struct alumno *aux = pila_desapilar(pila);
	print_test("Pruebo que el alumno desapilado sea 'fran' comparando los padrones", aux->padron == fran.padron);
	print_test("Pruebo desapilar y que sea la dirección de 'cad'", cad == pila_desapilar(pila));
	print_test("Pruebo ver tope y que sea la dirección del número pi", &pi == pila_ver_tope(pila) );
	
	double* aux_pi = pila_desapilar(pila);
	print_test("Pruebo que el número desapilado sea 'pi'", *aux_pi == pi);
	print_test("Pruebo ver tope y que sea la dirección del número pi", &e == pila_ver_tope(pila) );
	
	float* aux_e = pila_desapilar(pila);
	print_test("Pruebo que el número desapilado sea e", *aux_e == e );
	print_test("Pruebo desapilar y que sea el número uno", uno == pila_desapilar(pila) );
	print_test("Verifico que la pila quedó vacía", pila_esta_vacia(pila) );
	
	free(uno);
	free(cami);
	pila_destruir(pila);
}

// Prueba de redimensionamiento de la pila al sobrepasar la cantidad de
// elementos basica (no sabemos cuanto es), la hacemos crecer hasta 1000.    
void prueba_volumen() {
	
	// Nuevamente usamos dos tipos de datos distintos
	char* valor1 = "A";
	int num = 28;
	int *valor2 = &num;
	
	printf("\nPRUEBA DE VOLUMEN\n");
	
	pila_t* p = pila_crear();
    print_test("Prueba pila crear", p != NULL);
    
    for(int i = 0; i < 1000; i++)
    {
		pila_apilar(p, valor1);
	}
    print_test("Prueba pila devolver tope de pila", pila_ver_tope(p) == valor1);
    print_test("Prueba pila apilar valor2", pila_apilar(p, valor2));
    print_test("Prueba pila devolver tope de pila", pila_ver_tope(p) == valor2);
    print_test("Prueba pila desapilar valor2", pila_desapilar(p) == valor2);
    print_test("Prueba pila devolver tope de pila", pila_ver_tope(p) == valor1);

	for(int i = 0; i < 999; i++)
	{
		pila_desapilar(p);
	}
	
    print_test("Prueba pila devolver tope de pila", pila_ver_tope(p) == valor1);
    print_test("Prueba pila desapilar valor1", pila_desapilar(p) == valor1);
    print_test("Prueba pila comprobar que esta vacía despues de desapilar", pila_esta_vacia(p));
    print_test("Prueba pila ver tope final, es false", !pila_ver_tope(p));
	pila_destruir(p);    
	
}

int main() {
	prueba_tipos();
	prueba_volumen();
	return 0;
}

