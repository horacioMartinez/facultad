#include "Coma.h"
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

void Coma::operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
                  std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar == 1) {
    signed char c = std::cin.get();
    datos[puntero_datos % datos.size()] = std::cin.eof() ? 0 : c;
  }
}

const char* Coma::getCodigo() {
  return "c = std::cin.get();\ndata[AT(dataptr)] = std::cin.eof() ? 0 : c;";
}
