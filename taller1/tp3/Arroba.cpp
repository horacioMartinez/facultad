#include "Arroba.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

void Arroba::operar(int &puntero_datos, std::vector<signed char> &datos,
                    int &pos, std::stack<int> &pilaPosLoops, int &ejecutar) {
  if (ejecutar == 1) {
    std::cerr << "PI " << std::hex << std::uppercase << std::setfill('0')
              << std::setw(8) << pos << '\n';
    std::cerr << "PD " << std::hex << std::setfill('0') << std::setw(8)
              << (puntero_datos % datos.size()) << '\n';
    std::cerr << "Data\n";
    for (std::vector<signed char>::iterator it = datos.begin();
        it != datos.end(); ++it) {
      int i = (*it);
      std::cerr << std::setfill('0') << std::setw(2) << i;
      if (it != --datos.end())
        std::cerr << " ";
    }
    std::cerr << '\n';
    ejecutar--;
  }
}

const char* Arroba::getCodigo() {
  return "return 0;";
}
