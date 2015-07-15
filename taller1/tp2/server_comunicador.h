#ifndef SRC_SERVER_COMUNICADOR_H_
#define SRC_SERVER_COMUNICADOR_H_

#include <pthread.h>
#include "server_thread.h"
#include "server_procesador.h"
#include "common_socket.h"

class server_comunicador : public server_thread {
 public:
  server_comunicador(common_socket* socket, server_procesador *procesador,
                     pthread_mutex_t* procesadorMutex);
  virtual ~server_comunicador();
  void run();
  void apagarSocket();
 private:
  common_socket* socket;
  server_procesador* procesador;
  pthread_mutex_t* procesadorMutex;
};

#endif
