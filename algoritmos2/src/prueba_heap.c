#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <string.h>
#include <time.h>

typedef struct nodo_t{
	int prioridad;
	
	}nodo_t;

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

int cmp (const int* a,const int* b){
	
	if (*a>*b) return 1;
	if (*a==*b) return 0;
	else return -1;
	}

bool prueba_heapsort(){
	int **vector,a,b,c,d,e;
	int i;

	vector=malloc(5*sizeof(int*));
	a=4;b=1;c=9;d=3;e=2;
	vector[0]=&a;vector[1]=&b;vector[2]=&c;vector[3]=&d;vector[4]=&e;

	heapsort((void**) vector,5, (cmp_func_t) cmp);
	bool res=true;
	for (i=0;i<4;i++) {
		if (*(vector[i]) > *(vector[i+1]) ) res=false;
	}
	free(vector);
	return res;
}

void prueba_tipos(){
	
	heap_t *heap=heap_crear( (cmp_func_t) cmp);
	void *nulo=NULL;
	int*a=malloc(sizeof(int));
	*a=10;
	int*b=malloc(sizeof(int));
	*b=1;
	int*c=malloc(sizeof(int));
	*c=5;
	int*d=malloc(sizeof(int));
	*d=11;
	int*e=malloc(sizeof(int));
	*e=0;
	printf("-------------------------PRUEBAS------------------------\n\n");
	
	print_test("Pruebo si esta vacio con un puntero a null", heap_esta_vacio(nulo));

	print_test("Pruebo destruir con un puntero a null", !heap_destruir(nulo,NULL));

	print_test("Pruebo encolar con un puntero null", !heap_encolar(nulo,NULL));

	print_test("Pruebo ver maximo con un puntero null", heap_ver_max(nulo)==NULL);

	print_test("Pruebo desencolar con un puntero null", heap_desencolar(nulo)==NULL);

	print_test("Pruebo que el heap esta vacio", heap_esta_vacio(heap));
	
	print_test("Puebo desencolar algo en el heap vacio", heap_desencolar(heap)==NULL);
	
	print_test("Pruebo ver el maximo en el heap vacio", heap_ver_max(heap)==NULL);
	
	print_test("Encolo un nodo", heap_encolar(heap,a)==true);
	
	print_test("Verifico cual es el maximo ahora", heap_ver_max(heap)==a);
	
	print_test("La cantidad de datos en el heap es 1", heap_cantidad(heap)==1);
	
	print_test("Encolo un nodo de menor prioridad", heap_encolar(heap, b)==true);
	
	print_test("Verifico que el primer dato es el de mas prioridad", heap_ver_max(heap)==a);
	
	print_test("La cantidad de datos del heap ahora es 2", heap_cantidad(heap)==2);
	
	print_test("Encolo un dato de mayor prioridad", heap_encolar(heap, d)==true);

	print_test("El nuevo dato es el maximo", heap_ver_max(heap)==d);
	
	print_test("Encolo dato de menor prioridad", heap_encolar(heap, c));
	
	print_test("Encolo otro de menor prioridad", heap_encolar(heap, e));
	
	print_test("Verifico que el maximo sigue siendo el mismo", heap_ver_max(heap)==d);
	
	print_test("Desencolo el de mayor prioridad", heap_desencolar(heap)==d);
	
	print_test("La cantidad de datos es 4", heap_cantidad(heap)==4);
	
	print_test("El de mayor prioridad es el primer dato encolado", heap_ver_max(heap)==a);

	print_test("Vuelvo a desencolar", heap_desencolar(heap)==a);
	free(a);
	print_test("Encolo un dato con mayor prioridad", heap_encolar(heap, d)==true);

	print_test("Verifico ahora el maximo", heap_ver_max(heap)==d);
	print_test("Desencolo un dato", heap_desencolar(heap)==d);
	free(d);
	print_test("Desencolo otro", heap_desencolar(heap)==c);
	free(c);
	print_test("Vuelvo a desencolar", heap_desencolar(heap)==b);
	free(b);
	print_test("La cantidad de datos ahora es 1", heap_cantidad(heap)==1);

	print_test("El maximo es el unico dato que queda", heap_ver_max(heap)==e);

	print_test("Pruebo ordenar arreglo de enteros por heapsort", prueba_heapsort()==true);

	heap_destruir(heap, free);
	}
	
int main(){
	
	prueba_tipos();
	
	return 0;
	}
