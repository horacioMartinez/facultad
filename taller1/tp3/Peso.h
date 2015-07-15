#ifndef SRC_PESO_H_
#define SRC_PESO_H_

#include <vector>
#include <string>
#include <stack>
#include "Operacion.h"

class Peso : public Operacion {
 public:
  void operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
              std::stack<int> &pilaPosLoops, int &ejecutar);
  const char* getCodigo();
};

#endif /* SRC_PESO_H_ */
