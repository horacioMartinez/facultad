#ifndef SRC_SUMA_H_
#define SRC_SUMA_H_
#include "Operacion.h"
#include <vector>
#include <string>
#include <stack>

class Suma : public Operacion {
 public:
  void operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
              std::stack<int> &pilaPosLoops, int &ejecutar);
  const char* getCodigo();
};

#endif /* SRC_SUMA_H_ */
