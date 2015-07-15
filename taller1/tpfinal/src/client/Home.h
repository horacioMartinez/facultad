/*
 * Home.h
 *
 *  Created on: May 29, 2015
 *      Author: horacio
 */

#ifndef TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_HOME_H_
#define TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_HOME_H_

#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include "Screen.h"
#include "Enviados.h"
#include "Enviar.h"
#include "GenerarVideo.h"
#include "CambiarIP.h"

class Home : public Screen {
 public:
  Home(Glib::RefPtr < Gtk::Application > app);
  virtual ~Home();
  void ejecutar();
  void show();
  void hide();

 private:
  void cargarImagenes();
  void on_botonEnviar_clicked();
  void on_botonEnviados_clicked();
  void on_botonConvertir_clicked();
  void on_botonCambiarIP_clicked();
  Procesador* procesador;
  Enviar* enviar;
  Enviados* enviados;
  GenerarVideo* generarVideo;
  CambiarIP* cambiarIP;
  Gtk::Window* window;
  Gtk::Button* botonEnviar;
  Gtk::Button* botonEnviados;
  Gtk::Button* botonConvertir;
  Gtk::Button* botonCambiarIP;
};

#endif /* TPFINALTALLER_CLIENTE_CLIENT_UI_SCREENS_HOME_H_ */
