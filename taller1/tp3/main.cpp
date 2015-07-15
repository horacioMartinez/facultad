#include <iostream>
#include <stdlib.h>
#include "Interpretador.h"

int main(int argc, char** argv) {
  if (argc != 4)
    return 1;
  int cant_bytes = atoi(argv[1]);
  Interpretador interpretador;
  if (!interpretador.correr(cant_bytes, *argv[2], argv[3]))
    return 1;
  return 0;
}
