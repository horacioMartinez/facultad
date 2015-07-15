#include "server_procesador.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <string>

server_procesador::server_procesador() {
}

server_procesador::~server_procesador() {
}

void server_procesador::cargar_datos_entrada(int argc, char* argv[],
                                             std::string &puerto) {
  protocolo.cargar_parametros(argc, argv, puerto);
  protocolo.obtener_turnos_archivo(turnos);
  int i = 1;
  std::list<server_turno>::iterator it;
  for (it = turnos.begin(); it != turnos.end(); ++it) {
    it->setIdTurno(i);
    i++;
  }
}

int server_procesador::calcular_nuevo_turno_id(std::list<server_turno> &turnos,
                                               int offset) {
  int id = turnos.size() + 1;
  bool duplicado = false;

  std::list<server_turno>::iterator turnosIt;
  for (turnosIt = turnos.begin(); turnosIt != turnos.end(); ++turnosIt)
    if (turnosIt->getIdTurno() == (id + offset))
      duplicado = true;
  if (duplicado)
    return this->calcular_nuevo_turno_id(turnos, offset + 1);
  else
    return id + offset;
}

std::string server_procesador::procesar_peticion(const std::string &peticion) {
  using std::string;
  std::vector<string> vectorPeticion;
  protocolo.tokenizar(peticion,'|',vectorPeticion);

  if (!this->peticion_valida(vectorPeticion))
    return protocolo.obtener_mensaje_error();
  string comando = vectorPeticion[0];

  if (comando.compare("L") == 0)
    return protocolo.obtener_listado_de_turnos(turnos);

  if (comando.compare(string("R")) == 0) {
    if (this->reservar(atoi(vectorPeticion[1].c_str()),
                       atoi(vectorPeticion[2].c_str()),
                       atoi(vectorPeticion[3].c_str())))
      return protocolo.obtener_mensaje_ok();
    else
      return protocolo.obtener_mensaje_error();
  }

  if (comando.compare("C") == 0) {
    return protocolo.obtener_listado_de_reservas(
        atoi(vectorPeticion[1].c_str()), turnos);
  }

  if (comando.compare("B") == 0) {
    if (this->cancelar_reserva(atoi(vectorPeticion[1].c_str()),
                               atoi(vectorPeticion[2].c_str())))
      return protocolo.obtener_mensaje_ok();
    else
      return protocolo.obtener_mensaje_error();
  }
  return protocolo.obtener_mensaje_error();
}

bool server_procesador::peticion_valida(
    const std::vector<std::string> &vectorPeticion) {
  if (vectorPeticion.size() == 1) {
    if (vectorPeticion[0].compare("L") == 0)
      return true;
    return false;
  }
  if (vectorPeticion.size() == 2) {
    if (vectorPeticion[0].compare("C") == 0)
      if (protocolo.es_un_numero(vectorPeticion[1]))
        return true;
    return false;
  }
  if (vectorPeticion.size() == 3) {
    if (vectorPeticion[0].compare("B") == 0)
      if (protocolo.es_un_numero(vectorPeticion[1])
          && protocolo.es_un_numero(vectorPeticion[2]))
        return true;
    return false;
  }
  if (vectorPeticion.size() == 4) {
    if (vectorPeticion[0].compare("R") == 0)
      if (protocolo.es_un_numero(vectorPeticion[1])
          && protocolo.es_un_numero(vectorPeticion[2])
          && protocolo.es_un_numero(vectorPeticion[3]))
        return true;
    return false;
  }
  return false;
}

bool server_procesador::reservar(int id_cliente, int id_item_sesion,
                                 int cant_comensales) {
  std::list<server_turno>::iterator it;
  for (it = turnos.begin(); it != turnos.end(); ++it)
    if (it->getIdTurno() == id_item_sesion) {
      return it->agregar_comensales(id_cliente, cant_comensales);
    }
  return false;
}

bool server_procesador::cancelar_reserva(int id_cliente, int id_item_sesion) {
  std::list<server_turno>::iterator it;
  for (it = turnos.begin(); it != turnos.end(); ++it)
    if (it->getIdTurno() == id_item_sesion) {
      return it->borrar_cliente_y_comensales(id_cliente);
    }
  return false;
}

void server_procesador::apagar() {
  protocolo.escribir_turnos_archivo(turnos);
}
