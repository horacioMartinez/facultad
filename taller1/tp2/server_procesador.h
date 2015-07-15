#ifndef SRC_SERVER_PROCESADOR_H_
#define SRC_SERVER_PROCESADOR_H_
#include "server_protocolo.h"
#include "server_turno.h"
#include <string>
#include <list>
#include <vector>

class server_procesador {
 public:
  server_procesador();
  virtual ~server_procesador();
  // A partir de los datos de entrada obtiene el puerto y el archivo.
  void cargar_datos_entrada(int argc, char* argv[], std::string &puerto);
  // Calcula nuevo id para ser asignado a un turno.
  int calcular_nuevo_turno_id(std::list<server_turno> &turnos, int offset);
  // Procesa la peticion y devuelve el resultado.
  std::string procesar_peticion(const std::string &peticion);
  // Realiza una reserva con los datos indicados,
  // de no ser posible devuelve false.
  bool reservar(int id_cliente, int id_item_sesion, int cant_comensales);
  // Cancela la reserva indicada, de no encontrarla devuelve false.
  bool cancelar_reserva(int id_cliente, int id_item_sesion);
  void apagar();

 private:
  bool peticion_valida(const std::vector<std::string> &vectorPeticion);
  std::list<server_turno> turnos;
  server_protocolo protocolo;
};

#endif
