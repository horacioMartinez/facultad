#ifndef ES_H
#define ES_H

#define EJECUCION_EXITOSA 0
#define ARGUMENTOS_INVALIDOS 1
#define ES_ERRONEOS 2

// Valida los parametros y si estos lo indican abre los archivos de entrada
// y/o salida especificados.
// Devuelve 0 si se ejecuto correctamente, 1 si los parametros no son validos
// o 2 si hubo errores al tratar de abrir/crear los archivos.
int es_validar_y_abrir(int argc, char* argv[], FILE** entrada, FILE** salida);

// Verificar si es necesario cerrar los archivos y si es asi lo hace
void es_cerrar_archivos(FILE*entrada, FILE*salida);

#endif
