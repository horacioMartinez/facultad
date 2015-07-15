#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "vector_dinamico.h"
#include "funciones.h"
#include "lista.h"
#include "pila.h"


int main(){


	pila_t *pila=pila_crear();
	bool resultado;
	int opcion=0,opcion_aux, cantidad, cantidad_nueva, zona;
	char nombre[20];

	vector_t *vectorzonas=crear_zonas(5);
	vector_t *vectorprecios=crear_precios(5);
	definir_precios(vectorprecios);
	mostrar_menu();
			

	while (opcion<7) {
				
	scanf("%d", &opcion);
	//system("clear");//borra la pantalla
	
	//registrar pedidos
	if (opcion==1){
		registrar_pedido(vectorzonas);
				
		}
	
	//modificar o cancelar un pedido
	if (opcion==2){
		printf("Que desea hacer? 1. Modificar pedido, 2.Cancelar pedido\n");
		scanf("%d", &opcion_aux);
		if (opcion_aux<1 || opcion_aux>2){
			printf("INCORRECTO. Elija de vuelta una opcion, numero 1 o 2\n");
			scanf("%d",&opcion_aux);
			}
		if (opcion_aux==1){
			printf("Ingrese el nombre del cliente: \n");
			scanf("%s", nombre);
			printf("Ingrese la nueva cantidad de pizzas: \n");
			scanf("%d",&cantidad_nueva);
			resultado=modificar_pedido(vectorzonas, nombre, cantidad_nueva);
			if (resultado==false) printf("su pedido no existe.\n");
			}
		if (opcion_aux==2){
			printf("Ingrese el nombre del cliente: \n");
			scanf("%s", nombre);
			printf("Ingrese la cantidad de pizzas que habia encargado: \n");
			scanf("%d",&cantidad);
			printf("Ingrese la zona en la cual se iba a entregar: \n");
			scanf("%d", &zona);
			
			resultado=cancelar_pedido(vectorzonas, nombre, cantidad, zona);
			if (resultado==false) printf("Su pedido no existe\n");
			}
		}
	
	//preparar pedidos
	if (opcion==3){
		printf("Se procede a preparar todos los pedidos hasta ahora.\nRecuerde que un pedido no puede ser modificado o cancelado una vez preparado\n");		
		resultado=preparar_pedidos(vectorzonas,vectorprecios);
		
		if (resultado==false){
			printf("Error\n");
			}else {
				printf("Se prepararon los pedidos correctamente.\n");
				}

		};
	//enviar un pedido
	if (opcion==4){
		printf("Se procede a enviar todos los pedidos registrados\n");
		enviar(vectorzonas, pila);
		}

	//agregar una zona
	if (opcion==5){
		printf("Se procede a agregar una zona\n");
		resultado=agregar_zona(vectorzonas,vectorprecios);
		if (resultado==false) printf("Ocurrio un error\n");
			else printf("Se agrego una zona correctamente\n");
	}
		
	//mostrar pedidos registrados, preparados, enviados y la recaudacion total.
	if (opcion==6){
		printf("REGISTRADOS\n");
		mostrar_registrados(vectorzonas);
		
		printf("\n");
		pila=mostrar_enviados(pila, vectorzonas, vectorprecios);
		}
	
	mostrar_menu();
	}
	
	destruir(vectorzonas, vectorprecios, pila);
return 0;
}
