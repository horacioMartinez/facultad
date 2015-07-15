#include "client_cliente.h"
#include "client_socket.h"
#include <iostream>
#include <stdio.h>
#include <string>

int main(int argc, char** argv) {
  client_cliente cliente;
  int retorno = 2;
  if (argc == 2)
    cliente.conectar(argv[1]);
  else
    return 1;

  std::string entrada;
  while (retorno == 2) {
    std::getline(std::cin, entrada);
    entrada += '\n';
    retorno = cliente.procesar_entrada(entrada);
  }
  return retorno;
}
