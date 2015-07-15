#include "server_comunicador.h"
#include <string>

server_comunicador::server_comunicador(common_socket* socket,
                                       server_procesador *procesador,
                                       pthread_mutex_t* procesadorMutex) {
  this->muerto = false;
  this->socket = socket;
  this->procesador = procesador;
  this->procesadorMutex = procesadorMutex;
}

server_comunicador::~server_comunicador() {
}

void server_comunicador::run() {
  while (!this->muerto) {
    int aux;
    std::string mensajeRecibido;
    aux = socket->recibir(mensajeRecibido, '\n');
    if (aux < 1)
      this->muerto = true;
    if (!mensajeRecibido.empty()) {
      pthread_mutex_lock(procesadorMutex);
      std::string respuesta = procesador->procesar_peticion(mensajeRecibido);
      pthread_mutex_unlock(procesadorMutex);
      aux = socket->enviar(respuesta);
      if (aux < 1)
        this->muerto = true;
    }
  }
}

void server_comunicador::apagarSocket() {
  socket->apagar(SHUT_RDWR);
}
