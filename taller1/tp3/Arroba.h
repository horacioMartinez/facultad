#ifndef SRC_ARROBA_H_
#define SRC_ARROBA_H_

#include <vector>
#include <string>
#include <stack>
#include "Operacion.h"

class Arroba : public Operacion {
 public:
  void operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
              std::stack<int> &pilaPosLoops, int &ejecutar);
  const char* getCodigo();
};

#endif /* SRC_ARROBA_H_ */
