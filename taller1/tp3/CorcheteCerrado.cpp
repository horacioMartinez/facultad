#include "CorcheteCerrado.h"
#include <string>
#include <vector>
#include <stack>

void CorcheteCerrado::operar(int &puntero_datos,
                             std::vector<signed char> &datos, int &pos,
                             std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar < 1)
    ejecutar++;

  if (ejecutar == 1) {
    if (datos[puntero_datos % datos.size()] != 0) {
      pos = pilaPosLoops.top() - 1;
    }
  }
  pilaPosLoops.pop();
}

const char* CorcheteCerrado::getCodigo() {
  return "}";
}
