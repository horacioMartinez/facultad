#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct alumno {
	int padron;
	char nombre[64];
} alumno;

alumno *alumno_crear(int padron, const char *nombre)
{
	alumno *ret = (alumno *)malloc(sizeof(alumno));
	if (ret == NULL)
		return NULL;
	ret->padron = padron;
	strcpy(ret->nombre, nombre);
	return ret;
}

void alumno_imprimir(const alumno *alumno)
{
	printf("Nombre: %s\nPadron: %d\n", alumno->nombre, alumno->padron);
}

void alumno_destruir(alumno *alumno)
{
	free(alumno);
}

int main(void)
{
	alumno *willy = alumno_crear(78950, "Willy");
	if (willy == NULL)
	{
		puts("No se pudo reservar memoria.");
		return 1;
	}
	alumno_imprimir(willy);
	alumno_destruir(willy);
	return 0;
}

