#include "server_turno.h"
#include <string>
#include <list>

server_turno::server_turno(int id_turno, const std::string &fecha_hora,
                           int disponibilidad) {
  this->id_turno = id_turno;
  this->fecha_hora = fecha_hora;
  this->disponibilidad = disponibilidad;
}

server_turno::server_turno(const std::string &fecha_hora, int disponibilidad) {
  this->id_turno = 0;
  this->fecha_hora = fecha_hora;
  this->disponibilidad = disponibilidad;
}

server_turno::~server_turno() {
}

bool server_turno::agregar_comensales(int id_cliente, int cant_comensales) {
  std::list<clienteStruct>::iterator it;
  if (this->disponibilidad < cant_comensales)
    return false;
  this->disponibilidad = this->disponibilidad - cant_comensales;
  for (it = clientes.begin(); it != clientes.end(); ++it)
    if (it->id_cliente == id_cliente) {
      it->cant_comensales = it->cant_comensales + cant_comensales;
      return true;
    }
  this->agregar_cliente(id_cliente, cant_comensales);
  return true;
}

void server_turno::agregar_cliente(int id_cliente, int cant_comensales) {
  clienteStruct nuevo_cliente;
  nuevo_cliente.id_cliente = id_cliente;
  nuevo_cliente.cant_comensales = cant_comensales;
  clientes.push_back(nuevo_cliente);
}

bool server_turno::borrar_cliente_y_comensales(int cliente_id) {
  std::list<clienteStruct>::iterator it;
  bool res = false;
  for (it = clientes.begin(); it != clientes.end();) {
    if (it->id_cliente == cliente_id) {
      this->disponibilidad = this->disponibilidad + it->cant_comensales;
      it = clientes.erase(it);
      res = true;
    } else {
      ++it;
    }
  }
  return res;
}

// Getters  y setters:

int server_turno::getDisponibilidad() const {
  return disponibilidad;
}

void server_turno::setDisponibilidad(int disponibilidad) {
  this->disponibilidad = disponibilidad;
}

std::string server_turno::getFechaHora() const {
  return fecha_hora;
}

void server_turno::setFechaHora(std::string fechaHora) {
  fecha_hora = fechaHora;
}

int server_turno::getIdTurno() const {
  return id_turno;
}

std::list<clienteStruct> server_turno::getClientes() {
  return clientes;
}

void server_turno::setIdTurno(int idTurno) {
  id_turno = idTurno;
}
