#include <stdio.h>
#include <stdbool.h>
#include "pila.h"
#include "abb.h"
#include <string.h>

typedef struct prueba {
	char* clave;
	int* dato;
}prueba_t ;
	
/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

int cmp (const char* a, const char* b){
	if (strlen(a)>strlen(b)) return 1;
	if (strlen(a)<strlen(b)) return -1;
	return 0;
	}
	
bool funcion_extra(const char* clave, int* valor, int* extra){
	*valor+=*extra;
	return true;
	
	}

char *copiarcadena (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

	
int main(){
	
	prueba_t* f=malloc(sizeof(prueba_t));
	f->clave=(char*)copiarcadena("nicolasabcd");
	int* ff=malloc(sizeof(int));
	*ff=11;
	(f->dato)=ff;

	prueba_t* e=malloc(sizeof(prueba_t));
	e->clave=(char*)copiarcadena("nicolasabc");
	int* ee=malloc(sizeof(int));
	*ee=10;
	(e->dato)=ee;

	prueba_t* d=malloc(sizeof(prueba_t));
	d->clave=(char*)copiarcadena("alejandro");
	int* dd=malloc(sizeof(int));
	*dd=9;
	(d->dato)=dd;
	
	prueba_t* a=malloc(sizeof(prueba_t));
	a->clave=(char*)copiarcadena("agustin");
	int* aa=malloc(sizeof(int));
	*aa=7;
	(a->dato)=aa;
	
	prueba_t* g=malloc(sizeof(prueba_t));
	g->clave=(char*)copiarcadena("aaaa");
	int* gg=malloc(sizeof(int));
	*gg=4;
	(g->dato)=gg;

	prueba_t* b=malloc(sizeof(prueba_t));
	b->clave=(char*)copiarcadena("aa");
	int* bb=malloc(sizeof(int));
	*bb=2;
	(b->dato)=bb;
	
	prueba_t* c=malloc(sizeof(prueba_t));
	c->clave=(char*)copiarcadena("a");
	int* cc=malloc(sizeof(int));
	*cc=1;
	(c->dato)=cc;
	
	prueba_t* cinco=malloc(sizeof(prueba_t));
	cinco->clave=(char*)copiarcadena("aaaaa");
	int* datocinco=malloc(sizeof(int));
	*datocinco=5;
	(cinco->dato)=datocinco;

	prueba_t* seis=malloc(sizeof(prueba_t));
	seis->clave=(char*)copiarcadena("aaaaaa");
	int* datoseis=malloc(sizeof(int));
	*datoseis=6;
	(seis->dato)=datoseis;

	prueba_t* tres=malloc(sizeof(prueba_t));
	tres->clave=(char*)copiarcadena("aaa");
	int* datotres=malloc(sizeof(int));
	*datotres=3;
	(tres->dato)=datotres;

	
	
	abb_t* arbol=abb_crear(cmp, free);
/*
	print_test("La cantidad es cero, no hay datos", abb_cantidad(arbol)==0);
	print_test("Trato de obtener un dato en el arbol vacio", abb_obtener(arbol, a->clave)==NULL);
	print_test("Intento borrar un dato en el arbol vacio", abb_borrar(arbol, "clave")==NULL);
	print_test("Pertenece en un arbol vacio?", abb_pertenece(arbol, a->clave)==false);
	*/
	print_test("Guardo el primer valor", abb_guardar(arbol,a->clave, a->dato));
	//print_test("La cantidad de datos es correcta", abb_cantidad(arbol)==1);
	//print_test("Obtener el dato guardado", abb_obtener(arbol, a->clave)==a->dato);
	//print_test("Pertenece el que guarde?", abb_pertenece(arbol, a->clave));
	print_test("Guardo un valor mas", abb_guardar(arbol, b->clave, b->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, c->clave, c->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, e->clave, e->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, d->clave, d->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, g->clave, g->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, f->clave, f->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, tres->clave, tres->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, seis->clave, seis->dato));
	print_test("Guardo uno mas", abb_guardar(arbol, cinco->clave, cinco->dato));

	//mostrar_arbol(arbol);

	print_test("Borro un dato insertado", abb_borrar(arbol, d->clave)==d->dato);

	//Pruebo el iterador
	print_test("La cantidad es correcta?", abb_cantidad(arbol)==8);
	//mostrar_arbol(arbol);
	int* extra=malloc(sizeof(int));
	*extra=2;
	printf("Sumo 2 a todos los nodos con inorder \n");
	(abb_in_order(arbol, funcion_extra ,extra ));
//	mostrar_arbol(arbol);
	print_test("Se cambio el valor del primer dato?", abb_obtener(arbol, a->clave)==a->dato);
	print_test("se cambio el valor del otro dato?", abb_obtener(arbol, b->clave)==b->dato);
	print_test("se cambio el valor del otro dato?", abb_obtener(arbol, c->clave)==c->dato);
	print_test("se cambio el valor del ultimo dato?", abb_obtener(arbol, d->clave)==d->dato);

	abb_iter_t* iter=abb_iter_in_crear(arbol);
	print_test("Verifico si el iterador esta al final", !abb_iter_in_al_final(iter));

	print_test("Veo el dato actual C", strcmp(abb_iter_in_ver_actual(iter),c->clave)==0);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Veo el dato actual D",  strcmp(abb_iter_in_ver_actual(iter),b->clave)==0);
	print_test("Verifico si esta al final", !abb_iter_in_al_final(iter));
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	printf ( "         %s         ", abb_iter_in_ver_actual(iter) );
	print_test("Veo el nuevo dato actual G",  strcmp(abb_iter_in_ver_actual(iter),g->clave)==0);
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	printf ( "         %s         ", abb_iter_in_ver_actual(iter) );
	print_test("Veo el nuevo dato actual A",  strcmp(abb_iter_in_ver_actual(iter),a->clave)==0);
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	print_test("Veo el nuevo dato actual D",  strcmp(abb_iter_in_ver_actual(iter),d->clave)==0);
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	print_test("Veo el nuevo dato actual E",  strcmp(abb_iter_in_ver_actual(iter),e->clave)==0);
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	print_test("Veo el nuevo dato actual F",  strcmp(abb_iter_in_ver_actual(iter),f->clave)==0);
	print_test("Avanzo de vuelta", abb_iter_in_avanzar(iter));
	print_test("el iterador esta al final", abb_iter_in_al_final(iter));
	print_test("No hay dato actual", abb_iter_in_ver_actual(iter)==NULL);
	print_test("La cantidad es correcta", abb_cantidad(arbol)==7);
	

	abb_iter_in_destruir(iter);
	abb_destruir(arbol);

	//Libero la memoria reservada por las pruebas
	//free(extra);
	free(a->clave);
	free(a);
	free(aa);
	free(d->clave);
	free(d);
	free(dd);
	free(c->clave);
	free(c);
	free(cc);
	free(b->clave);
	free(b);
	free(bb);
	return 0;
}
