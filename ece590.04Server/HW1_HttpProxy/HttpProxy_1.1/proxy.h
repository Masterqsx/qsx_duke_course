#ifndef _PROXY_H_
#define _PROXY_H_
#include <iostream>
#include <functional>
#include <sys/stat.h>
#include <fcntl.h>
#include <unordered_map>
#include <pthread.h>
#include <exception>
#include <signal.h>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class cache_cb {
  public:
    double max_age;
    time_t last_modify;
    string e_tag;
    string call; // used to double check has been cached
    vector<char*> data;
    vector<size_t> siz;
    size_t h_value;
    cache_cb();
    cache_cb(double, time_t);
    ~cache_cb();
};

class connec {
  public:
  int connec_fd;
  sockaddr_storage socket_addr;
  socklen_t socket_addr_len;
  string from_client;
  char buffer[8000];
  int index;
  connec();
  connec(int);
  ~connec();
};

class proxy_server {
  public:
  int socket_fd;

  string from_client;
  proxy_server();
  ~proxy_server();
  int setup_socket(int, const char*, const char*);
  void server_listen();
  connec* server_accept();
  int proxy_recvheader(connec*);
};


extern vector<pthread_mutex_t> rwlock_vector;

extern vector<cache_cb*> caching;

extern proxy_server* p1;

extern unsigned N;

extern pthread_mutex_t lock;

void recv_req_log(size_t, string, string);

void cache_log(size_t, size_t, string);

void send_req_log(size_t, string, string, size_t);

void cache_check_log(size_t, string, size_t);

void modify_req_info(string&);

void delete_proxy_info(string&);

int body_size(const string&);

int client_to_server(int, int);


int request_type(const string&);

string header_content(const string&, const string& name);

void port_search(string&, string&, int);

int cache_check(string, cache_cb&);

int client_to_server(int, int, cache_cb&);

int proxy_send(const char*, size_t, int);

void request_resent(connec*);

int proxy_recvheader(connec*);

void http_connect(connec*);

void https_connect(connec*);

void fill_gmttime(char*, time_t);

void add_tag(string&, string, string);

int cache_valid(cache_cb&);

#endif
