#include "server_apagador.h"
#include "server_servidor.h"
#include <string>

int main(int argc, char** argv) {
  std::string mensaje;
  server_servidor servidor(argc, argv);
  server_apagador apagador(&servidor);
  apagador.start();
  servidor.ejecutar();
  apagador.join();
  return 0;
}
