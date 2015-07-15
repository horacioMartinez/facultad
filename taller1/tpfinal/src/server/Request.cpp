/*
 * Request.cpp
 *
 *  Created on: 28/05/2015
 *      Author: pablito
 */

#include "Request.h"
#include <iostream>
#include <vector>


namespace requests {

Request::Request(net::Communication* const communication,
				 catalog::Catalog* const catalog) {
	this->socket = communication;
	this->catalog = catalog;
}

Request::~Request() {
	delete this->socket;
}

void* Request::process() {
	std::string request;
	net::Communication* communication = this->getCommunication();
	while (this->isRunning()) {
			try {
				communication->receive(request);
				this->executeRequest(request);
				request.clear();
			}catch (std::exception &e) {
				this->stop();
				std::cerr<<e.what()<<std::endl;
				communication->interrupt();
				return (void *) NULL;
			}
		}
	communication->interrupt();
	return (void *) NULL;
}

void Request::executeRequest(const std::string& request) {
	utils::StringUtils util;
	if (!request.empty()) {
		std::vector<std::string> splitRequest = util.split(request,utils::separator);
		std::string type = splitRequest.front();
		if(type == utils::NEW_VISION_AREA) {
				createVisionArea(splitRequest);
		} else if(type ==  utils::MODIFY_VISION_AREA) {
				modifyVisionArea(splitRequest);
		} else if(type == utils::DELETE_VISION_AREA) {
				deleteVisionArea(splitRequest);
		} else if (type==utils::NEW_PRODUCT) {
				createProduct(splitRequest);
		} else if (type == utils::MODIFY_PRODUCT) {
				modifyProduct(splitRequest);
		} else if (type == utils::DELETE_PRODUCT) {
			deleteProduct(splitRequest);
		} else if (type == utils::LIST_AREA) {
			listAreas();
		} else if (type == utils::LIST_PRODUCT) {
			listProducts();
		} else if (type == utils::PRODUCT_IMAGE) {
			listProductImages(splitRequest);
		} else if (type == utils::STOCK_GENERAL) {
			listStockGeneral(splitRequest);
		} else if (type == utils::STOCK_AREA) {
			listStockArea(splitRequest);
		} else if (type == utils::STOCK_HISTORIC) {
			listStockHistoric(splitRequest);
		} else if (type == utils::PROCESS_FILE) {
			processFile(splitRequest);
		} else if (type == utils::PROCESS_VIDEO) {
			processVideo(splitRequest);
		} else if (type == utils::QUIT) {
			this->stop();
		} else if (type == utils::DETAILS_AREA){
			getAreas();
		}
		else if (type == utils::DETAILS_PRODUCT){
					detallesProductos();
				}
		else if (type == utils::IMAGES){
					imagenesDeProducto(splitRequest);
				}
		else {
			this->socket->send(utils::ERROR_MESSAGE);
		}
	}
}

void Request::imagenesDeProducto(const std::vector<std::string>& splitVector){
	std::string id = splitVector[1];
	utils::StringUtils util;
	util.removeLastChar(id);
	std::vector<catalog::Product> productos = catalog->getProducts();
	for(unsigned int i = 0; i < productos.size(); i++){
		if(productos[i].getId() == id){
			std::string pathImagenes = productos[i].getPath();
			std::string message = utils::ERROR_MESSAGE;
				if (!pathImagenes.empty()) {
					utils::Directory dir(pathImagenes);
					std::vector<std::string> images = dir.getFileNames();
					std::vector<std::string>::iterator it= images.begin();
					std::string cImages = util.toString(images.size());
					cImages += utils::endline;
					this->getCommunication()->send(cImages);
					std::string s;
					this->getCommunication()->receive(s);
					while(it != images.end()) {
						this->getCommunication()->sendFileWithName((*it));
						it++;
					}
				} else {
					this->getCommunication()->send(message);
				}
		}
	}
}

void Request::createVisionArea(const std::vector<std::string> &splitVector) {
	std::string message = utils::ERROR_MESSAGE;
	utils::StringUtils util;
	if (splitVector.size() == utils::CREATE_AREA_ARGU) {
		std::string name = splitVector[1];
		std::string type = splitVector[2];
		util.removeLastChar(type);
		std::string id = catalog->addArea(name, type);
		message.clear();
		message = id + utils::endline;
	}
	this->getCommunication()->send(message);
}

void Request::modifyVisionArea(const std::vector<std::string> &splitVector) {
	std::string message = utils::ERROR_MESSAGE;
	utils::StringUtils util;
	if (splitVector.size() == 4) {
		std::string id = splitVector[utils::ID_AREA];
		std::string nombre = splitVector[2];
		std::string tipo = splitVector[3];
		if (catalog->updateArea(id,nombre,tipo)) {
			message.clear();
			message = utils::OK_MESSAGE;
		}
	}
	this->getCommunication()->send(message);
}

void Request::deleteVisionArea(const std::vector<std::string> &splitVector) {
	std::string message = utils::ERROR_MESSAGE;
	utils::StringUtils util;
	if (splitVector.size() == utils::DELETE_AREA_ARGU) {
		std::string id = splitVector[utils::ID_AREA];
		util.removeLastChar(id);
		if (catalog->removeArea(id)) {
			message.clear();
			message = utils::OK_MESSAGE;
		}
	}
	this->getCommunication()->send(message);
}

void Request::createProduct(const std::vector<std::string> &splitVector) {
	std::string nombre = splitVector[1];
	std::string descripcion = splitVector[2];
	std::string cantImagenes = splitVector[3];
	int cantidad;
	std::stringstream s;
	s << cantImagenes;
	s >> cantidad;

	std::string attributes;
	attributes = nombre + "|" + descripcion;
	const std::string id = catalog->addProduct(attributes);
	
	std::string path = catalog->getPathProductImages(id);
	std::string pathIconos = catalog ->getPathProductIcons(id);
	this->getCommunication()->send(utils::OK_MESSAGE);
	receiveImage(pathIconos);
	for (int i = 0; i < cantidad; i++){
		receiveImage(path);
	}
}

void Request::detallesProductos(){
	std::vector<catalog::Product> productos=catalog->getProducts();
	utils::StringUtils util;
	std::string s = util.toString(productos.size()) + "\n";

	this->getCommunication()->send(s);
	this->getCommunication()->receive(s);
	for(unsigned int i = 0; i < productos.size(); i++){
		detailsProduct(productos[i]);
	}
}

void Request::detailsProduct(catalog::Product& producto) {
		std::string nombre = producto.getName();
		std::string descripcion = producto.getDescription();
		std::string id = producto.getId();
		std::string msj = id+"|"+nombre+"|"+descripcion + "\n";
		this->getCommunication()->send(msj);
		std::string rta;
		this->getCommunication()->receive(rta);
		if(rta == "ok\n"){
		std::string dirstr = producto.getPathIcon();
		utils::Directory dir (dirstr);
		std::vector<std::string> iconos = dir.getFileNames();
		this->getCommunication()->sendFileWithName(iconos[0]);
		}
}

void Request::receiveImage(std::string path){
	std::string tam; // Tiene el formato, el nombre y el tamaño separados por un |
	this -> getCommunication()->receive(tam);
	utils::StringUtils stringutils;
	std::vector<std::string> tok;
	stringutils.tokenizarMensaje(tam,tok);
	std::stringstream s;
	s << tok[2];
	int tamanio;
	s >> tamanio;
	std::string nombre = tok[1];
	std::string ext = tok[0];
	if (ext != "EI") this -> getCommunication()->send(utils::ERROR_MESSAGE);
	this -> getCommunication()->send(utils::OK_MESSAGE);
	path += "/"+nombre;
	this -> getCommunication()->receiveFile(path,tamanio);
}

void Request::modifyProduct(const std::vector<std::string> &splitVector) {
	std::string id = splitVector[1];
	std::string nombre = splitVector[2];
	std::string descripcion = splitVector[3];
	std::string cant = splitVector[4];
	std::stringstream s;
	int cantImagenes;
	s << cant;
	s >> cantImagenes;
	/**/
	this->getCommunication()->send(utils::OK_MESSAGE);
	catalog->updateProduct(id,nombre,descripcion);
	std::string pathIcono = catalog->getPathProductIcons(id);
	utils::Directory dir (pathIcono);
	dir.remove();
	dir.make(pathIcono);
	receiveImage(pathIcono);
	std::string path = catalog->getPathProductImages(id);
	utils::Directory dir1 (path);
	dir1.remove();
	dir1.make(path);
	for(unsigned int i = 0; i < cantImagenes; i++){
		receiveImage(path);
	}
}

void Request::deleteProduct(const std::vector<std::string> &splitVector) {
	splitVector.size();
	utils::StringUtils stringutils;
	std::string id = splitVector[1];
	stringutils.removeLastChar(id);
	catalog->removeProduct(id);
	this->getCommunication()->send(utils::OK_MESSAGE);
}

void Request::listAreas() {
		std::string message = catalog->listAreas();
		this->getCommunication()->send(message);
}

void Request::listProducts() {
	std::string message = catalog->listProducts();
	this->getCommunication()->send(message);
}

void Request::listProductImages(const std::vector<std::string> &splitVector) {
	std::string message = utils::ERROR_MESSAGE;
	utils::StringUtils util;
	if (splitVector.size() == 2) {
		std::string id = splitVector[1];
		util.removeLastChar(id);
		std::string path("");
		path = catalog->getPathProductImages(id);
		if (!path.empty()) {
			utils::Directory dir(path);
			std::vector<std::string> images = dir.getFileNames();
			std::vector<std::string>::iterator it= images.begin();
			std::string cImages = util.toString(images.size());
			cImages += utils::endline;
			this->getCommunication()->send(cImages);
			while(it != images.end()) {
				this->getCommunication()->sendFile((*it));
				it++;
			}
		}
	} else {
		this->getCommunication()->send(message);
	}
}

void Request::getAreas(){
	std::vector<catalog::VisionArea> areas = catalog->getAreas();
	std::string msg;
	for(unsigned int i = 0; i < areas.size(); i++){
		msg += areas[i].getId();
		msg += "|";
		msg += areas[i].getName();
		msg += "|";
		msg += areas[i].getType();
		msg += "|";
	}
	if(msg.length()!=0)msg[msg.length()-1] = '\n';
	else msg="error\n";
	this -> getCommunication()->send(msg);
}

void Request::listStockGeneral(const std::vector<std::string> &splitVector) {
	utils::StringUtils util;
	std::vector<std::string> idProductos;
	std::vector<int> cant;
	file.obtenerStockGeneral(idProductos,cant);
	if(idProductos.size() == 0){
		std::vector<catalog::Product> listadoProductos = catalog -> getProducts();
		for(int i = 0; i < listadoProductos.size(); i++){
			idProductos.push_back(listadoProductos[i].getId());
			cant.push_back(0);
		}
	}
	std::string s;
	for(int i = 0; i < idProductos.size(); i++){
		s += idProductos[i] + "|" + util.toString(cant[i]) + "|";
	}	
	util.removeLastChar(s);
	s += "\n";
	this->getCommunication()->send(s);
}

void Request::listStockArea(const std::vector<std::string> &splitVector) {
	std::vector<std::string> idProductos;
	std::vector<int> cant;
	std::string idArea = splitVector[1];
	utils::StringUtils util;
	util.removeLastChar(idArea);
	file.obtenerStockAreaVision(idArea,idProductos,cant);
	std::string s;
	std::vector<catalog::Product> productos = catalog->getProducts();
	for(int i = 0; i < idProductos.size(); i++){
		for(int j = 0; j < productos.size(); j++){
			if(productos[j].getId() == idProductos[i]){
				idProductos[i] = productos[j].getName();
				break;
			}
		}
	
	}
	for(int i = 0; i < idProductos.size(); i++){
		s += idProductos[i] + "|" + util.toString(cant[i]) + "|";
	}
	util.removeLastChar(s);
	s += "\n";
	this->getCommunication()->send(s);
}

void Request::listStockHistoric(const std::vector<std::string> &splitVector) {
	std::string idProducto = splitVector[1];
	std::string desde = splitVector[2];
	std::string hasta = splitVector[3];
	std::vector<int> hist = file.obtenerHistoricoGeneral(idProducto,desde,hasta);
	std::string s;
	utils::StringUtils util;
	for(unsigned int i = 0; i < hist.size() - 1; i++){
		s += util.toString(hist[i]) + "|";
	}
	s += util.toString(hist.back()) + "\n";

	this->getCommunication()->send(s);
}

void Request::processFile(const std::vector<std::string> &splitVector) {
  utils::StringUtils utils;
  if (splitVector.size() == 6) {
    std::string extension = utils.setExtension(splitVector[1]);
    std::string method = splitVector[2];
    std::string id = splitVector[3];
    std::string pathProcess = this->catalog->getPathAreasProcess(id);
    std::string date = splitVector[4];
    std::string size = splitVector[5];
    utils.removeLastChar(size);
    int sizeInt = atoi(size.c_str());
    pathProcess += "/" + utils.toString(sizeInt) + extension;
    this->socket->send(utils::OK_MESSAGE);
    this->socket->receiveFile(pathProcess, sizeInt);
    std::vector<catalog::Product> products = catalog->getProducts();
    std::vector<catalog::Product>::iterator iter = products.begin();
    opencv::Matcher mat;
    std::vector<std::string> respuesta;
    if (method == "TP") {
      cv::Mat ref = cv::imread(pathProcess);
      int counter = 0;
      while (iter != products.end()) {
        counter = mat.templateMatching((*iter).getPath(), ref);
        file.update((*iter).getId(), id, counter, date);
        respuesta.push_back((*iter).getId());
        respuesta.push_back(utils.toString(counter));
        counter = 0;
        iter++;
      }
    } else if (method == "FM") {
      cv::Mat ref = cv::imread(pathProcess);
      int counter = 0;
      while (iter != products.end()) {
        counter = mat.featureMatch((*iter).getPath(), ref);
        file.update((*iter).getId(), id, counter, date);
        respuesta.push_back((*iter).getId());
        respuesta.push_back(utils.toString(counter));
        counter = 0;
        iter++;
      }
    }
    std::string mensaje;
    mensaje = utils.concatenarMensaje(respuesta);
    this->socket->send(mensaje);
  } else {
    this->socket->send(utils::ERROR_MESSAGE);
  }
}

void Request::processVideo(const std::vector<std::string> &splitVector) {
  utils::StringUtils utils;
  if (splitVector.size() == 5) {
    std::string extension = utils.setExtension("AVI");
    std::string id = splitVector[2];
    std::string pathProcess = this->catalog->getPathAreasProcess(id);
    std::string date = splitVector[3];
    std::string size = splitVector[4];
    utils.removeLastChar(size);
    int sizeInt = atoi(size.c_str());
    pathProcess += "/" + utils.toString(sizeInt) + extension;
    this->socket->send(utils::OK_MESSAGE);
    this->socket->receiveFile(pathProcess, sizeInt);
    opencv::Matcher mat;
    cv::Mat ref;
    cv::VideoCapture video(pathProcess.c_str());
    std::vector<catalog::Product> products = catalog->getProducts();
    std::vector<catalog::Product>::iterator iter = products.begin();
    if (!video.isOpened()) {
      std::cout << "ERROR: Failed to write the video" << std::endl;
      return;
    }
    //double fps = video.get(CV_CAP_PROP_FPS);
    std::vector<int> vectorCounter(products.size(), 0);
    std::vector<std::string> vectorIDs(products.size(), "");

    unsigned int counter = 0;
    while (video.read(ref)) {
      int i = 0;
      while (iter != products.end()) {
        if (splitVector[1] == "TP")
          counter = mat.templateMatching((*iter).getPath(), ref);
        else if (splitVector[1] == "FM")
          counter = mat.featureMatch((*iter).getPath(), ref);
        vectorCounter[i] = vectorCounter[i] + counter;
        file.update((*iter).getId(), id, counter, date);
        if (vectorIDs[i].empty())
          vectorIDs[i] = (*iter).getId();
        counter = 0;
        iter++;
        i++;
      }
      iter = products.begin();
    }
    std::vector<std::string> respuesta;
    for (unsigned int i = 0; i < vectorCounter.size(); i++) {
      respuesta.push_back(vectorIDs[i]);
      std::cout << vectorIDs[i] << std::endl;
      respuesta.push_back(utils.toString(vectorCounter[i]));
    }
    std::string mensaje;
    mensaje = utils.concatenarMensaje(respuesta);
    this->socket->send(mensaje);
  } else {
    this->socket->send(utils::ERROR_MESSAGE);
  }
}


net::Communication* Request::getCommunication() const {
	return (this->socket);
}
void Request::stop() {
	Thread::stop();
}

} /* namespace requests */
