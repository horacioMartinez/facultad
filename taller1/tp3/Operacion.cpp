#include "Operacion.h"
#include <string>

Operacion::~Operacion() {
}

std::ostream &operator<<(std::ostream &salida, Operacion &operacion) {
  salida << operacion.getCodigo();
  return salida;
}
