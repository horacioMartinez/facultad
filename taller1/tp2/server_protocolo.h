#ifndef SRC_SERVER_PROTOCOLO_H_
#define SRC_SERVER_PROTOCOLO_H_

#include "common_protocolo.h"
#include "server_turno.h"
#include <fstream>
#include <list>
#include <string>

class server_protocolo : public common_protocolo {
 public:
  server_protocolo();
  virtual ~server_protocolo();
  void cargar_parametros(int argc, char* argv[], std::string &puerto);
  // Lee el archivo de entrada y a partir de el obtiene el listado de turnos
  // y los guarda en la lista pasada como parametro.
  void obtener_turnos_archivo(std::list<server_turno>& turnos);
  // Guarda los turnos en el archivo de salida.
  void escribir_turnos_archivo(std::list<server_turno>& turnos);
  // Devuelve un string con los listados de turnos.
  std::string obtener_listado_de_turnos(std::list<server_turno> &turnos);
  // Devuelve un string con los listados de reservas.
  std::string obtener_listado_de_reservas(int id_cliente,
                                          std::list<server_turno> &turnos);
  std::string obtener_mensaje_error();
  std::string obtener_mensaje_ok();
 private:
  std::fstream archivo;
  char* dirArchivo;
};

#endif
