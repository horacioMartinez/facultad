#ifndef SRC_SERVER_SERVIDOR_H_
#define SRC_SERVER_SERVIDOR_H_

#include "server_comunicador.h"
#include "server_procesador.h"
#include "server_socket.h"
#include <pthread.h>
#include <list>
#include <string>

class server_servidor {
 public:
  server_servidor(int argc, char* argv[]);
  virtual ~server_servidor();
  void ejecutar();
  // Procesa la peticion y devuelve la respuesta.
  std::string procesar_peticion(const std::string &peticion);
  void apagar();
  void setSeguirAceptando(bool seguirAceptando);

 private:
  void cargar_datos_entrada(int argc, char* argv[]);
  void terminarComunicadoresMuertos();
  void terminarComunicadores();
  bool seguirAceptando;
  server_procesador procesador;
  pthread_mutex_t* procesadorMutex;
  server_socket servidorSocket;
  std::list<common_socket*> sockets;
  std::list<server_comunicador*> threadsComunicadores;
};

#endif
