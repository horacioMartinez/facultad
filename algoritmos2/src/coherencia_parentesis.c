#include <stdio.h>
#include <stdbool.h>
#include "pila.h"

/* La idea en este problema es recorrer la expresion, y apilar cada 
 * apertura de parentesis que encuentra. Cuando encuentra un cierre de
 * parentesis, desapila un elemento. Si no saca un parentesis de
 * apertura es que la expresion es incorrecta. Cuando termina de evaluar
 * la expresion, si quedo algo en la pila es que falta algun cierre, por
 * lo tanto la expresion es incorrecta. */


// Chequea que los parentesis esten correctamente cerrados
// en la expresion
bool coherencia_parentesis(char* expresion) {

    pila_t* pila = pila_crear();
    char *aux = NULL;
    int i = 0;

    while(expresion[i] != '\0') {
        if(expresion[i] == '(') {
            pila_apilar(pila, &expresion[i]);
        } else if(expresion[i] == ')') {
            aux = pila_desapilar(pila);
            // Si la pila esta vacia, devuelve NULL
            if(aux == NULL || *aux != '(') {
                return false;
            }
        }
        i++;
    }
    // Si quedo algo en la pila es que sobran parentesis de apertura
    if(pila_esta_vacia(pila)) {
        return true;
    } else {
        return false;
    }
}
