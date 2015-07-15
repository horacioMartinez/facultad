#ifndef GRAFICO_BARRAS
#define GRAFICO_BARRAS
#include <gtkmm/iconview.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <vector>
#define GBARRAS_COMPARACION 0
#define GBARRAS_HISTORICO 1
#define GBARRAS_LINEAL 2
class GraficoDeBarras{
	private:
		std::vector<std::string> labels;
		std::vector<int> datos;
		int tipo;	
		Gtk::DrawingArea* dibujo;	
		Glib::RefPtr<Gdk::Window> win;
	public:
		void setearTipo(int tipo);
		GraficoDeBarras(Gtk::DrawingArea* dibujo, int tipo);
		void dibujarRectangulo(const Cairo::RefPtr<Cairo::Context>& c,int x, int y, int ancho,int alto);
		bool dibu(const Cairo::RefPtr<Cairo::Context>& contexto);
		bool dibujarLineal(const Cairo::RefPtr<Cairo::Context>& contexto);
		void dibujar();
		void vaciar();
		bool setDatos(std::vector<std::string> labels, std::vector<int> datos);
};
#endif
