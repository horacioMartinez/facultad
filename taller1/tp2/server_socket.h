#ifndef SRC_SERVER_SOCKET_H_
#define SRC_SERVER_SOCKET_H_
#include "common_socket.h"
#include <string>

class server_socket : public common_socket {
 public:
  server_socket();
  virtual ~server_socket();

  // Crea un socket y les asigna la IP de la maquina y un puerto.
  int enlazar(const std::string &puerto);
  // Habilita al socket para recibir conexiones, con una cola
  // de largo maximo maximas_conecciones.
  int escuchar(int maximas_conecciones);
  // Acepta la conexion de un socket cliente y crea
  // un nuevo socket para comunicarse.
  int aceptar(common_socket &socket_nuevo);
};

#endif
