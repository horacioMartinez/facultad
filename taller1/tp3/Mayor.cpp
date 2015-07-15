#include "Mayor.h"
#include <string>
#include <vector>
#include <stack>

void Mayor::operar(int &puntero_datos, std::vector<signed char> &datos,
                   int &pos, std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar == 1)
    puntero_datos += 1;
}

const char* Mayor::getCodigo() {
  return "dataptr += 1;";
}
