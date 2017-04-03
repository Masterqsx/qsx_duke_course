#include "proxy.h"

using namespace std;

proxy_server *p1;

void* proxy_connect(void* c_in) {
  pthread_detach(pthread_self());
  
  connec* c = (connec *)c_in;
  try {
    proxy_recvheader(c);
    if (request_type(c->from_client) == 2) https_connect(c);  
    else http_connect(c);
  }
  catch (exception& e) {
    delete c;
    cout << e.what() << endl;  
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{ 
  signal(SIGPIPE, SIG_IGN);
  if (daemon(0, 1) == -1) {
    perror("Daemon error");
    exit(EXIT_FAILURE);
  }
  p1 = new proxy_server();
  string argu("8000");
  if (argc > 1) argu = string(argv[1]);
  p1->setup_socket(1, NULL, argu.substr(0, 6).c_str());
  p1->server_listen();
  connec *c = NULL;
  while (1) {
    pthread_t tid;
    c = p1->server_accept();
    if (c) pthread_create(&tid, NULL, proxy_connect, (void *)c);
  }
  return 0;
}
