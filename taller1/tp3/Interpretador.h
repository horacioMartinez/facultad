#ifndef SRC_INTERPRETADOR_H_
#define SRC_INTERPRETADOR_H_

#include <vector>

#include "Operacion.h"
#include "Parseador.h"

class Interpretador {
 public:
  Interpretador();
  ~Interpretador();
  bool correr(int n, char modo, char* dirArchivo);

 private:
  Parseador parseador;
  void ejecutar();
  void compilar();
  int n;
  std::vector<signed char> datos;
  std::vector<Operacion*> instrucciones;
  int puntero_datos;
};

#endif /* SRC_INTERPRETADOR_H_ */
