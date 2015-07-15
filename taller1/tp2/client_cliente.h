#ifndef SRC_CLIENT_CLIENTE_H_
#define SRC_CLIENT_CLIENTE_H_

#include "common_protocolo.h"
#include "client_socket.h"
#include <string>

class client_cliente {
 public:
  client_cliente();
  virtual ~client_cliente();
  void conectar(char* ipPuerto);
  int procesar_entrada(const std::string &entrada);

 private:
  std::string ipServer;
  std::string puertoServer;
  client_socket socket;
  common_protocolo protocolo;
};

#endif
