#include "client_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

client_socket::client_socket() {
}

client_socket::~client_socket() {
}

int client_socket::conectar(const std::string &direccion,
                            const std::string &puerto) {
  int aux;
  struct addrinfo *serverInfo;
  aux = 0;
  aux = getaddrinfo(direccion.c_str(), puerto.c_str(), &hints, &serverInfo);

  if (aux != 0) {
    fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(aux));
    return aux;
  }
  socketfd = socket(serverInfo->ai_family, serverInfo->ai_socktype,
                    serverInfo->ai_protocol);
  if (socketfd == -1) {
    perror("Error al crear socket");
    return -1;
  }
  if (connect(socketfd, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
    close(socketfd);
    perror("Error al conectar");
    return -1;
  }
  freeaddrinfo(serverInfo);
  return 0;
}
