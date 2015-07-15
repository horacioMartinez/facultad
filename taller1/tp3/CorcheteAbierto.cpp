#include "CorcheteAbierto.h"
#include <string>
#include <vector>
#include <stack>

void CorcheteAbierto::operar(int &puntero_datos,
                             std::vector<signed char> &datos, int &pos,
                             std::stack<int> &pilaPosLoops, int &ejecutar) {
  pilaPosLoops.push(pos);
  if (ejecutar < 1)
    ejecutar--;
  else if (datos[puntero_datos % datos.size()] == 0)
    ejecutar--;
}

const char* CorcheteAbierto::getCodigo() {
  return "while(data[AT(dataptr)]) {";
}
