#include "proxy.h"

using namespace std;

proxy_server *p1;
vector<cache_cb*> caching;
vector<pthread_mutex_t> rwlock_vector;
unsigned N = 337;
pthread_mutex_t lock;

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
  string argu1("8000"), argu2("337");
  if (argc > 2) {
    argu1 = string(argv[1]);
    argu2 = string(argv[2]);
  }
  N = (unsigned) stoul(argu2);
  caching = vector<cache_cb*>(N, NULL);
  rwlock_vector = vector<pthread_mutex_t>(N, PTHREAD_MUTEX_INITIALIZER);
  lock = PTHREAD_MUTEX_INITIALIZER;
  signal(SIGPIPE, SIG_IGN);
  freopen("/var/log/erss-proxy.log","w",stdout);
  freopen("/var/log/erss-proxy.log","w",stderr);
  if (daemon(0, 1) == -1) {
    perror("Daemon error");
    exit(EXIT_FAILURE);
  }
  p1 = new proxy_server();
  p1->setup_socket(1, NULL, argu1.substr(0, 6).c_str());
  p1->server_listen();
  connec *c = NULL;
  while (1) {
    pthread_t tid;
    c = p1->server_accept();
    if (c) pthread_create(&tid, NULL, proxy_connect, (void *)c);
  }
  return 0;
}
