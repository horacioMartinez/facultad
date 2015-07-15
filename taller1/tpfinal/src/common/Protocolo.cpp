#include "Protocolo.h"

#include <cstdlib>
#include <iterator>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "Directory.h"
#include "Communication.h"

void Protocolo::obtenerStockAreaVision(const std::string& aVision, std::vector< std::pair< std::string, int > >& stockAreaVision)
{
	std::string s = "SA|" + aVision + "\n";
	comunicador-> send(s);
	std::string respuesta;
	comunicador->receive(respuesta);
	utils::StringUtils util;
	std::vector<std::string> aux;
	util.tokenizarMensajeConChar(respuesta,aux,'|');
	for(unsigned int i = 0; i < aux.size() -1; i += 2){
		std::string idProducto = aux[i];
		int cant = std::atoi(aux[i+1].c_str());
		std::pair <std::string ,int> par (idProducto,cant);
		stockAreaVision.push_back(par);
	}
}


Protocolo::Protocolo(net::Communication *comunicador) {
  this->comunicador = comunicador;
}

// Pasar parametros sin fin de linea, genera un string concatenado de la forma
// parametro1|parametro2|...|ultimoparametro\n
std::string Protocolo::concatenarMensaje(std::vector<std::string>& parametros) {
  std::stringstream buffer;
  std::string mensajeConcatenado;
  std::vector<std::string>::iterator it;
  std::vector<std::string>::iterator final_iter = parametros.end();
  --final_iter;
  for (it = parametros.begin(); it != parametros.end(); ++it) {
    if (it != final_iter)
      buffer << *it << "|";
    else
      buffer << *it;
  }
  buffer << '\n';
  return buffer.str();
}

void Protocolo::altaProducto(std::string nombre,std::string descripcion, std::string icono, std::vector<std::string> imagenes){
	std::vector<std::string> params;
	params.push_back("PA");
	params.push_back(nombre);
	params.push_back(descripcion);
	std::stringstream s;
	s << imagenes.size();
	params.push_back(s.str());
	std::string msg = concatenarMensaje(params);
	comunicador -> send(msg);
	std::string sss;
	comunicador->receive(sss);
	comunicador -> sendFileWithName(icono);
	for(unsigned int i = 0; i < imagenes.size(); i++){
		comunicador -> sendFileWithName(imagenes[i]);
	}

}
// Guarda en un vector los parametros de un string concatenado como con la funcion de arriba

void Protocolo::tokenizarMensaje(std::string mensaje,std::vector<std::string> &vectorResultado) {
  // remover '\n' del final del mensaje si es que lo tiene
  // y no es el unico caracter:
  if (!mensaje.empty() && mensaje[mensaje.length() - 1] == '\n'
      && mensaje.size() > 1) {
    mensaje.erase(mensaje.length() - 1);
  }
  std::stringstream stream(mensaje);
  std::string token;
  while (std::getline(stream, token, '|')) {
    vectorResultado.push_back(token);
  }
}

void Protocolo::getAreasDeVision(std::vector<std::string> &areasDeVision, std::vector<std::string>& ids) {
  comunicador->send("AL\n");
  std::string recibido;
  comunicador->receive(recibido);
  std::vector<std::string> aux;
  tokenizarMensaje(recibido, aux);
	for(unsigned int i = 0; i < aux.size() - 1; i+=2){
		ids.push_back(aux[i]);
		areasDeVision.push_back(aux[i+1]);
	}
}

void Protocolo::getProductos(std::vector<std::string> &productos,std::vector<std::string>& ids) {
  comunicador->send("PL\n");
  std::string recibido;
  comunicador->receive(recibido);
  std::vector <std::string> aux;
  tokenizarMensaje(recibido, aux);
  	for(unsigned int i = 0; i < aux.size() - 1; i+=2){
		ids.push_back(aux[i]);
		productos.push_back(aux[i+1]);
	}
}

void Protocolo::modificarAreaVision(std::string id, std::string nombre, std::string tipo)
{
	std::string s = "AM|";
	s+=id;
	s+="|";
	s+=nombre;
	s+="|";
	s+=tipo;
	s+="\n";
	comunicador->send(s);
	comunicador->receive(s);
}

void Protocolo::modificarProducto(std::string id, std::string nombre, std::string descripcion, std::string icono, std::vector<std::string> imagenes)
{
	utils::StringUtils util;
	std::string msj = "PM|" + id + "|" + nombre + "|" + descripcion +  "|" + util.toString(imagenes.size())  + "\n";
	comunicador->send(msj);
	std::string r;
	comunicador->receive(r);
	comunicador->sendFileWithName(icono);
	for(unsigned int i = 0; i < imagenes.size();i++){
		comunicador->sendFileWithName(imagenes[i]);
	}
}

void Protocolo::getStockGeneral(std::vector<std::pair<std::string,int> >& stock){
	comunicador -> send("SG\n");
	std::string respuesta;
	comunicador -> receive(respuesta);
	std::vector<std::string> vector;
	tokenizarMensaje(respuesta,vector);
	std::stringstream s;
	std::vector<std::string>::iterator iter;
	int c;
	std::string producto;
	for(iter = vector.begin(); iter != vector.end(); ++iter){
		producto = *iter;
		s << *++iter;
		s >> c;
		stock.push_back(std::pair<std::string,int>(producto,c));
	}
}

void Protocolo::bajaProducto(std::string id){
	std::string s = "PB";
	s+="|";
	s+=id;
	s+="\n";
	comunicador->send(s);
	comunicador->receive(s);
	utils::Directory dir("data/" + id);
	dir.remove();

}

void Protocolo::getDetallesProductos(std::vector<std::string> &productos, std::vector<std::string>& ids, std::vector<std::string> &descripciones, std::vector<std::string> &iconos){
	comunicador -> send("DP\n");
	std::stringstream s;
	unsigned int cantidadProductos;
	std::string msj;
	comunicador->receive(msj);
	comunicador->send("ok\n");
	s<<msj;
	s>>cantidadProductos;
	std::vector<std::string> attr;
	for(unsigned int i = 0; i < cantidadProductos; i++){
		msj = "";
		attr.clear();
		comunicador -> receive(msj);
		comunicador->send("ok\n");
		tokenizarMensaje(msj,attr);
		ids.push_back(attr[0]);
		productos.push_back(attr[1]);
		descripciones.push_back(attr[2]);
		std::string tam;
		comunicador->receive(tam);
		utils::StringUtils stringutils;
		std::vector<std::string> tok;
		stringutils.tokenizarMensaje(tam,tok);
		std::stringstream s;
		std::string nombreArchivo = tok[1];
		s << tok[2];
		int tamanio;
		s >> tamanio;
		comunicador->send("ok\n");
		std::string directorio = "data/" + ids[i] + "/" ;
		struct stat st;
		stat (directorio.c_str(),&st);
		bool isdir = S_ISDIR(st.st_mode);
		if(!isdir){
			/* Si el directorio no existia, crearlo*/
			utils::Directory dir;
			dir.make(directorio);
		}
		std::string str = directorio + nombreArchivo;
		comunicador->receiveFile(str,tamanio);
		iconos.push_back(str);
	}
}

void Protocolo::altaAreaVision(std::string nombre, std::string tipo){
	std::vector<std::string> params;
	params.push_back("AA");
	params.push_back(nombre);
	params.push_back(tipo);
	comunicador -> send(concatenarMensaje(params));
	std::string id;
	comunicador ->receive(id);
}

void Protocolo::bajaAreaVision(std::string id)
{
	std::string s = "AB|";
	s += id + "\n";
	comunicador->send(s);
	comunicador->receive(s);
}

void Protocolo::getTiposAreasVision(std::vector<std::string>& areasVision,std::vector<std::string>& ids, std::vector<std::string>& tipos)
{
	comunicador -> send("DA\n");
	std::string rta;
	comunicador -> receive(rta);
	if(rta=="error\n")return;
	std::vector<std::string> tokens;
	tokenizarMensaje(rta,tokens);
	for(std::vector<std::string>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter){
		ids.push_back(*iter);
		areasVision.push_back(*++iter);
		tipos.push_back(*++iter);
	}
}

// almacena las imagenes en un vector y sus extensiones en otro, tal que la extension de la imagen en pos i se encuentra en pos i del vector extensiones
void Protocolo::getImagenesDeProducto(const std::string &id, std::vector<std::string> &imagenes, std::vector<std::string> &extensiones) {
  std::vector<std::string> parametros;
  parametros.push_back("PI");
  parametros.push_back(id);
  comunicador->send(concatenarMensaje(parametros));
  parametros.clear();
  std::string recibido;
  comunicador->receive(recibido);
  int cantidadImagenes = atoi( recibido.c_str() );
  recibido.clear();
  parametros.clear();
  for (int i = 0; i < cantidadImagenes; i++){
    bool png = false;
    comunicador->receive(recibido);
    tokenizarMensaje(recibido,parametros);
    if (parametros[0] == "EIP")
      png = true;

    unsigned int size = atoi( parametros[1].c_str() );
    comunicador->send(utils::OK_MESSAGE);
    recibido.clear();
    parametros.clear();

    comunicador->receiveOfSize(size,recibido);
    if (size ==  recibido.size()) {
    	comunicador->send(utils::OK_MESSAGE);
    }
    imagenes.push_back(recibido);
    if (png)
      extensiones.push_back(".png");
    else
      extensiones.push_back(".jpg");

    recibido.clear();
  }
}

void Protocolo::getImagenesProducto(const std::string& id ,std::vector<std::string>& imagenes)
{
	std::vector<std::string> parametros;
	parametros.push_back("II");
	parametros.push_back(id);
	comunicador->send(concatenarMensaje(parametros));
	parametros.clear();
	std::string recibido;
	comunicador->receive(recibido);
	if(recibido=="error\n")return;
	int cantidadImagenes = atoi( recibido.c_str() );
	comunicador->send("ok\n");
	recibido.clear();
	parametros.clear();
	for (int i = 0; i < cantidadImagenes; i++){
	  comunicador->receive(recibido);
	  tokenizarMensaje(recibido,parametros);

	  std::string nombre = parametros[1];
	  std::string tamanio = parametros[2];

	  unsigned int size = atoi( parametros[2].c_str() );

	  comunicador->send(utils::OK_MESSAGE);

	  recibido.clear();
	  parametros.clear();
		std::string s = "data/" + id + "/" + nombre;
		comunicador->receiveFile(s,size);
	imagenes.push_back(s);
	}
}

void Protocolo::enviarImagen(bool png, bool featureMatching,const std::string &areaDeVision,const std::string &fechaYHora,const std::string &bytesImagen) {
  std::vector<std::string> parametros;
  parametros.push_back("PF");
  if (png)
    parametros.push_back("EIP");
  else
    parametros.push_back("EIJ");
  if (featureMatching)
    parametros.push_back("FM");
  else
    parametros.push_back("TP");
  std::string answer;
  parametros.push_back(areaDeVision);
  parametros.push_back(fechaYHora);
  int size = (int) bytesImagen.size();
  parametros.push_back(stringUtils.toString(size));

  comunicador->send(concatenarMensaje(parametros));
  comunicador->receive(answer);
  comunicador->send(bytesImagen);
  answer.clear();
  comunicador->receive(answer);
}

void Protocolo::getHistorico(std::string idProducto, std::string desde, std::string hasta, std::vector<int>& hist){
	std::string s = "SH|" + idProducto + "|" + desde + "|" + hasta + "\n";
	comunicador->send(s);
	s ="";
	comunicador->receive(s);
	std::vector<std::string> tok;
	utils::StringUtils util;
	util.tokenizarMensajeConChar(s,tok,'|');
	for(unsigned int i = 0; i < tok.size(); i++){
		hist.push_back(std::atoi(tok[i].c_str()));
	}
}

void Protocolo::enviarVideo(bool featureMatching,const std::string &areaDeVision,const std::string &fechaYHora,const std::string &bytesImagen) {
  std::vector<std::string> parametros;
  parametros.push_back("PV");
  if (featureMatching)
    parametros.push_back("FM");
  else
    parametros.push_back("TP");
  std::string answer;
  parametros.push_back(areaDeVision);
  parametros.push_back(fechaYHora);
  int size = (int) bytesImagen.size();
  parametros.push_back(stringUtils.toString(size));

  comunicador->send(concatenarMensaje(parametros));
  comunicador->receive(answer);
  comunicador->send(bytesImagen);
  answer.clear();
  comunicador->receive(answer);
}

