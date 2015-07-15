#ifndef SRC_COMA_H_
#define SRC_COMA_H_
#include "Operacion.h"
#include <vector>
#include <string>
#include <stack>

class Coma : public Operacion {
 public:
  void operar(int &puntero_datos, std::vector<signed char> &datos, int &pos,
              std::stack<int> &pilaPosLoops, int &ejecutar);
  const char* getCodigo();
};

#endif /* SRC_COMA_H_ */
