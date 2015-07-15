#include "server_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

server_socket::server_socket() {
  hints.ai_flags = AI_PASSIVE;  // usa IP de la maquina
}
server_socket::~server_socket() {
}

int server_socket::enlazar(const std::string &puerto) {
  struct addrinfo *info;
  int si = 1;
  int res = 0;

  res = getaddrinfo(NULL, puerto.c_str(), &hints, &info);
  if (res != 0) {
    fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(res));
    return -1;
  }
  socketfd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
  // para evitar "Address already in use"
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &si, sizeof(int)) == -1)
    perror("Error en setsockopt");

  res = bind(socketfd, info->ai_addr, info->ai_addrlen);
  if (res == -1) {
    close(socketfd);
    perror("Error al enlazar");
  }
  freeaddrinfo(info);
  return res;
}

int server_socket::escuchar(int maximas_conecciones) {
  int res;
  res = listen(socketfd, maximas_conecciones);
  if (res == -1)
    perror("Error al escuchar");
  return res;
}

int server_socket::aceptar(common_socket &socket_nuevo) {
  int socket_fd_nuevo;
  socklen_t tamanio_info;
  struct sockaddr_storage info_socket_cliente;
  tamanio_info = sizeof info_socket_cliente;

  socket_fd_nuevo = accept(socketfd, (struct sockaddr*) &info_socket_cliente,
                           &tamanio_info);
  if (socket_fd_nuevo == -1)
    return -1;
  socket_nuevo.setSocketfd(socket_fd_nuevo);
  return 0;
}
