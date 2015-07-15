#include "server_thread.h"
#include "server_servidor.h"
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <list>

#define MAXIMA_CANTIDAD_CONECCIONES 200

server_servidor::server_servidor(int argc, char* argv[]) {
  this->cargar_datos_entrada(argc, argv);
  this->seguirAceptando = true;
  procesadorMutex = new pthread_mutex_t;
  pthread_mutex_init(procesadorMutex, NULL);
}

server_servidor::~server_servidor() {
  pthread_mutex_destroy(procesadorMutex);
  delete procesadorMutex;
  std::list<common_socket*>::iterator socketIt;
  for (socketIt = sockets.begin(); socketIt != sockets.end(); ++socketIt)
    delete (*socketIt);
}

void server_servidor::cargar_datos_entrada(int argc, char* argv[]) {
  std::string puerto;
  procesador.cargar_datos_entrada(argc, argv, puerto);
  servidorSocket.enlazar(puerto);
  servidorSocket.escuchar(MAXIMA_CANTIDAD_CONECCIONES);
}

void server_servidor::ejecutar() {
  int aux;
  while (seguirAceptando) {
    common_socket* nuevo_socket = new common_socket;
    aux = servidorSocket.aceptar((*nuevo_socket));
    if (aux != -1) {
      sockets.push_back(nuevo_socket);
      server_comunicador* nuevo_thread = new server_comunicador(
          nuevo_socket, &procesador, procesadorMutex);
      threadsComunicadores.push_back(nuevo_thread);
      nuevo_thread->start();
      terminarComunicadoresMuertos();
    } else {
      delete nuevo_socket;
    }
  }
  terminarComunicadores();
  procesador.apagar();
}

void server_servidor::apagar() {
  this->seguirAceptando = false;
  servidorSocket.apagar(SHUT_RD);  // por si esta trabado en el accept()
}

void server_servidor::setSeguirAceptando(bool seguirAceptando) {
  this->seguirAceptando = seguirAceptando;
}

void server_servidor::terminarComunicadoresMuertos() {
  std::list<server_comunicador*>::iterator threadtIt;
  for (threadtIt = threadsComunicadores.begin();
      threadtIt != threadsComunicadores.end();) {
    if ((*threadtIt)->isMuerto()) {
      (*threadtIt)->apagarSocket();
      (*threadtIt)->join();
      delete (*threadtIt);
      threadtIt = threadsComunicadores.erase(threadtIt);
    } else {
      ++threadtIt;
    }
  }
}

void server_servidor::terminarComunicadores() {
  std::list<server_comunicador*>::iterator threadtIt;
  for (threadtIt = threadsComunicadores.begin();
      threadtIt != threadsComunicadores.end(); ++threadtIt) {
    (*threadtIt)->apagarSocket();
    (*threadtIt)->join();
    delete (*threadtIt);
  }
}
