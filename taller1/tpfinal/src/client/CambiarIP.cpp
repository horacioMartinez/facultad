/*
 * CambiarIP.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: horacio
 */

#include "CambiarIP.h"
#include <glibmm/signalproxy.h>
#include <gtkmm/builder.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>

CambiarIP::CambiarIP(Glib::RefPtr<Gtk::Application> app, Procesador* procesador, Screen* padre) {
  this->app = app;
  this->padre = padre;
  this->procesador = procesador;
  refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("./ui/glade/cambiarIP.glade");
  refBuilder->get_widget("window1", window);
  refBuilder->get_widget("button1", botonOK);
  refBuilder->get_widget("button2", botonCancelar);
  refBuilder->get_widget("entry1", ip);
  refBuilder->get_widget("entry2", puerto);
  botonOK->signal_clicked().connect(
      sigc::mem_fun(*this, &CambiarIP::on_botonOK_clicked));
  botonCancelar->signal_clicked().connect(
        sigc::mem_fun(*this, &CambiarIP::on_botonCancelar_clicked));
}

void CambiarIP::on_botonOK_clicked() {
  if (ip->get_text().empty() || puerto->get_text().empty())
    return;
  std::string nuevaIP = this->ip->get_text();
  std::string nuevoPuerto = this->puerto->get_text();
  std::cout << nuevaIP << "  " << nuevoPuerto << std::endl;
  procesador->cambiarConexion(nuevaIP,nuevoPuerto);
  padre->show();
  this->hide();
}

void CambiarIP::on_botonCancelar_clicked() {
  padre->show();
  this->hide();
}

void CambiarIP::show() {
  app->add_window(*window);
  window->show();
}

void CambiarIP::hide() {
  window->hide();
  app->remove_window(*window);
}

