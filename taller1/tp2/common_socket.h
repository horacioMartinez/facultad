#ifndef SRC_COMMON_SOCKET_H_
#define SRC_COMMON_SOCKET_H_

#include <string>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_LARGO_MENSAJE 1000

class common_socket {
 public:
  common_socket();
  // Envia el mensaje hasta que este llegue, si se envia correctamente devuelve
  // la cantidad de bytes transmitidos, si el socket destinatario esta cerrado
  // devuelve 0, si se produce un error devuelve -1.
  int enviar(const std::string &mensaje);
  // Recibe mensajes hasta encontrar el char terminador, devuelve la cantidad
  // de bytes recibidos, 0 si se cerró el socket enviante o -1 en caso de un
  // error devuelve 0, si se produce un error devuelve -1.
  int recibir(std::string& mensaje, char terminador);
  // Hace un shutdown de forma 'como' al socket.
  int apagar(int como);
  // cierra el file descriptor del socket.
  int cerrar();
  virtual ~common_socket();
  void setSocketfd(int socketfd);

 protected:
  struct addrinfo hints;
  int socketfd;
};

#endif
