/*
 * File.h
 *
 *  Created on: 30/05/2015
 *      Author: pablito
 */

#ifndef STOCK_H_
#define STOCK_H_
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "StringUtils.h"
#include <glibmm/datetime.h>
namespace utils {

class Stock {
public:
	Stock();
	~Stock();
	void update(const std::string& idProduct, const std::string& idArea, unsigned int counter, const std::string& date);


	void updateHistoricStock(const std::string& idProduct,const std::string& idArea, unsigned int counter, const std::string& date);
	unsigned int getActual(const std::string& idProduct);
	std::string calcularIntervalo(Glib::DateTime& date);
	std::vector<int> obtenerHistoricoGeneral(const std::string& idProduct, const std::string& desde,const std::string& hasta);
	std::vector<int> obtenerHistorico(const std::string& idProduct, const std::string& desde, const std::string& hasta, std::string archivoResumenAnterior);
	void obtenerStockAreaVision(const std::string& idArea, std::vector<std::string>& idProducts, std::vector<int>& cant);
	std::vector<std::pair<std::string, std::string> > separarDias(const std::string& desde, const std::string& hasta);
	void actualizarStockAreaVision(std::string idProduct, std::string idArea, unsigned int counter);
	bool actualizarStockProducto(const std::string& idProduct, const std::string& idArea, unsigned int counter, const std::string& date);
	void actualizarStockGeneral(const std::string& idProduct, unsigned int counter);
	bool reemplazarLinea(const std::string& pathGeneral, const  std::string& pathAux, const std::string& nuevo, unsigned int pos);
	void obtenerStockGeneral(std::vector< std::string >& idProductos, std::vector< int >& cant);
	void separarArchivosResumen(Glib::DateTime& fecha, std::vector<std::string>& archivosResumenDisponibles,std::vector<std::string>& menores, std::vector<std::string>& mayores);
	bool actualizarResumenDiario(const std::string& resumen , const std::string&  idArea, const std::string& producto, unsigned int counter, const std::string& date);
	bool actualizarArchivoDiario(const std::string& idArea, const std::string& idProducto, unsigned int counter, const std::string& date);	
	private:
	/*Constructor por copia declarado privado pero no definido
	 * no se deben copiar las instancias de "Archivo").
	*/
	Stock(const Stock &file);
	/*
	 * Operador asignacion de copia declarado privado pero no definido
	 * (no se deben copiar las instancias de "Archivo").
	*/
	Stock& operator=(const Stock &File);
	void actualizarResumenesDiarios(const std::string& idProduct, const std::string& idArea, unsigned int counter,const std::string& date);

	std::fstream file;

  
};

} /* namespace utils */
#endif /* STOCK_H_ */
