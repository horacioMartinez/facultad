all: vistaIconos.o areaVisionBox.o generalBox.o productoBox.o graficoDeBarras.o graficoDeTorta.o modelo.o dialogoAgregarProducto.o dialogoAgregarAreaVision.o controlador.o selectorFecha.o vista.o
	 g++ -std=c++98 *.o main.cpp ../common/*.cpp -o admin `pkg-config gtkmm-3.0 --cflags --libs` -g

vistaIconos.o:
	 $(OK_COLOR)g++ -std=c++98 vistaIconos.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g $(NO_COLOR)
areaVisionBox.o:
	 g++ -std=c++98 areaVisionBox.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
generalBox.o:
	 g++ -std=c++98 generalBox.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
productoBox.o:
	 g++ -std=c++98 productoBox.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
graficoDeBarras.o: 
	g++ -std=c++98 graficoDeBarras.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
graficoDeTorta.o:
	g++ -std=c++98 graficoDeTorta.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
modelo.o: 
	g++ -std=c++98 modelo.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
dialogoAgregarProducto.o: 
	g++ -std=c++98 dialogoAgregarProducto.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
dialogoAgregarAreaVision.o:
	 g++ -std=c++98 dialogoAgregarAreaVision.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
controlador.o:	 
	g++ -std=c++98 controlador.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
selectorFecha.o:
	g++ -std=c++98 selectorFecha.cpp -c `pkg-config gtkmm-3.0 --cflags --libs` -g
vista.o: 
	 g++ -std=c++98 vista.cpp -c  `pkg-config gtkmm-3.0 --cflags --libs` -g
