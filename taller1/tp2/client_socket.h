#ifndef SRC_CLIENT_SOCKET_H_
#define SRC_CLIENT_SOCKET_H_
#include "common_socket.h"
#include <string>

class client_socket : public common_socket {
 public:
  client_socket();
  virtual ~client_socket();
  // Se conecta a la ip y puerto, si se ejecuta exitosamente devuelve 0,
  // en caso de error devuelve -1.
  int conectar(const std::string &ip, const std::string &puerto);
};

#endif
