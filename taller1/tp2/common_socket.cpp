#include "common_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

common_socket::common_socket() {
  setSocketfd(0);
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;  //TCP
}

common_socket::~common_socket() {
  cerrar();
}

int common_socket::enviar(const std::string &mensaje) {
  int n = 0;
  int m = 0;
  int tamanio = mensaje.length();
  while (n < tamanio) {
    m = send(socketfd, &mensaje.c_str()[n], tamanio - n, 0);
    if (m > 0) {
      n += m;
    } else {
      if (m == 0)  //cerro el socket
        return 0;
      if (m < 0) {
        perror("Error al enviar");
        return -1;
      }
    }
  }
  return m;
}

int common_socket::recibir(std::string& mensaje, char terminador) {
  char buffer[MAX_LARGO_MENSAJE + 1];
  memset(buffer, 0, MAX_LARGO_MENSAJE + 1);
  int bytesRecibidos = 0;
  mensaje = "";
  while (mensaje.find(terminador) == std::string::npos) {
    bytesRecibidos = recv(socketfd, buffer, MAX_LARGO_MENSAJE - 1, 0);
    if (bytesRecibidos == -1) {
      perror("Error al recibir");
      return -1;
    }
    // si recibe 0, cerro el socket
    if (bytesRecibidos == 0) {
      return 0;
    }
    mensaje += buffer;
  }
  //si se encuentra el terminador antes del final, se recibieron datos de mas
  if (mensaje.find(terminador) != mensaje.size()){
    mensaje = mensaje.substr(0, mensaje.find(terminador)+1);
  }
  return bytesRecibidos;
}

int common_socket::apagar(int como) {
  int res = shutdown(this->socketfd, como);
  if (res < 0)
    perror("Error al apagar");
  return res;
}

int common_socket::cerrar() {
  int res = close(socketfd);
  if (res < 0)
    perror("Error al cerrar");
  return res;
}

void common_socket::setSocketfd(int socketfd) {
  this->socketfd = socketfd;
}
