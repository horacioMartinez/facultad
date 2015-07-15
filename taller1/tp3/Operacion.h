#ifndef SRC_OPERACION_H_
#define SRC_OPERACION_H_

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Operacion {
 public:
  virtual const char* getCodigo() = 0;
  virtual void operar(int &puntero_datos, std::vector<signed char> &datos,
                      int &pos, std::stack<int> &pilaPosLoops,
                      int &ejecutar) = 0;
  friend std::ostream &operator<<(std::ostream &salida, Operacion &operacion);
  virtual ~Operacion();
};

#endif /* SRC_OPERACION_H_ */
