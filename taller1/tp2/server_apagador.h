#ifndef SRC_SERVER_APAGADOR_H_
#define SRC_SERVER_APAGADOR_H_

#include "server_thread.h"
#include "server_servidor.h"

class server_apagador : public server_thread {
 public:
  explicit server_apagador(server_servidor* servidor);
  virtual ~server_apagador();
  void run();
 private:
  server_servidor* servidor;
};

#endif
