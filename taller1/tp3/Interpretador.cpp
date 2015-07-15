#include "Interpretador.h"

#include <iostream>
#include <iterator>
#include <vector>
#include <stack>
#include "Arroba.h"
#include "Coma.h"
#include "CorcheteAbierto.h"
#include "CorcheteCerrado.h"
#include "Mayor.h"
#include "Menor.h"
#include "Peso.h"
#include "Punto.h"
#include "Resta.h"
#include "Suma.h"

Interpretador::Interpretador() {
  n = 0;
  puntero_datos = 0;
}

Interpretador::~Interpretador() {
  for (std::vector<Operacion*>::iterator it = instrucciones.begin();
      it != instrucciones.end(); ++it)
    delete (*it);
}

bool Interpretador::correr(int n, char modo, char* dirArchivo) {
  if ((modo != 'c') && (modo != 'e'))
    return false;
  this->n = n;
  parseador.getInstrucciones(dirArchivo, instrucciones);
  datos = std::vector<signed char>(n, 0);
  if (modo == 'e')
    this->ejecutar();
  if (modo == 'c')
    this->compilar();
  return true;
}

void Interpretador::ejecutar() {
  int pos;
  std::stack<int> pilaPosLoops;
  int ejecutar = 1;
  // casteo a int asi no tira warning de comparacion entre signed y unsigned:
  for (pos = 0; pos < (int) instrucciones.size(); ++pos) {
    (*instrucciones[pos]).operar(puntero_datos, datos, pos, pilaPosLoops,
                                 ejecutar);
  }
}

void Interpretador::compilar() {
  // Codigo de inicializacion:
  std::cout << "#include <iostream>\n#include <vector>\n\n";
  std::cout << "#define N " << n << '\n';
  std::cout << "#define AT(x) ((x) % " << n << ")\n\n";
  std::cout << "int main(int argc, char *argv[]) {\nint dataptr = 0;\n";
  std::cout << "signed char c = 0;\nstd::vector<signed char> data(N, 0);\n";

  //instrucciones:
  for (std::vector<Operacion*>::iterator it = instrucciones.begin();
      it != instrucciones.end(); ++it)
    std::cout << (*(*it)) << '\n';
  std::cout << "return 0;\n}\n";
}
