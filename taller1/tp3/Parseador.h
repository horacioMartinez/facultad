#ifndef SRC_PARSEADOR_H_
#define SRC_PARSEADOR_H_

#include <vector>
#include <fstream>
#include "Operacion.h"

class Parseador {
 public:
  void getInstrucciones(char* dirArchivo,
                        std::vector<Operacion*> &instrucciones);
 private:
  std::fstream archivo;
};

#endif /* SRC_PARSEADOR_H_ */
