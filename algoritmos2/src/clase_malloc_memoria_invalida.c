#include <stdio.h>
#include <stdlib.h>

#define VECTOR 5
#define INVALIDO 50

void prueba(int prueba, int n, int carga, int lectura){
    int i;
    
	// Pide memoria para "arreglo"
	// malloc recibe un unico parametro la cantidad de bytes a pedir
	// devuelve un puntero del tipo (void *) al que explicitamente 'casteo'
	int *arreglo = (int *) malloc(n * sizeof(int));
	
	
    // Imprime info de la prueba
    printf("\n\nPrueba %d= ", prueba);
    printf(" Long: %d; Carga: %d; Lectura: %d;\n", n, carga, lectura);
    
    // Control para correr o ignorar prueba
    printf("Presione enter para comenzar, otro caracter para ignorar\n");
    if (getc(stdin) != '\n'){
        getc(stdin);
        return;
    }
    
	// Verificacion de que haya memoria
	if (arreglo == 0) {// es lo mismo que (arreglo == NULL)
		printf("\nNo anduvo\n");
		return; // Salgo de aca.
	}

    // Cargo el Arreglo desde arreglo[0] hasta arreglo[carga - 1]
    for(i = 0; i < carga; i++){
        arreglo[i] = i; // Valor "i" en el indice "i"
    }

    // Imprimo el Arreglo desde arreglo[0] hasta arreglo[lectura - 1]
    for(i = 0; i < lectura; i++){
        printf(" %d -", arreglo[i]);
        if( ((i % VECTOR) == 0) && (i != 0)) {
            printf("\n");
        }
    }

	// Libera "arreglo"
	free(arreglo);
	printf("\nOK\n");
}

int main(void) {
    // Nro de prueba, Longitud del vector, Cant. Carga, Cant Lectura
    prueba(1, 0, 0, 0);
    prueba(2, VECTOR, VECTOR,   VECTOR);
    
    // De aca en adelante deberian fallar
    prueba(3, VECTOR, VECTOR,   INVALIDO);
    prueba(4, VECTOR, INVALIDO, VECTOR);
    prueba(5, VECTOR, INVALIDO, INVALIDO);

	return 0;
}
