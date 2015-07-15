#include "Stock.h"
#include <cstdlib>
#include <map>
#include <iterator>
#include <glibmm/datetime.h>
#include <glibmm/date.h>
#include "StringUtils.h"
#include "Directory.h"
#include <algorithm>

namespace utils {

Stock::Stock(){
}

Stock::~Stock() {
}

void Stock::update(const std::string& idProduct, const std::string& idArea,unsigned int counter, const std::string& date) {
	/* Actualiza los archivos de stock histórico, de stock de producto y de área de visión, de stock general y resúmenes diarios. */
	actualizarStockProducto(idProduct,idArea,counter,date);
	updateHistoricStock(idProduct,idArea,counter,date);
}

std::string Stock::calcularIntervalo(Glib::DateTime& hora){
	/*Recibe una hora y devuelve el intervalo (de duracion 30 minutos, entre hh:00 y hh:29 o entre hh:30 y hh:59) en el que se encuentra el formato de string.*/
	int hh = hora.get_hour();
	int mm = hora.get_minute();
	utils::StringUtils util;
	std::string s = "0";
	if(mm < 30) {
		return util.fillFront(s,util.toString(hh),2) + "30";
	}
	return util.fillFront(s,util.toString(hh + 1),2) + "00";
}

Glib::DateTime nombreArchivoADate(const std::string& nombre){
	/* Recibe el nombre de un archivo de la forma dd_mm_aa y devuelve un Glib::DateTime con esa fecha */
	Glib::DateTime fechaAux;
	std::string strFechaAux;
	std::vector< std::string > vecFechaAux;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(nombre,vecFechaAux,'_');
	std::string cero = "0";
	strFechaAux = util.fillFront(cero,vecFechaAux[0],2) + "/" + util.fillFront(cero,vecFechaAux[1],2) + "/" + vecFechaAux[2] + "-00:00";
	return util.stringToDate(strFechaAux);
}

std::string dateANombreArchivo(const Glib::DateTime& date){
	/* Recibe una fecha tipo Glib::DateTime y devuelve un nombre de archivo para esa fecha, con el formato dd_mm_aa.csv */
	utils::StringUtils util;
	std::string dia = util.toString(date.get_day_of_month());
	std::string mes = util.toString(date.get_month());
	std::string anio = util.toString(date.get_year());
	return dia + "_" + mes + "_" + anio + ".csv";
}

void extraerNombreArchivo(std::string& fullPath){
	/* Recibe el path completo de un archivo (incluyendo directorios), y remueve los directorios, dejando sólo el nombre del archivo */
	utils::StringUtils util;
	std::vector<std::string> vectorAuxiliar;
	util.tokenizarMensajeConChar(fullPath,vectorAuxiliar,'/');
	fullPath = vectorAuxiliar.back();
}

void copiarArchivo(const std::string& pathIn,const std::string& pathOut){
	/* Copia el archivo pathIn en el archivo pathOut */
	std::ifstream input( pathIn.c_str() );
	if( input.is_open() ) {
		std::ofstream output( pathOut.c_str() );
		std::string temp;
		while( std::getline(input,temp) ) {
			output << temp << std::endl;
		}
	}
}

void Stock::updateHistoricStock(const std::string& idProduct,const std::string& idArea, unsigned int counter, const std::string& date){
	/* Actualiza los archivos de stock histórico dada un nuevo registro de stock para un area y un producto para una cierta fecha y hora*/
	actualizarResumenesDiarios(idProduct,idArea,counter,date);
	actualizarArchivoDiario(idProduct,idArea,counter,date);
}

bool Stock::actualizarArchivoDiario(const std::string& idProducto, const std::string& idArea, unsigned int counter, const std::string& date){
	/* Actualiza el archivo de stock diario con el nuevo registro para un area y un producto para una cierta fecha y hora */
	utils::StringUtils util;
	Glib::DateTime fecha = util.stringToDate(date);
	std::string intervalo = calcularIntervalo(fecha);
	std::string cero = "0";
	std::string hh = util.fillFront(cero,util.toString( fecha.get_hour() ),2);
	std::string mm = util.fillFront(cero,util.toString( fecha.get_minute() ),2);
	int dia, mes, anio;
	fecha.get_ymd(anio,mes,dia);
	std::ifstream stock;
	std::string f = "data/Historic/" + dateANombreArchivo(fecha);
	stock.open( f.c_str() );
	bool found = false;
	std::ofstream aux;
	std::string a = "data/Historic/aux.csv";
	aux.open( a.c_str() );
	int interEntry, interDato;
	interDato = std::atoi( intervalo.c_str() );
	std::string newEntry = intervalo + "," + hh + ":" + mm + "," + idArea + "," + idProducto + "," + util.toString(counter) + "\n";
	if( stock.is_open() ) {
		std::string stockEntry;
		while( std::getline(stock,stockEntry) ) {
			std::vector<std::string> toka;
			util.tokenizarMensajeConChar(stockEntry,toka,',');
			std::string entryInterv = toka[0];
			std::string entryTime = toka[1];
			std::string entryArea = toka[2];
			std::string entryIdProd = toka[3];

			interEntry = std::atoi( entryInterv.c_str() );
			std::vector<std::string> auxiliar;
			util.tokenizarMensajeConChar(entryTime,auxiliar,':');
			if(interEntry < interDato) {
				/*Todos los que están en un intervalo anterior, los copio tal cual.*/
				aux << stockEntry << "\n";
			} else if(interEntry == interDato) {
				if(idArea == entryArea) {
					if(idProducto == entryIdProd) {
						Glib::DateTime time ( Glib::DateTime::create_utc(anio,mes,dia,std::atoi( auxiliar[0].c_str() ),std::atoi( auxiliar[1].c_str() ),0) );
						if(fecha.compare(time) == 1) {

							aux << newEntry;
						}else{
							aux << stockEntry << "\n";
						}
						found = true;
					}
					else{
						aux << stockEntry << "\n";
					}
				}else{
					aux << stockEntry << "\n";
				}
			} else if(interEntry > interDato) {
				if(!found) {
					/*Si el intervalo es mayor, pero todavía no lo encontré, lo pongo en el medio.*/
					found = true;
					aux << newEntry;
					aux << stockEntry << std::endl;
				} else {
					/*Si ya lo había agregado, sigo con la copia.*/
					aux << stockEntry << std::endl;
				}
			}
		}
		stock.close();
	}

	if(!found) aux << newEntry;  /*Si el archivo estaba vacio, lo agrego*/
	aux.close();
	::remove( f.c_str() );
	::rename( a.c_str(),f.c_str() );
	return true;
}

void Stock::actualizarResumenesDiarios(const std::string& idProduct,const std::string& idArea, unsigned int counter, const std::string& date){
	/* Dado un nuevo registro de stock, actualiza los archivos de resúmenes diarios para las fechas posteriores a date, si es necesario. */
	utils::StringUtils util;
	Glib::DateTime fechaYHora = util.stringToDate(date);
	std::string nombreArchivo = dateANombreArchivo(fechaYHora);
	std::string pathResumenes = "data/Historic/Summaries";
	std::string nombreArchivoResumenDiario = pathResumenes + "/" + nombreArchivo;
	std::vector<std::string> archivosFechasMayores;
	std::vector<std::string> archivosFechasMenores;
	std::ifstream archivoResumenDiario;
	utils::Directory dir (pathResumenes);

	std::vector<std::string> archivosResumenDisponibles = dir.getFileNames();

	std::for_each(archivosResumenDisponibles.begin(),archivosResumenDisponibles.end(),extraerNombreArchivo);

	separarArchivosResumen(fechaYHora,archivosResumenDisponibles,archivosFechasMenores, archivosFechasMayores);
	archivoResumenDiario.open( nombreArchivoResumenDiario.c_str() );

	if( !archivoResumenDiario.is_open() ) {

		if(archivosFechasMenores.size() != 0) {
			std::string archivoMasNuevo = pathResumenes + "/" + archivosFechasMenores.back();
			copiarArchivo(archivoMasNuevo,nombreArchivoResumenDiario);
		}
		extraerNombreArchivo(nombreArchivoResumenDiario);
		archivosFechasMayores.push_back(nombreArchivoResumenDiario);
	}else archivoResumenDiario.close();

	for(size_t i = 0; i < archivosFechasMayores.size(); i++) {
		if( !actualizarResumenDiario(pathResumenes + "/" + archivosFechasMayores[i],idArea,idProduct,counter,date) ) break;

	}

}

bool Stock::actualizarResumenDiario(const std::string& resumen, const std::string&  idArea, const std::string& producto, unsigned int counter, const std::string& date){
	/* Actualiza el archivo de resumen dado por el primer parámetro, con los datos del nuevo registro de stock */

	std::ifstream resumenFile( resumen.c_str() );
	std::string line;
	utils::StringUtils util;
	std::string entryDate;
	std::string entryIdArea;
	std::string entryIdProduct;
	std::string stockEntry;
	Glib::DateTime mDate = util.stringToDate(date);
	Glib::DateTime nDate;
	std::ofstream newResumen ("data/Historic/summaryaux.csv");
	std::string entryCant;
	bool nuevo = false;
	bool found = false;
	if( resumenFile.is_open() ) {
		while( std::getline(resumenFile,stockEntry) ) {
			std::vector<std::string> v;
			util.tokenizarMensajeConChar(stockEntry,v,',');
			entryDate = v[1];
			entryIdArea = v[0];
			entryIdProduct = v[2];
			//Ya hay una entrada de esa área de visión, hay que actualizarla si date es más nueva que entryDate;
			if(entryIdArea == idArea) {
				nDate = util.stringToDate(entryDate);
				if(entryIdProduct == producto) {
					if(mDate.compare(nDate) == 1) {

						newResumen << idArea + "," + date + "," + producto + "," + util.toString(counter) + "\n";
						nuevo = true;
					}
					else{
						newResumen << stockEntry << "\n";
					}
					found = true;
				}else{
					newResumen << stockEntry << "\n";
				}
			}else{
				newResumen << stockEntry << "\n";
			}
		}
		resumenFile.close();
	}
	if(!found) {

		newResumen << idArea + "," + date + "," + producto + "," + util.toString(counter) + "\n";
		nuevo = true;
	}
	newResumen.close();
	::remove( resumen.c_str() );

	::rename( "data/Historic/summaryaux.csv",resumen.c_str() );
	return nuevo;
}

bool comparaFechas(const Glib::DateTime& date1, const Glib::DateTime& date2){
	/* Compara dos Glib::DateTime devuelve 1 si la segunda fecha es > a la primera. */
	
	return date2.compare(date1) == 1;
}

void Stock::separarArchivosResumen(Glib::DateTime& fechaYHora,std::vector<std::string>& archivosResumenDisponibles, std::vector<std::string>& archivosFechasMenores, std::vector<std::string>& archivosFechasMayores){
	
	/* Recibe un listado de nombres de archivos con el formato dd_mm_aa, y una fecha. En los otros dos vectores, guarda los archivos con fecha anterior y posterior a la dada por separado.*/
	
	utils::StringUtils util;
	Glib::DateTime fechaMax ( Glib::DateTime::create_utc(1,1,1,0,0,0) );
	Glib::DateTime fechaAux;
	std::vector<Glib::DateTime> fechasMenores;
	std::vector<Glib::DateTime> fechasMayores;
	Glib::DateTime sinMinutos = fechaYHora;
	sinMinutos = sinMinutos.add_minutes( -sinMinutos.get_minute() );
	sinMinutos = sinMinutos.add_hours( -sinMinutos.get_hour() );

	for(unsigned int i = 0; i < archivosResumenDisponibles.size(); i++) {
		fechaAux = nombreArchivoADate(archivosResumenDisponibles[i]);
		if(fechaAux.compare(sinMinutos) == -1) {
			fechasMenores.push_back(fechaAux);
		}else {
			fechasMayores.push_back(fechaAux);
		}
	}

	std::sort(fechasMenores.begin(),fechasMenores.end(),comparaFechas);
	std::sort(fechasMayores.begin(),fechasMayores.end(),comparaFechas);

	for(unsigned int i = 0; i < fechasMenores.size(); i++) {
		archivosFechasMenores.push_back( dateANombreArchivo(fechasMenores[i]) );
	}

	for(unsigned int i = 0; i < fechasMayores.size(); i++) {
		archivosFechasMayores.push_back( dateANombreArchivo(fechasMayores[i]) );
	}

}

bool Stock::reemplazarLinea(const std::string& in, const std::string& out, const std::string& newLine, unsigned int pos){
	/*Recibe el path de un archivo de entrada, un archivo de salida, una linea en formato csv del mismo formato que el
	 * archivo de entrada, y una posicion dentro de la entrada csv con la cual se hace la comparacion. Luego copia el 
	 * archivo de entrada en el de salida, modificando la línea en la que coinciden en la posición pos por newLine.*/

	std::ifstream inFile( in.c_str() );
	std::ofstream outFile( out.c_str() );
	std::string line;
	std::vector<std::string> lineTok;
	std::vector<std::string> newLineTok;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(newLine,newLineTok,',');
	if(newLineTok.size() - 1 < pos) return false;
	bool found = false;

	if( inFile.is_open() && outFile.is_open() ) {
		while( std::getline(inFile,line) ) {

			lineTok.clear();
			util.tokenizarMensajeConChar(line,lineTok,',');

			if( lineTok.size() != newLineTok.size() ) return false;
			if(!found && lineTok[pos] == newLineTok[pos]) {

				outFile << newLine << std::endl;
				found = true;
			} else {

				outFile << line << std::endl;
			}

		}
	}
	if(!found) {

		outFile << newLine << std::endl;

	}
	return true;
}

void Stock::actualizarStockGeneral(const std::string& idProduct, unsigned int counter){
	/* Actualiza el archivo de stock general con un producto y una cantidad para el mismo. */
	
	std::string pathGeneral = "data/gral.csv";
	std::string pathAux = "data/auxGral.csv";
	utils::StringUtils util;
	std::string nuevo = idProduct + "," + util.toString(counter);

	if( reemplazarLinea(pathGeneral,pathAux,nuevo,0) ) {
		std::ifstream aux ( pathGeneral.c_str() );
		if( aux.is_open() ) {
			aux.close();
			::remove( pathGeneral.c_str() );
		}
		::rename( pathAux.c_str(),pathGeneral.c_str() );
	}
}

bool Stock::actualizarStockProducto(const std::string& idProduct, const std::string& idArea, unsigned int counter, const std::string& date ){
	/* Actualiza el archivo de stock del producto, si la fecha dada es más nueva que la de la última entrada para la misma área de visión. */
	
	std::ifstream stock;
	std::string f = "data/Products/" + idProduct +"/"+"stock.csv";
	stock.open( f.c_str() );
	utils::StringUtils util;
	Glib::DateTime mdate = util.stringToDate(date);
	std::string stockEntry;

	std::string entryIdArea;
	std::string entryCant;
	std::string entryDate;

	std::ofstream aux;
	std::string a = "data/Products/" + idProduct +"/"+"aux.csv";
	aux.open( a.c_str() );
	int diff = 0;
	bool nuevo = false;
	bool found = false;
	Glib::DateTime nDate;
	if( stock.is_open() ) {
		while( std::getline(stock,stockEntry) ) {
			std::vector<std::string> v;
			util.tokenizarMensajeConChar(stockEntry,v,',');
			entryDate = v[2];
			entryIdArea = v[0];
			//Ya hay una entrada de esa área de visión, hay que actualizarla si date es más nueva que entryDate;
			if(entryIdArea == idArea) {
				nDate = util.stringToDate(entryDate);
				if(mdate.compare(nDate) == 1) {
					aux << idArea + "," + util.toString(counter) + "," + date + "\n";
					entryCant = v[1];
					int act = std::atoi( entryCant.c_str() );
					diff = counter - act;
					nuevo = true;
				}else{
					aux << stockEntry << "\n";
				}
				found = true;
			}else{
				aux << stockEntry << "\n";
			}
		}
		stock.close();
	}
	if(!found) {
		diff = counter;
		aux << idArea + "," + util.toString(counter) + "," + date + "\n";
		nuevo = true;
	}
	aux.close();
	::remove( f.c_str() );
	::rename( a.c_str(),f.c_str() );

	if(nuevo) {
		actualizarStockGeneral(idProduct,getActual(idProduct)+diff);
		actualizarStockAreaVision(idProduct,idArea,counter);
	}


	return nuevo;

}

void Stock::actualizarStockAreaVision(std::string idProduct, std::string idArea, unsigned int counter){
	/* Actualiza el archivo de stock del área de visión con la nueva cantidad de el producto. */
	std::string pathArea = "data/VisionAreas/" + idArea + "/stock.csv";
	std::string pathAux = "data/VisionAreas/" + idArea + "/aux.csv";
	utils::StringUtils util;
	std::string nuevo = idProduct + "," + util.toString(counter);

	if( reemplazarLinea(pathArea,pathAux,nuevo,0) ) {
		std::ifstream aux ( pathArea.c_str() );
		if( aux.is_open() ) {
			aux.close();
			::remove( pathArea.c_str() );
		}
		::rename( pathAux.c_str(),pathArea.c_str() );
	}


}

unsigned int Stock::getActual(const std::string& idProduct) {
	/* Devuelve la disponibilidad en stock del producto, más reciente. */
	std::ifstream gral;
	gral.open("data/gral.csv");
	if( gral.is_open() ) {
		std::string stockEntry;
		utils::StringUtils util;
		while( std::getline(gral,stockEntry) ) {
			std::vector<std::string> v;
			util.tokenizarMensajeConChar(stockEntry,v,',');
			std::string entryIdProduct = v[0];
			if(entryIdProduct == idProduct) {
				std::string entryIdCant = v[1];
				return std::atoi( entryIdCant.c_str() );
			}
		}
		gral.close();
	}
	return 0;
}

std::vector<std::pair<std::string, std::string> > Stock::separarDias(const std::string& desde, const std::string& hasta){
	/* Recibe dos fechas/horas en formato DD/MM/AA-hh:mm, divide ese período en intervalos dentro de un mismo día y 
	 * devuelve un vector con las fechas inicial y final de cada uno de esos intervalos. */
	std::vector<std::pair<std::string, std::string> > s;
	utils::StringUtils util;
	Glib::DateTime fechaDesde = util.stringToDate(desde);
	Glib::DateTime fechaHasta = util.stringToDate(hasta);
	Glib::DateTime fecha = fechaDesde;
	Glib::DateTime fechaAnterior = fechaDesde;
	while(fecha.compare(fechaHasta) != 0) {
		fecha = fecha.add_minutes(30);
		if(fecha.get_day_of_month() != fechaAnterior.get_day_of_month()||fecha.compare(fechaHasta) == 0) {

			s.push_back( std::pair<std::string,std::string>( util.dateToString(fechaAnterior),util.dateToString( fecha.add_minutes(-1) ) ) );
			fechaAnterior = fecha;
		}
	}
	return s;
}

Glib::DateTime fechaMasCercana(const std::vector<Glib::DateTime>& fechasDisponibles, const Glib::DateTime& fecha){
	/*Recibe un vector con fechas ordenadas en forma creciente, y una fecha. Devuelve una fecha que es la anterior 
	 * inmediata a la fecha recibida por parámetro, de entre las del vector de fechas. */
	Glib::DateTime masCercana ( Glib::DateTime::create_utc(1,1,1,0,0,0) );
	if(fechasDisponibles.size() != 0) {
		for(size_t i = 0; i < fechasDisponibles.size(); i++) {
			Glib::DateTime actual = fechasDisponibles[i];
			if(fecha.compare(actual) == 1 && actual.compare(masCercana) == 1) masCercana = actual;
		}
	}
	return masCercana;
}

std::vector<int> Stock::obtenerHistoricoGeneral(const std::string& idProduct, const std::string& desde,const std::string& hasta){
	
	/* Recibe un producto y una fecha inicial y final. Devuelve un vector con las cantidades en stock de ese producto entre las fechas, cada intervalos de 30 minutos.*/
	
	std::vector< std::pair<std::string,std::string> > v = separarDias(desde,hasta);
	std::vector<int> s;

	utils::StringUtils util;
	Glib::DateTime fechaYHora;
	std::string pathResumenes = "data/Historic/Summaries";
	std::string nombreArchivoResumenAnterior;
	utils::Directory dir (pathResumenes);
	std::vector<std::string> archivosResumenDisponibles = dir.getFileNames();

	std::for_each(archivosResumenDisponibles.begin(),archivosResumenDisponibles.end(),extraerNombreArchivo);

	std::vector<Glib::DateTime> fechasDisponibles;

	for(unsigned int i = 0; i < archivosResumenDisponibles.size(); i++) {
		fechasDisponibles.push_back( nombreArchivoADate(archivosResumenDisponibles[i]) );
	}

	std::sort(fechasDisponibles.begin(),fechasDisponibles.end(),comparaFechas);

	Glib::DateTime fechaMas;

	for(unsigned int i = 0; i < v.size(); i++) {
		fechaYHora = util.stringToDate(v[i].first);

		fechaYHora = fechaYHora.add_hours( -fechaYHora.get_hour() );
		fechaYHora = fechaYHora.add_minutes( -fechaYHora.get_minute() );


		fechaMas = fechaMasCercana(fechasDisponibles,fechaYHora);

		Glib::DateTime auxaa ( Glib::DateTime::create_utc(1,1,1,0,0,0) );

		if(fechaMas.compare(auxaa) == 0) nombreArchivoResumenAnterior = "";
		else{
			nombreArchivoResumenAnterior = dateANombreArchivo(fechaMas);

			nombreArchivoResumenAnterior = pathResumenes + "/" + nombreArchivoResumenAnterior;
		}
		std::vector<int> aux = obtenerHistorico(idProduct,v[i].first,v[i].second,nombreArchivoResumenAnterior);
		for(unsigned int j = 0; j < aux.size(); j++) {
			s.push_back(aux[j]);
		}
	}



	return s;
}


std::vector<int> Stock::obtenerHistorico(const std::string& idProduct, const std::string& desde, const std::string& hasta, std::string archivoResumenAnterior){
	/* Recibe el id de un producto, una hora inicial y una hora final DENTRO DEL MISMO DÍA. 
	 * Haciendo uso del archivo de resumen del día anterior, devuelve un vector con las cantidades en stock entre esos horarios.*/
	utils::StringUtils util;
	std::vector<std::string> tok;
	Glib::DateTime fechaDesde = util.stringToDate(desde);
	Glib::DateTime fechaHasta = util.stringToDate(hasta);
	std::string f = "data/Historic/" + dateANombreArchivo(fechaDesde);

	unsigned int total = ( fechaHasta.get_hour() - fechaDesde.get_hour() )*2 + (fechaHasta.get_minute() - fechaDesde.get_minute() + 1)/30;
	std::ifstream stock( f.c_str() );

	int interDesde = std::atoi( calcularIntervalo(fechaDesde).c_str() );
	int interHasta = std::atoi( calcularIntervalo(fechaHasta).c_str() );
	int interActual;
	std::vector<int> hist(total,-1);
	std::map<std::string, std::vector<int> > areas;
	if( stock.is_open() ) {
		std::string stockEntry;
		/*Este vector tiene el stock histórico.*/
		while( std::getline(stock,stockEntry) ) {
			std::vector<std::string> toka;
			util.tokenizarMensajeConChar(stockEntry,toka,',');
			std::string entryInterv = toka[0];
			std::string entryTime = toka[1];
			std::string entryArea = toka[2];
			std::string entryProduct = toka[3];
			std::string entryCant = toka[4];

			interActual = std::atoi( entryInterv.c_str() );

			/*Busco el vector de esta área de visión*/
			if(entryProduct == idProduct) {

				/*indice es la posicion donde va el dato del intervalo actual*/
				int indice;
				if(interActual > interHasta) break;
				else {
					if(areas.count(entryArea) == 0) {
						std::vector<int> actual (total,-1);
						areas[entryArea] = actual;
					}
					std::vector<int>& actual = areas[entryArea];

					if(interActual <= interDesde) {
						indice = 0;
					}else {
						std::string hh3;
						hh3.push_back(entryInterv[0]);
						hh3.push_back(entryInterv[1]);
						std::string mm3;
						mm3.push_back(entryInterv[2]);
						mm3.push_back(entryInterv[3]);
						indice = ( std::atoi( hh3.c_str() ) - fechaDesde.get_hour() )*2 + ( std::atoi( mm3.c_str() ) - fechaDesde.get_minute() )/30 - 1;
					}
					for(unsigned int i = indice; i < total; i++) {
						actual[i] = std::atoi( entryCant.c_str() );
					}
				}

			}
		}
	}

	/****************  COMPLETO LAS PRIMERAS POSICIONES DE LAS AREAS DE VISION CON EL ULTIMO DATO QUE TENGO DEL RESUMEN ANTERIOR ************/
	if(archivoResumenAnterior != "") {

		std::ifstream resumenAnterior( archivoResumenAnterior.c_str() );

		std::string entrada;
		if( resumenAnterior.is_open() ) {
			while( std::getline(resumenAnterior,entrada) ) {
				std::vector<std::string> vectorcito;
				vectorcito.clear();
				util.tokenizarMensajeConChar(entrada,vectorcito,',');
				std::string mProduct = vectorcito[2];
				std::string mArea = vectorcito[0];
				std::string mCant = vectorcito[3];
				if(mProduct == idProduct) {
					if( !areas.count(mArea) ) {
						std::vector<int> actual (total,-1);
						areas[mArea] = actual;
					}
					std::vector<int>& stockArea = areas[mArea];
					for(size_t i = 0; i < stockArea.size(); i++) {

						if(stockArea[i] != -1) break;
						else{
							stockArea[i] = std::atoi( mCant.c_str() );
						}

					}
				}
			}
		}
	}
	for(size_t i = 0; i < hist.size(); i++) {
		hist[i] = 0;
	}
	for(std::map<std::string, std::vector<int> >::iterator iter = areas.begin(); iter != areas.end(); ++iter) {
		for(size_t i = 0; i < total; i++) {
			if(iter->second[i] > 0) {
				hist[i] += iter->second[i];
			}
		}
	}
	return hist;
}

void Stock::obtenerStockGeneral(std::vector< std::string >& idProductos, std::vector< int >& cant){
	/* Modifica los vectores recibidos con los ids de los productos disponibles actualmente y sus cantidades respectivas. */
	std::ifstream gral;
	gral.open("data/gral.csv");
	if( gral.is_open() ) {
		std::string stockEntry;
		std::vector<std::string> v;
		utils::StringUtils util;
		while( std::getline(gral,stockEntry) ) {
			v.clear();
			util.tokenizarMensajeConChar(stockEntry,v,',');
			std::string entryIdProduct = v[0];
			std::string entryIdCant = v[1];
			int stk = std::atoi( entryIdCant.c_str() );
			idProductos.push_back(entryIdProduct);
			cant.push_back(stk);
		}
		gral.close();
	}
}
void Stock::obtenerStockAreaVision(const std::string& idArea,std::vector<std::string>& idProducts,std::vector<int>& cant){
	/* Recibe el id de un área de visión y dos vectores para los ids de los productos y sus cantidades, que serán los 
	 * indicados por el archivo de stock del área de visión. */
	utils::StringUtils util;
	std::string pathArea = "data/VisionAreas/"+idArea+"/stock.csv";
	std::ifstream stock( pathArea.c_str() );
	std::string line;
	std::string id;
	int stk;
	std::vector<std::string> stockEntry;
	if( stock.is_open() ) {
		while( std::getline(stock,line) ) {
			stockEntry.clear();
			util.tokenizarMensajeConChar(line,stockEntry,',');
			id = stockEntry[0];
			stk = std::atoi( stockEntry[1].c_str() );

			idProducts.push_back(id);
			cant.push_back(stk);
		}
	}
}
} /* namespace utils */
