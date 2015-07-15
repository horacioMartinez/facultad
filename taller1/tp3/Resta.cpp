#include "Resta.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>

void Resta::operar(int &puntero_datos, std::vector<signed char> &datos,
                   int &pos, std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar == 1)
    datos[puntero_datos % datos.size()] += -1;
}

const char* Resta::getCodigo() {
  return "data[AT(dataptr)] += -1;";
}
