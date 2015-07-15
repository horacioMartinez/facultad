#include <stdio.h>
#include <stdlib.h>

#define TAM 15

int main(void) {
    int *vector = (int *) malloc(sizeof(int));
    int *nuevo;
    
    printf("Vector: %p\n", (void*)vector);
    
    // Pido la nueva memoria (en este caso el doble)
    nuevo = (int *) realloc(vector, TAM * 2 * sizeof(int));
    // realloc recibe 2 parametros un puntero existente, y un nuevo tamaño
    // realloc devuelve lo mismo que malloc
    // free(ptr) == realloc(ptr, 0)
    // el contenido del puntero viejo se conserva en el nuevo
    
    
    if (nuevo){ // chequeo que la memoria sea valida
        vector = nuevo; 
    }else{
        return 1;
    }
    
    printf("Despues del realloc\n");
    printf(" Nuevo: %p\n", (void*)nuevo);
    printf(" Vector: %p\n", (void*)vector);

    // Libero la memoria
    free(vector); 
    
	return 0;
}
