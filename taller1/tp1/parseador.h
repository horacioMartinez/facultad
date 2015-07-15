#ifndef PARSEADOR_H
#define PARSEADOR_H

typedef struct {
	int largo;
	float pCero, pUno, varianza;
} valores_iniciales_t;

// Lee la primer linea del archivo y a partir de ellas completa
// el struct parametros. Si se excuta exitosamente retorna 0, si se
// produce un error retorna -1
int parseador_cargar_valores_iniciales(valores_iniciales_t* valoresIniciales,
		FILE* entrada);

// Lee la proxima señal del archivo entrada y devuelve
// el ultimo caracter de esta
char parseador_parsear_senial(FILE* entrada, int* senial, int n);

// funcion que permite determinar si el archivo termina en el siguiente
// caracter sin necesidad de haberlo leido anteriormente
int parseador_fin_de_archivo(FILE * archivo);
#endif
