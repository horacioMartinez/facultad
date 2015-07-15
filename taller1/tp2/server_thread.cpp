#include <pthread.h>
#include "server_thread.h"

server_thread::server_thread() {
  this->muerto = false;
  this->thread = 0;
}

server_thread::~server_thread() {
}

void* server_thread::starter(void* data) {
  server_thread* realthread = (server_thread*) data;
  realthread->run();
  return NULL;
}

void server_thread::join() {
  pthread_join(this->thread, NULL);
}

void server_thread::start() {
  pthread_create(&this->thread, NULL, starter, this);
}

void server_thread::run() {
}

bool server_thread::isMuerto() const {
  return this->muerto;
}

void server_thread::setMuerto(bool estaMuerto) {
  this->muerto = estaMuerto;
}
