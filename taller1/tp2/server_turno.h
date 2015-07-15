#ifndef SRC_SERVER_TURNO_H_
#define SRC_SERVER_TURNO_H_
#include <iostream>
#include <stdio.h>
#include <list>
#include <string>

struct clienteStruct {
  int id_cliente;
  int cant_comensales;
};

class server_turno {
 public:
  server_turno(int id_turno, const std::string &fecha_hora,
               int disponibilidad);
  server_turno(const std::string &fecha_hora, int disponibilidad);
  virtual ~server_turno();
  // Agrega comensales al cliente de id id, si no existe el cliente lo crea.
  bool agregar_comensales(int id, int cant_comensales);
  // Agrega un cliente nuevo sin descontar la cantidad
  // de comensales de la disponibilidad.
  void agregar_cliente(int id_cliente, int cant_comensales);
  // Borra cliente con sus comensales, actualiza la disponibilidad.
  bool borrar_cliente_y_comensales(int cliente_id);

  // Getters y setters:
  int getDisponibilidad() const;
  void setDisponibilidad(int disponibilidad);
  std::string getFechaHora() const;
  void setFechaHora(std::string fechaHora);
  int getIdTurno() const;
  std::list<clienteStruct> getClientes();
  void setIdTurno(int idTurno);

 private:
  int id_turno;
  std::string fecha_hora;
  int disponibilidad;
  std::list<clienteStruct> clientes;
};

#endif
