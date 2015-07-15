#ifndef DIALOGO_AGREGAR_AREA_VISION
#define DIALOGO_AGREGAR_AREA_VISION

#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>
#include <iostream>
#include <vector>
#include <string>

class DialogoAgregarAreaVision:public Gtk::Dialog{
	private:
		
		/****** WIDGETS ******/

		Gtk::ComboBoxText* tipoAreaVisionCombo;
		Gtk::Entry* nombreEntry;
		Gtk::Button* aceptarButton;
		Gtk::Button* cancelarButton;

		void conectarSeniales(Glib::RefPtr<Gtk::Builder>& builder);

	public:

		/****** CONSTRUCTOR ******/

		DialogoAgregarAreaVision(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder);

		/****** HANDLERS DE LOS BOTONES ******/

		void cerrar();
		void aceptar();

		/****** GETTERS ******/

		std::string obtenerNombreAreaVision();
		std::string obtenerTipoAreaVision();

		/****** SETTER ******/

		void precargarCampos(std::string areaVision, std::string tipo);
};

#endif
