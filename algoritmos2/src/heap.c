#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM 50

struct heap_t{
	void** datos;
	cmp_func_t cmp;
	size_t cantidad;
	size_t tamanio;
	};

void swap(void** a, void** b){
	void* aux;
	aux=*a;
	*a=*b;
	*b=aux;
}

heap_t *heap_crear(cmp_func_t cmp){
	int i;
	heap_t* heap=malloc(sizeof(heap_t));
		if (!heap) return NULL;
		
	heap->datos=malloc(sizeof(void*)*TAM);
		if (!heap->datos) return NULL;
	
	heap->tamanio=TAM;
	heap->cantidad=0;
	heap->cmp=cmp;
	for (i=0;i>heap->tamanio;i++) {
				heap->datos[i]=NULL;
			}
	return heap;
	}

bool heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (heap==NULL) return false;
	int i;
	if (destruir_elemento){
		for(i=0;i<heap->cantidad;i++){
			destruir_elemento(heap->datos[i]);
			}
		}
	free(heap->datos);
	free(heap);
	return true;
	}
	
size_t heap_cantidad(const heap_t *heap){
	if (heap==NULL) return 0;
	return (heap->cantidad);
	}
	
bool heap_esta_vacio(const heap_t *heap){
	if (heap==NULL) return true;
	if (heap->cantidad==0) return true;
	
	return false;
	}
	
void *heap_ver_max(const heap_t *heap){
	if (heap==NULL) return NULL;
	if(heap_esta_vacio(heap)) return NULL;
	
	return (heap->datos[0]);
	}


void upheap(heap_t* heap){

	int i=heap->cantidad-1;
	int padre;

	if (i%2==0) padre=(i-2)/2;
	else padre=(i-1)/2;

	while ( (i>=0 && padre>=0) && (heap->cmp(heap->datos[padre], heap->datos [i])<0) ) {
		swap(&heap->datos[padre],&heap->datos[i]);
		i=padre;
		if (i%2==0) padre=(i-2)/2;
		else padre=(i-1)/2;
	}
}

	
bool heap_encolar(heap_t *heap, void *elem){
	if (heap==NULL) return false;
	//Si no hay tamaño, lo redimensiono.
	if(heap->tamanio < heap->cantidad+2){
		void** nuevos_datos=realloc( (heap->datos) , (heap->tamanio)*2 *sizeof(void*));
			if(!nuevos_datos) return false;
		heap->tamanio=(heap->tamanio)*2;
		heap->datos=nuevos_datos;
		int i;
		for (i=heap->cantidad;i< heap->tamanio;i++) {
			heap->datos[i]=NULL;
		}
	}
	heap->datos[heap->cantidad]=elem;
	heap->cantidad++;
	upheap(heap);
	return true;
	}

void mostrar(heap_t* heap) { //usada para probar
	int i;
	int* dato;
	printf("DATOS: ");
	for (i=0;i<heap->cantidad;i++){
		dato=(heap->datos[i]);
		printf(" %d ",*dato);
	}
	printf("\n");
}


void downheap(heap_t* heap, int i, int fin) {
	if (heap==NULL) return;
	if (heap_esta_vacio(heap)) return;
	int izq=2*i+1;
	int der=2*i+2;
	int maslargo=i;
	if (fin >= izq+1){ //verifica que tiene hijos

		if (fin == izq+1) //caso en el que tiene solo hijo izq
		{
		if (heap->cmp(heap->datos[i],heap->datos[izq])<0)
			swap(&heap->datos[i],&heap->datos[izq]);
		}
		else{ //tiene los 2 hijos
			if (heap->cmp(heap->datos[i],heap->datos[izq])<0)
				maslargo=izq;
			if (heap->cmp(heap->datos[maslargo],heap->datos[der])<0)
				maslargo=der;
			if (maslargo != i){
				swap(&heap->datos[i],&heap->datos[maslargo]);
				downheap(heap,maslargo,fin);
				}
			}
	}
}

void *heap_desencolar(heap_t *heap){
	if (heap==NULL) return NULL;
	if (heap_esta_vacio(heap)) return NULL;
	void* aux=heap->datos[0];

	//cambio la raiz por la ultima hoja,la borro, y hago downheap con la nueva raiz.
	heap->datos[0]=heap->datos[heap->cantidad-1];
	heap->datos[heap->cantidad-1]=NULL;

	heap->cantidad--;
	downheap(heap,0,heap->cantidad);
	return aux;
	}

heap_t *heapify(void *elementos[], size_t cant,  cmp_func_t cmp) {

	heap_t* heap_aux=heap_crear(cmp);
	int i;
	for (i=0; i<cant;i++){
			heap_encolar(heap_aux, elementos[i]);
	}
	return heap_aux;
}

void heapsort(void *elementos[], size_t cant, cmp_func_t cmp){

	heap_t* heap_aux= (heap_t *) heapify( elementos, cant, cmp);

	int fin=heap_aux->cantidad;
	while (fin>0) {
		elementos[fin-1]=heap_desencolar(heap_aux);

		downheap(heap_aux,0,fin-1);
		fin--;
	}

	heap_destruir(heap_aux, NULL);
}

