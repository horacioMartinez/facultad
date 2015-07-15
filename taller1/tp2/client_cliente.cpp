#include "client_cliente.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

client_cliente::client_cliente() {
}
client_cliente::~client_cliente() {
}

void client_cliente::conectar(char* ip_y_Puerto) {
  using std::string;
  string aux = ip_y_Puerto;
  string delimitador = ":";
  ipServer = aux.substr(0, aux.find(delimitador));
  aux.erase(0, aux.find(delimitador) + delimitador.length());
  puertoServer = aux.substr(0, aux.find(delimitador));

  socket.conectar(ipServer, puertoServer);
}

int client_cliente::procesar_entrada(const std::string &entrada) {
  using std::string;

  std::vector<string> vectorMensaje;
  protocolo.tokenizar(entrada, ' ', vectorMensaje);
  string comando = vectorMensaje[0];

  if (comando.compare("S") == 0)
    return 0;

  // Si los hay, saca los ceros de la izquierda
  if ((comando.compare("R") == 0) || (comando.compare("B") == 0)) {
    if (vectorMensaje.size() == 3) {
      std::stringstream aux;
      aux << atoi(vectorMensaje[2].c_str());
      vectorMensaje[2] = aux.str();
    }
  }

  if (socket.enviar(protocolo.concatenar_mensaje(vectorMensaje)) < 1)
    return 1;
  string respuesta = "";
  if (socket.recibir(respuesta, '\n') < 1)
    return 1;
  protocolo.reemplazar_fin_de_linea(respuesta);
  std::cout << respuesta;
  return 2;
}

