#include "vista.h"
#include <gtkmm/application.h>
#include "controlador.h"
#include "modelo.h"
int main(int argc, char*  argv[]){
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,"mi.app");
	Vista vista;
	std::string puerto;
	std::getline(std::cin,puerto);
	std::string ip;
	std::getline(std::cin,ip);
	Modelo modelo(puerto,ip);
	Controlador controlador(modelo,vista);
	controlador.iniciar();
	app -> run(vista.obtenerVentanaPrincipal());
}
