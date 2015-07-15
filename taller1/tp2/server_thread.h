#ifndef SRC_SERVER_THREAD_H_
#define SRC_SERVER_THREAD_H_
#include <pthread.h>

class server_thread {
 public:
  server_thread();
  virtual ~server_thread();
  void start();
  void join();
  virtual void run();
  bool isMuerto() const;
  void setMuerto(bool estaMuerto);

 protected:
  bool muerto;
 private:
  pthread_t thread;
  static void *starter(void* data);
};

#endif
