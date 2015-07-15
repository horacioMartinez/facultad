#include "server_protocolo.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

using std::string;

server_protocolo::server_protocolo() {
  dirArchivo = NULL;
}

server_protocolo::~server_protocolo() {
}

void server_protocolo::cargar_parametros(int argc, char* argv[],
                                         std::string &puerto) {
  if (argc != 3) {
    std::cerr << "Parametros incorrectos";
    return;
  }
  puerto = argv[1];
  this->dirArchivo = argv[2];
  archivo.open(argv[2]);
}

void server_protocolo::obtener_turnos_archivo(std::list<server_turno>& turnos) {
  string line;
  string delimitador = "|";
  while (getline(archivo, line)) {
    if (line.empty())
      continue;

    string fecha_hora = line.substr(0, line.find(delimitador));
    line.erase(0, line.find(delimitador) + delimitador.length());

    string disponibilidad = line.substr(0, line.find(delimitador));
    line.erase(0, line.find(delimitador) + delimitador.length());

    server_turno nuevo_turno(fecha_hora, atoi(disponibilidad.c_str()));

    if (line.length() > 0)
      line.erase(0, 1);

    while (line.length() > 0 && line.find(delimitador) != line.npos) {
      string id_cliente = line.substr(0, line.find(delimitador));
      line.erase(0, line.find(delimitador) + delimitador.length());
      string cant_comensales = line.substr(0, line.find(delimitador));
      line.erase(0, line.find(delimitador) + delimitador.length());
      nuevo_turno.agregar_cliente(atoi(id_cliente.c_str()),
                                  atoi(cant_comensales.c_str()));
    }
    turnos.push_back(nuevo_turno);
  }
  archivo.close();
}

void server_protocolo::escribir_turnos_archivo(
    std::list<server_turno>& turnos) {
  archivo.open(dirArchivo, std::fstream::out | std::fstream::trunc);
  std::stringstream buffer;
  std::list<server_turno>::iterator turnoIt;
  std::list<clienteStruct> clientes;
  std::list<clienteStruct>::iterator clienteIt;
  for (turnoIt = turnos.begin(); turnoIt != turnos.end(); ++turnoIt) {
    buffer << turnoIt->getFechaHora() << "|" << turnoIt->getDisponibilidad()
           << "|";
    clientes = turnoIt->getClientes();
    for (clienteIt = clientes.begin(); clienteIt != clientes.end();
        ++clienteIt) {
      buffer << "|" << clienteIt->id_cliente << "|"
             << clienteIt->cant_comensales;
    }
    buffer << "\n";
  }
  archivo << buffer.rdbuf();
  archivo.close();
}

string server_protocolo::obtener_listado_de_turnos(
    std::list<server_turno> &turnos) {
  char finDeLinea = 3;
  std::stringstream buffer;
  std::list<server_turno>::iterator it;
  std::list<clienteStruct> clientes;
  std::list<clienteStruct>::iterator clienteIt;
  for (it = turnos.begin(); it != turnos.end(); ++it) {
    buffer << std::setfill('0') << std::setw(4) << it->getIdTurno();
    buffer << "\t" << it->getFechaHora() << "\t" << "("
           << it->getDisponibilidad() << ")";
    if (!(it == (--turnos.end())))
      buffer << finDeLinea;
  }
  buffer << "\n";
  return buffer.str();
}

string server_protocolo::obtener_listado_de_reservas(
    int id_cliente, std::list<server_turno> &turnos) {
  char finDeLinea = 3;
  bool primero = true;
  std::stringstream buffer;
  std::list<server_turno>::iterator turnoIt;
  std::list<clienteStruct> clientes;
  std::list<clienteStruct>::iterator clienteIt;
  for (turnoIt = turnos.begin(); turnoIt != turnos.end(); ++turnoIt) {
    clientes = turnoIt->getClientes();
    for (clienteIt = clientes.begin(); clienteIt != clientes.end();
        ++clienteIt) {
      if (clienteIt->id_cliente == id_cliente) {
        if (primero)
          primero = false;
        else
          buffer << finDeLinea;
        buffer << clienteIt->id_cliente << "\t";
        buffer << std::setfill('0') << std::setw(4) << turnoIt->getIdTurno();
        buffer << "\t" << turnoIt->getFechaHora() << "\t"
               << clienteIt->cant_comensales;
      }
    }
  }

  if (buffer.str().empty())
    return this->obtener_mensaje_error();
  buffer << "\n";
  return buffer.str();
}

string server_protocolo::obtener_mensaje_error() {
  string res = "error\n";
  return res;
}

string server_protocolo::obtener_mensaje_ok() {
  string res = "ok\n";
  return res;
}
