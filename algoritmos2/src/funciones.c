#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "vector_dinamico.h"
#include "funciones.h"
#include "lista.h"
#include "pila.h"


 struct pedido {
	char nombre[20];
	int cantidad;
	int zona;
	bool preparado;
};


vector_t* crear_zonas(int tam) {
	int i;
    vector_t* vector=vector_crear(tam);

    for (i=0;i<tam;i++){
    	vector_guardar(vector,-1,lista_crear());
    }
    return vector;
}

vector_t* crear_precios(int tam) {
	int i;
	int *precio;
	vector_t* vector=vector_crear(tam);

	for (i=0;i<tam;i++){
			precio=malloc(sizeof(int*));
	    	vector_guardar(vector,-1,precio );
	    }
    return vector;
}


bool agregar_zona(vector_t *vectorzonas, vector_t *vectorprecios)
{
	int *precio = malloc(sizeof(int*));

	vector_guardar(vectorzonas, -1, lista_crear() );

	printf("Ingrese el precio unitario por pizza para la nueva zona en pesos: \n");
	scanf("%d",precio);
	vector_guardar(vectorprecios, -1, precio);

	return true;
}

void destruir(vector_t* vectorzonas, vector_t* vectorprecios, pila_t* pila){
	int i;
	lista_t * aux;
	int* intaux;
	pedido_t* pedidoaux;
	i=vector_obtener_tamanio(vectorzonas);
	for (i=0; i<vector_obtener_tamanio(vectorzonas);i++){
		aux= vector_obtener(vectorzonas, i);
		if (aux != NULL)
			lista_destruir(aux,free);
	}
	for (i=0; i<vector_obtener_tamanio(vectorprecios);i++){
		intaux= vector_obtener(vectorprecios, i);
		if (intaux != NULL)
			free(intaux);
	}
	vector_destruir(vectorzonas);
	vector_destruir(vectorprecios);
	if (pila) {
		while (!pila_esta_vacia(pila)) {
			pedidoaux=pila_desapilar(pila);
			free(pedidoaux);
		}
		pila_destruir(pila);
	}

}

bool agregar_pedido(vector_t *vectorzonas, pedido_t* pedido)
{
	if (pedido==NULL)
		return false;
	int i;
	i=pedido->zona;
	lista_t* listaaux=vector_obtener(vectorzonas, i-1);
	lista_insertar_ultimo(listaaux,pedido);
	printf("Se agrego el pedido %s en la zona %d \n",pedido->nombre,i);
	return true;
}

bool modificar_pedido(vector_t * vectorzonas, char n[], int cantidad){
	int i;
	if (cantidad<0 || cantidad>5) {
		printf("La cantidad maxima permitida es de 5 pizzas\n");
		return false;
		}
	bool encontrado=false;
	pedido_t *pedido,*pedidoaux;
	lista_iter_t *iter;
	lista_t * listaaux;
	for (i=0;i<vector_obtener_cantidad(vectorzonas);i++){

		listaaux= (lista_t*) vector_obtener(vectorzonas, i);
		iter=lista_iter_crear(listaaux);

		while ( (!lista_iter_al_final(iter)) && (!encontrado) ){
			pedidoaux=(pedido_t*) (lista_iter_ver_actual(iter));
			if (pedidoaux){
				if (strcmp (pedidoaux->nombre,n)==0){
					pedido=(lista_iter_ver_actual(iter));
					encontrado=true;
					}
			}
			lista_iter_avanzar(iter);
		}

		lista_iter_destruir(iter);
	}

	if (encontrado){
		pedido->cantidad=cantidad;
		return true;
	}

	return false;
}

bool cancelar_pedido(vector_t * vectorzonas, char n[], int cantidad, int zona){
    pedido_t *auxpedido;

    lista_t* listaaux= (lista_t*) vector_obtener(vectorzonas, (zona-1));
    lista_iter_t *iter=lista_iter_crear(listaaux);
   
    while (lista_iter_al_final(iter)==false){
        auxpedido=(pedido_t*)(lista_iter_ver_actual(iter));
        if ( ( (strcmp (auxpedido->nombre,n)==0)) && auxpedido->cantidad==cantidad){
            printf("Se borro el pedido, %s",auxpedido->nombre);
            lista_borrar(listaaux, iter);
            return true;
            }
        lista_iter_avanzar(iter);
        }
   
    return false;
    }

void enviar(vector_t * vectorzonas, pila_t* pila){

	lista_iter_t *iter,*iterborrar;
	bool primeroencontrado;
	int i,canti,cantf,total;
	pedido_t *pedidoaux,*primerpedido,*pedidof;
	lista_t* listaaux;
	for (i=0;i<vector_obtener_cantidad(vectorzonas);i++){
			primeroencontrado=true;

			while(primeroencontrado)
			{
				primeroencontrado=false;
				canti=0;
				cantf=0;
				total=0;
				pedidof=NULL;

				listaaux= (lista_t*) vector_obtener(vectorzonas, i);
				iter=lista_iter_crear(listaaux);

				while ( !lista_iter_al_final(iter) )
				{

					pedidoaux=(pedido_t*) (lista_iter_ver_actual(iter));
					if (pedidoaux !=NULL)
					{
						if ( (!primeroencontrado) && (pedidoaux->preparado))
						{
							primerpedido=pedidoaux;                  //primer pedido es el primer pedido preparado de esa zona
							canti=pedidoaux->cantidad;
							primeroencontrado=true;
						}
						else if (pedidoaux->preparado)
						{
							cantf=pedidoaux->cantidad;
							if ( ((canti + cantf)<=5) && ((canti+cantf)>total) )
							{
								pedidof=pedidoaux;
								total=canti+cantf;
							}
						}
					}
					lista_iter_avanzar(iter);
				}
				lista_iter_destruir(iter);
				if ( (primeroencontrado) && (pedidof!=NULL))
					printf("Se envio el pedido %s junto con el pedido %s \n",primerpedido->nombre,pedidof->nombre);
				else  if (primeroencontrado){
					printf("Se envio el pedido %s \n",primerpedido->nombre);
				}
				iterborrar=lista_iter_crear(listaaux);
				while (!lista_iter_al_final(iterborrar))
				{
					if ( primerpedido==lista_iter_ver_actual(iterborrar) )
					{
						pila_apilar(pila,primerpedido);
						lista_borrar(listaaux,iterborrar);
					}
					else{
						if (pedidof==lista_iter_ver_actual(iterborrar))
							{
								pila_apilar(pila,pedidof);
								lista_borrar(listaaux,iterborrar);
							}
						else lista_iter_avanzar(iterborrar);
					}
				}
				lista_iter_destruir(iterborrar);

			}
	}

}

pila_t* mostrar_enviados(pila_t* pila, vector_t *vectorzonas, vector_t* vectorprecios){
	pedido_t* pedido;
	pila_t * pila_nueva=pila_crear();
	pila_t *pila_aux=pila_crear();
	int recaudado=0;
	printf ("\n");
	printf ("Los pedidos que fueron enviados, en orden del mas reciente al mas antiguo, son: \n");
	printf ("\n");
	while (!pila_esta_vacia(pila)){
		pedido=pila_desapilar(pila);
		int* precio= (int*) vector_obtener(vectorprecios, pedido->zona-1);
		recaudado+=( (*precio) *(pedido->cantidad));
		pila_apilar(pila_aux, pedido);
		printf("Pedido: %s Cantidad: %d Zona: %d \n",pedido->nombre,pedido->cantidad,pedido->zona);
	}
	printf("\n\n");
	printf("Lo recaudado en total en los ultimos envios: $ %d\n", recaudado);
	while (!pila_esta_vacia(pila_aux)){
		pila_apilar(pila_nueva, pila_desapilar(pila_aux));
		}
	pila_destruir(pila_aux);
	pila_t *piladestruir=pila;
	if (piladestruir)
		pila_destruir(piladestruir);
	return pila_nueva;
}

void mostrar_menu(){
	printf ("\n-------------MENU-----------------\n");
	printf ("Eliga una opcion:\n 1: Registrar pedido.\n 2: Modificar o cancelar un pedido.\n 3: Preparar todos los pedidos.\n 4: Enviar todos los pedidos.\n 5: Agregar una zona.\n 6: Mostrar registrados y enviados.\n 7: Salir. \n\n");
}


bool preparar_pedidos(vector_t * vectorzonas, vector_t * vectorprecios){
	int i, lvacias=0;
	pedido_t *pedido;
	lista_iter_t *iter;
	lista_t* listaaux;
	
	int cantidad=vector_obtener_cantidad(vectorzonas);
	for (i=0; i<cantidad; i++){
		listaaux= (lista_t*) vector_obtener(vectorzonas, i);
		if(lista_esta_vacia(listaaux)==true){
			lvacias++;
			printf("No hay pedidos en la zona %d\n", i+1);
			}
		}
	
	if (lvacias==cantidad) return false;
	
	for (i=0; i<cantidad; i++){
		listaaux= (lista_t*) vector_obtener(vectorzonas, i);
		iter=lista_iter_crear(listaaux);
		while (lista_iter_al_final(iter)==false){	
			pedido=(pedido_t *)(lista_iter_ver_actual(iter));
			pedido->preparado=true;
			lista_iter_avanzar(iter);
			}
		lista_iter_destruir(iter);
		}
	return true;	
	}

void registrar_pedido(vector_t* vectorzonas){
	bool resultado;
	pedido_t *pedido=malloc(sizeof(pedido_t));
	lista_t *listaaux;
		if (pedido==NULL){
			printf("Ocurrio un error, pruebe de vuelta\n");
			return;
			};
	int cantidad=vector_obtener_cantidad(vectorzonas);

	printf("Ingrese la zona del cliente:\n");
	scanf("%d", &(pedido->zona));
	while ((pedido->zona)<1 || (pedido->zona)> cantidad){
		printf ("la zona tiene que se del 1 al %d. Ingresela de vuelta\n",cantidad);
		scanf("%d", &(pedido->zona));  
		  }
	
	printf("A continuacion ingrese el nombre del cliente:\n");
	scanf("%s", pedido->nombre);
	
	printf("Ahora ingrese la cantidad de pizzas pedidas:\n");
	scanf("%d", &(pedido->cantidad));
		while ((pedido->cantidad)<1 || (pedido->cantidad)> 5){
		printf ("la cantidad tiene que se del 1 al 5. Ingresela de vuelta\n");
		scanf("%d", &(pedido->cantidad));  
		  }
	
	pedido->preparado=false;
	
	listaaux = (lista_t*) vector_obtener(vectorzonas,pedido->zona-1);
	resultado=lista_insertar_ultimo(listaaux, pedido);
	
	if (resultado==false){
		printf("Error al ingresar pedido\n");
		}else {
			printf("Se agrego el pedido correctamente\n");
			}
	}
	
//

void definir_precios(vector_t *vectorprecios){
	int i;
	int *precio;
	for (i=0; i<5; i++){
		printf("Ingrese el precio para la zona %d\n", i+1);
		precio= (int*) vector_obtener(vectorprecios,i);
		scanf("%d", &(*precio) );
		}
	
	}
	
void mostrar_registrados (vector_t *vectorzonas){
    int i;
    pedido_t *auxpedido;
    lista_t* listaaux;
    int cantidad = vector_obtener_cantidad(vectorzonas);
    for (i=0; i<cantidad; i++){
    	listaaux = (lista_t*) vector_obtener(vectorzonas,i);
		printf("\n");
        lista_iter_t *iter;
        iter=lista_iter_crear(listaaux);
        printf("Pedidos registrados de la zona %d\n", i+1);
        printf("Nombre        cantidad        zona\n");
        while(lista_iter_al_final(iter)==false){
            auxpedido=(pedido_t *)(lista_iter_ver_actual(iter));
            printf("%s            %d            %d\n",auxpedido->nombre, auxpedido->cantidad, auxpedido->zona);
            if (auxpedido->preparado==true) printf ("Preparado\n");           
            lista_iter_avanzar(iter);
            }
        lista_iter_destruir(iter);
        }
    }
    

