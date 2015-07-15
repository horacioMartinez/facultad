#include "Punto.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>

void Punto::operar(int &puntero_datos, std::vector<signed char> &datos,
                   int &pos, std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar == 1)
    std::cout << datos[puntero_datos % datos.size()];
}

const char* Punto::getCodigo() {
  return "std::cout << data[AT(dataptr)];";
}
