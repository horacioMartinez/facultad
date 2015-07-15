#include <vector>
#include "Parseador.h"
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

void Parseador::getInstrucciones(char* dirArchivo,
                                 std::vector<Operacion*> &instrucciones) {
  archivo.open(dirArchivo);
  char c;
  bool ignorar = false;
  archivo.get(c);
  while (!archivo.eof()) {
    if (c == '#')
      ignorar = true;
    if ((!ignorar) && (c != ' ') && (c != '\n')) {
      if (c == '+')
        instrucciones.push_back(new Suma);
      else if (c == '<')
        instrucciones.push_back(new Menor);
      else if (c == '>')
        instrucciones.push_back(new Mayor);
      else if (c == '-')
        instrucciones.push_back(new Resta);
      else if (c == ',')
        instrucciones.push_back(new Coma);
      else if (c == '.')
        instrucciones.push_back(new Punto);
      else if (c == '$')
        instrucciones.push_back(new Peso);
      else if (c == '@')
        instrucciones.push_back(new Arroba);
      else if (c == '[')
        instrucciones.push_back(new CorcheteAbierto);
      else if (c == ']')
        instrucciones.push_back(new CorcheteCerrado);
    }
    if (c == '\n')
      ignorar = false;
    archivo.get(c);
  }
  archivo.close();
}
