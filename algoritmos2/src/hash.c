
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "lista.h"
#include <stdio.h>

#define TAM 100

struct hash {
	size_t cantidad;
	size_t tam;
	lista_t **tabla;
	hash_destruir_dato_t destruir_dato;
};

struct hash_dato{
	char *clave;
	void *dato;
	};

struct hash_iter{
	lista_iter_t* iterlista;
	size_t pos;
	size_t tam;
	lista_t **tabla;
};

char *copiarstring (const char *s) {
    char *d = malloc (strlen (s) + 1);
    if (d == NULL) return NULL;
    strcpy (d,s);
    return d;
}

size_t fhash(const char* clave, size_t tam){
    size_t hashval;

    for(hashval=0;*clave != '\0'; clave++)
    	hashval = *clave + 31 * hashval;

    return (hashval % tam);
    }

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	
	int i;
	hash_t *hash=malloc(sizeof(hash_t));
	if (hash==NULL) return NULL;
	
	hash->tabla=malloc(TAM * sizeof(lista_t *));
	if (hash->tabla==NULL) return NULL;
	
	for (i=0; i<TAM; i++){
		hash->tabla[i]=lista_crear();

		if (hash->tabla[i]==NULL) return NULL;
		}
	hash->tam=TAM;
	hash->cantidad=0;
	hash->destruir_dato=destruir_dato;	
	
	return hash;
	}
	
hash_dato_t *hash_iter_ver_nodo_actual(hash_iter_t *iter){
	hash_dato_t* hashdato;
	if (iter->iterlista==NULL) return NULL;
	hashdato = lista_iter_ver_actual(iter->iterlista);
	if (hashdato==NULL) return NULL;
	return hashdato;
}

void hash_redimensionar (hash_t* hash){

	hash_t* viejo= malloc(sizeof(hash_t));
	hash_dato_t *aux;
	viejo->tam=hash->tam;
	viejo->tabla=hash->tabla;
	viejo->cantidad=hash->cantidad;
	viejo->destruir_dato=hash->destruir_dato;

	hash->tam=(viejo->tam)*10;
	hash->tabla=malloc(hash->tam*sizeof(lista_t *));
	hash->cantidad=0;
	int i;
	for (i=0; i<hash->tam; i++)
		hash->tabla[i]=lista_crear();

	lista_iter_t * iterlista=NULL;
	for (i=0; i<viejo->tam;i++){

		if (!lista_esta_vacia(viejo->tabla[i]))
			iterlista= lista_iter_crear(viejo->tabla[i]);

		while (!lista_esta_vacia(viejo->tabla[i])) {
			aux=lista_borrar(viejo->tabla[i], iterlista);
			hash_guardar(hash,aux->clave,aux->dato);
			free(aux->clave);
			free(aux);
		}
		if (iterlista!=NULL)
			lista_iter_destruir(iterlista);
		iterlista=NULL;
	}

	hash_destruir(viejo);
 }

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	bool resultado;
	hash_dato_t* datohashaux;
	void* aux;
	
	if (hash->cantidad*2>hash->tam)
		hash_redimensionar(hash);

	hash_dato_t *datohash=malloc(sizeof(hash_dato_t));
		if (datohash==NULL) return false;

	datohash->dato=dato;
	char * destino;
	destino=copiarstring(clave);
	datohash->clave=destino;
	int indice=fhash(clave, hash->tam);


	if (hash_pertenece(hash, clave)==true){
			lista_iter_t *iter=lista_iter_crear(hash->tabla[indice]);
			while (lista_iter_al_final(iter)==false){
				datohashaux=lista_iter_ver_actual(iter);
				if (datohashaux!=NULL){
					if (strcmp(datohashaux->clave, destino)==0){
						aux=datohashaux->dato;
						datohashaux->dato=dato;
						if (hash->destruir_dato)
							hash->destruir_dato(aux);
						lista_iter_destruir(iter);
						free(datohash);
						free(destino);
						return true;
					}
				}
				lista_iter_avanzar(iter);
			}
		}

	else{
		resultado=lista_insertar_primero(hash->tabla[indice], datohash);
		hash->cantidad++;
	}
	return resultado;
	}

bool hash_pertenece(const hash_t *hash, const char *clave){
	
	size_t indice= fhash(clave, hash->tam);
	hash_dato_t *datohash;
	datohash=NULL;
	lista_iter_t *iter=lista_iter_crear(hash->tabla[indice]);
	while (lista_iter_al_final(iter)==false){
		datohash=lista_iter_ver_actual(iter);
		if (datohash!=NULL){
			if (strcmp(clave, datohash->clave)==0){
				lista_iter_destruir(iter);
				return true;
			}
				else lista_iter_avanzar(iter);
			}
		}
	lista_iter_destruir(iter);
	return false;
	}
	
void *hash_borrar(hash_t *hash, const char *clave){
	
	int indice;
	indice=fhash(clave, hash->tam);
	hash_dato_t* datohash;
	void *dato;
	
	if (hash_pertenece(hash, clave)==true){
		lista_iter_t *iter=lista_iter_crear(hash->tabla[indice]);
		
		while (!lista_iter_al_final(iter)){
			datohash=lista_iter_ver_actual(iter);
			if (datohash!=NULL){
				if (strcmp(clave, datohash->clave)==0){
					dato=datohash->dato;
					free(datohash->clave);
					if (datohash->dato!=NULL)
						if (hash->destruir_dato!=NULL)
							hash->destruir_dato(datohash->dato);
					free(datohash);
					lista_borrar(hash->tabla[indice], iter);
					hash->cantidad--;
					lista_iter_destruir(iter);
					return (dato);
				}
			}
			lista_iter_avanzar(iter);
			}
		lista_iter_destruir(iter);
		}
	return NULL;
	}
	
void *hash_obtener(const hash_t *hash, const char *clave){
	hash_dato_t *datohash;
	size_t indice=fhash(clave, hash->tam);
	
	if (hash_pertenece(hash, clave)==true){
		lista_iter_t *iter=lista_iter_crear(hash->tabla[indice]);
		while (lista_iter_al_final(iter)==false){
			datohash=lista_iter_ver_actual(iter);
			if (datohash!=NULL){
				if (strcmp(clave, datohash->clave)==0){
					lista_iter_destruir(iter);
					return (datohash->dato);
				}
			}
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
	}
	
	return NULL;
}

size_t hash_cantidad(const hash_t *hash){
	
	return (hash->cantidad);
	}

	
void hash_destruir(hash_t *hash){
	int i;
	hash_dato_t* datoaux;
	for (i=0; i<(hash->tam); i++){
			while (!lista_esta_vacia(hash->tabla[i])){
				datoaux=lista_borrar_primero(hash->tabla[i]);
				free(datoaux->clave);
				if (datoaux->dato!=NULL){
					if (hash->destruir_dato)
						hash->destruir_dato(datoaux->dato);
				}
				free(datoaux);
			}
			lista_destruir(hash->tabla[i], NULL);
	}
	free(hash->tabla);
	free(hash);
	}


hash_iter_t *hash_iter_crear(const hash_t *hash){
	int i;
	bool res;
	hash_iter_t *iterhash=malloc(sizeof(hash_iter_t));
	lista_iter_t *iter;
	res=false;
	iter=NULL;
	i=0;
	while ((i<hash->tam) && (res==false)){
		if (!lista_esta_vacia(hash->tabla[i])){
			res=true;
			iter=lista_iter_crear(hash->tabla[i]);
			iterhash->pos=i;
		}
		i++;
	}

	if (res==false) {
		iter=lista_iter_crear(hash->tabla[hash->tam-1]);
		iterhash->pos=hash->tam-1;
	}
	iterhash->iterlista=iter;
	iterhash->tam=(size_t) hash->tam;
	iterhash->tabla=(lista_t **) hash->tabla;
	return iterhash;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	hash_dato_t* hashdato;
	hashdato=lista_iter_ver_actual(iter->iterlista);
	if (hashdato==NULL) return NULL;
	return hashdato->clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){

	if (iter==NULL) return true;

	if (!lista_iter_al_final(iter->iterlista)) return false;

	int i;
	for (i=iter->pos+1;i<iter->tam;i++){
		if (!lista_esta_vacia(iter->tabla[i])) return false;
	}

	return true;
}


bool hash_iter_avanzar(hash_iter_t *iter){
	int i;
	bool res;
	lista_iter_t *iternuevo;
	iternuevo=NULL;
	if (iter->iterlista==NULL)
			 return false;
	res=false;

	if (hash_iter_al_final(iter)) return false;

	bool resaux=lista_iter_avanzar(iter->iterlista);

	if (lista_iter_al_final(iter->iterlista)){
		i=(iter->pos)+1;
		while ((i<iter->tam) && (!res)){
			if (!lista_esta_vacia(iter->tabla[i])){
						res=true;
						iternuevo=lista_iter_crear(iter->tabla[i]);
						iter->pos=i;
			}
			i++;
		}
		if (res==false)
			return resaux;

		lista_iter_destruir(iter->iterlista);
		iter->iterlista=iternuevo;
	}

	return true;

}

void hash_iter_destruir(hash_iter_t* iter){

	if (iter->iterlista!=NULL)
		lista_iter_destruir(iter->iterlista);
	
	free(iter);
}



