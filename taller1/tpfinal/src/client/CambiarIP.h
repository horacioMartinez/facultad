/*
 * CambiarIP.h
 *
 *  Created on: Jul 4, 2015
 *      Author: horacio
 */

#ifndef CAMBIARIP_H_
#define CAMBIARIP_H_

#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <string>

#include "Procesador.h"
#include "Screen.h"

class CambiarIP : public Screen {
 public:
  CambiarIP(Glib::RefPtr<Gtk::Application> app, Procesador* procesador, Screen* padre);
  void show();
  void hide();

 private:
  void on_botonCancelar_clicked();
  void on_botonOK_clicked();
  Gtk::Window* window;
  Gtk::Button* botonOK;
  Gtk::Button* botonCancelar;
  Gtk::Entry* ip;
  Gtk::Entry* puerto;
  Screen* padre;
  Procesador* procesador;
};

#endif /* CAMBIARIP_H_ */
