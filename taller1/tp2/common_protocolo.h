#ifndef SRC_COMMON_PROTOCOLO_H_
#define SRC_COMMON_PROTOCOLO_H_

#include <string>
#include <vector>

class common_protocolo {
 public:
  common_protocolo();
  virtual ~common_protocolo();
  // Convierte el mensaje en tokens y los almacena en vectorMensaje. Si el
  // mensaje contine el caracter de fin de linea al final de este lo remueve,
  // al menos que este sea su unico caracter.
  void tokenizar(std::string mensaje, char delimitador,
                 std::vector<std::string> &vectorMensaje);
  // Concatena todos los strings en el vector vectorMensaje
  // e inserta el caracter de fin de linea.
  std::string concatenar_mensaje(std::vector<std::string> &vectorMensaje);
  // Reemplaza el char 3 por el caracter de fin de linea
  void reemplazar_fin_de_linea(std::string &s);
  // Devuelve true si el string contiene únicamente números.
  bool es_un_numero(const std::string& s);
 private:
  void reemplazar_en_string(std::string& s, const std::string& aReemplazar,
                            const std::string& reemplazo);
};

#endif
