#ifndef SRC_MAYOR_H_
#define SRC_MAYOR_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include "Operacion.h"

class Mayor : public Operacion {
 public:
  void operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
              std::stack<int> &pilaPosLoops, int &ejecutar);
  const char* getCodigo();
};

#endif /* SRC_MAYOR_H_ */
