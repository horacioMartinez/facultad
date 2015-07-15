#ifndef DIALOGO_AGREGAR_PRODUCTO
#define DIALOGO_AGREGAR_PRODUCTO

#include <gtkmm/listviewtext.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>
#include <gtkmm/image.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/messagedialog.h>
#include <iostream>
#include <vector>
#include <string>

class DialogoAgregarProducto:public Gtk::Dialog{
	private:

		/****** MODELO DEL LISTADO DE IMÁGENES ******/

		Gtk::ListViewText listaImagenes;
		Glib::RefPtr<Gtk::TreeSelection> selection;
		Gtk::TreeModelColumnRecord mCol;
		Glib::RefPtr<Gtk::ListStore> lista;
		int nImagenes;

		/****** WIDGETS ******/

		Gtk::Image* imagen;
		Gtk::Entry* nombreEntry;
		Gtk::TextView* descripcionText;
		Gtk::FileChooserButton* iconoFile;
		Gtk::ScrolledWindow* scrolled;
		Gtk::Image* icono;

		void conectarSeniales(Glib::RefPtr<Gtk::Builder>& builder);



	public:
	
		/****** CONSTRUCTOR ******/

		DialogoAgregarProducto(BaseObjectType* cobject,Glib::RefPtr<Gtk::Builder>& builder);

		/****** MOSTRAR LAS IMÁGENES Y EL ÍCONO ******/

		void mostrarIcono();
		void mostrarImagen();

		/****** IMÁGENES DEL PRODUCTO ******/

		void agregarImagen();
		void eliminarImagen();
		void modificarImagen();

		/****** HANDLERS DE LOS BOTONES ******/

		void cerrar();
		void aceptar();

		/****** GETTERS ******/
		
		std::string obtenerNombreProducto();
		std::string obtenerDescripcionProducto();
		std::string obtenerIcono();
		std::vector<std::string> obtenerImagenes();	
		
		/****** SETTER ******/

		void precargarCampos(std::string producto, std::string descripcion, std::string icono, std::vector<std::string> imagenes);
};

#endif
