#include "common_protocolo.h"
#include <vector>
#include <sstream>
#include <string>

common_protocolo::common_protocolo() {
}

common_protocolo::~common_protocolo() {
}

void common_protocolo::tokenizar(std::string mensaje, char delimitador,
                                 std::vector<std::string> &vectorMensaje) {
  // remover '\n' del final del mensaje si es que lo tiene
  // y no es el unico caracter:
  if (!mensaje.empty() && mensaje[mensaje.length() - 1] == '\n'
      && mensaje.size() > 1) {
    mensaje.erase(mensaje.length() - 1);
  }
  std::stringstream stream(mensaje);
  std::string token;
  while (std::getline(stream, token, delimitador)) {
    vectorMensaje.push_back(token);
  }
}

std::string common_protocolo::concatenar_mensaje(
    std::vector<std::string> &vectorMensaje) {
  std::stringstream buffer;
  std::string mensajeConcatenado;
  std::vector<std::string>::iterator it;
  std::vector<std::string>::iterator final_iter = vectorMensaje.end();
  --final_iter;
  for (it = vectorMensaje.begin(); it != vectorMensaje.end(); ++it) {
    if (it != final_iter)
      buffer << *it << "|";
    else
      buffer << *it;
  }
  buffer << '\n';
  return buffer.str();
}

void common_protocolo::reemplazar_en_string(std::string& s,
                                            const std::string& aReemplazar,
                                            const std::string& reemplazo) {
  size_t pos = 0;
  while ((pos = s.find(aReemplazar, pos)) != std::string::npos) {
    s.replace(pos, aReemplazar.length(), reemplazo);
    pos += reemplazo.length();
  }
}

void common_protocolo::reemplazar_fin_de_linea(std::string &s) {
  char finDeLinea = 3;
  std::string reemplazo = "\n";
  std::string aReemplazar = "";
  aReemplazar += finDeLinea;
  this->reemplazar_en_string(s, aReemplazar, reemplazo);
}

bool common_protocolo::es_un_numero(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return (!s.empty() && it == s.end());
}
