#include "server_apagador.h"

server_apagador::server_apagador(server_servidor* servidor) {
  this->servidor = servidor;
}

server_apagador::~server_apagador() {
}

void server_apagador::run() {
  char entrada;
  std::cin >> entrada;
  while (entrada != 'q') {
    std::cin >> entrada;
  }
  servidor->apagar();
}
