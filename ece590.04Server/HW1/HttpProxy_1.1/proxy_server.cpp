#include "proxy.h"

using namespace std;

connec::connec() {
  socket_addr_len = sizeof(socket_addr);
  memset(buffer, '\0', 8000);
}

connec::connec(int fd) {
  socket_addr_len = sizeof(socket_addr);
  memset(buffer, '\0', 8000);
  connec_fd = fd;
}

connec::~connec() {
  shutdown(connec_fd, SHUT_RDWR);
  usleep(10);
  close(this->connec_fd);
}

proxy_server::proxy_server() {
}

int proxy_server::setup_socket(int option, const char* hostname, const char* port) {
  struct addrinfo host_info;
  struct addrinfo* host_info_list = NULL;

  memset(&host_info, 0, sizeof(host_info));

  host_info.ai_family = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  if (option == 1) host_info.ai_flags = AI_PASSIVE;
  
  int status = 0;
  status = getaddrinfo(hostname, port, &host_info, &host_info_list);
  if (status != 0 || host_info_list == NULL) {
    perror("Error: cannot getaddrinfo\n");
    return -1;
  }
  
  socket_fd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
  if (socket_fd == -1) {
    perror("Error: cannot socket\n");
    return -1;
  }
  //connec_list[0].connec_fd = socket_fd;
 if (option == 1) {//start as server
    int yes = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 
    setsockopt(socket_fd, SOL_SOCKET, SO_LINGER, &yes, sizeof(int));
    if (::bind(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen) == -1) {
      perror("Error: cannot bind");
      return -1;
      //abort();
    }
    
 }
  else if (option == 0) {//start as client
    if (connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen) == -1) {
      perror("Error: cannot connect\n");
      return -1;
      //abort();
    }
  }
  freeaddrinfo(host_info_list); 
  return socket_fd;
}

void proxy_server::server_listen() {
  if (listen(socket_fd, 20) == -1) {
    perror("Error: cannot listen\n");
    return;
    //abort();
  }
}

proxy_server::~proxy_server() {
  shutdown(socket_fd, SHUT_RDWR);  
  usleep(10);
  close(socket_fd);
  //for (unsigned i = 0; i < connec_list.size(); i++) close(connec_list[i].connec_fd);
}

connec* proxy_server::server_accept() {
  connec* c = new connec();
  c->connec_fd = accept(this->socket_fd, (sockaddr *)&(c->socket_addr), &(c->socket_addr_len));
  if (c->connec_fd == -1) {
    perror("Error: cannot accept\n");
    delete c;
    return NULL;
  }
  return c;
}


int proxy_recvheader(connec* i) {
  i->from_client.clear();
  while (1) {
    memset(i->buffer, '\0', 8000);
    ssize_t recv_size = 0;
    recv_size = recv(i->connec_fd, i->buffer, 8000, 0);
    if (recv_size <= 0) break;
    i->from_client += i->buffer;
    if (i->from_client.find("\r\n\r\n") != string::npos) break;
  }
  if (i->from_client[0] == ' ')
    i->from_client = i->from_client.substr(i->from_client.find_first_not_of(" "));
  return i->from_client.size();
}

int proxy_send(const char* info, size_t sz, int i) {
  if (::send(i, info, sz, 0) == -1) {
    perror("Error: send mesg fail");
    return -1;
  }
  return 0;
}

int client_to_server(int in, int out) {
  char buffer[8000];
  size_t sz = 0;
  ssize_t flag = 0;
  memset(buffer, '\0', 8000);
  while ((sz = recv(in, buffer, 8000, 0)) > 0) {
    flag = ::send(out, buffer, sz, 0);
    if (flag == -1) {
      perror("Error: send server data back fail");
      return -1;
    }
    memset(buffer, '\0', 8000);
    sz = 0;
  }
  return 0;
}

int client_to_server(int in, int out, cache_cb& ccb) {//0: normal, -1: error, 1: cached
  char buffer[8001];
  size_t sz = 0;
  ssize_t flag = 0;
  int search_header = 1;//1: searching "cache-control", 0: searched, -1: no cahce
  memset(buffer, '\0', 8001);
  while ((sz = recv(in, buffer, 8000, 0)) > 0) {
    if (search_header == 1) {
      send_req_log(ccb.h_value, string(buffer, sz).substr(0, string(buffer, sz).find("\r\n")), ccb.call, 1);
      send_req_log(ccb.h_value, string(buffer, sz).substr(0, string(buffer, sz).find("\r\n")), string(), 2);
      int re = cache_check(string(buffer), ccb);
      if (re == 1) {
        search_header = 0;
        ccb.data.push_back(new char[8000]);
        ccb.siz.push_back(sz);
        for (size_t i = 0;i < sz;i++) ccb.data.back()[i] = buffer[i];
      }
      else if (re == 0) return 1;
      else search_header = -1;//we assume the header check only perform once
    }
    else if (search_header == 0) {
      ccb.data.push_back(new char[8000]);
      ccb.siz.push_back(sz);
      for (size_t i = 0;i < sz;i++) ccb.data.back()[i] = buffer[i];
    }

    flag = ::send(out, buffer, sz, 0);
    if (flag == -1) {
      ccb.max_age = -1;
      perror("Error: send server data back fail");
      return -1;
    }
    memset(buffer, '\0', 8000);
    sz = 0;
  }

  return 0;
}

void* client_to_server_https(void* fd_in) {
  int* fd = (int*) fd_in;
  char buffer[8000];
  size_t sz = 0;
  ssize_t flag = 0;
  memset(buffer, '\0', 8000);
  while ((sz = recv(fd[0], buffer, 8000, 0)) > 0) {
    flag = ::send(fd[1], buffer, sz, 0);
    if (flag == -1) {
      perror("Error: send server data back fail");
      return NULL;
    }
    memset(buffer, '\0', 8000);
    sz = 0;
  }
  return NULL;
}

int request_type(const string& req) {// GET: 1, RETURN: 0, CONNECT: 2, POST: 3, UNKNOWN: -1
  if (req.substr(0, 3) == "GET") return 1;
  else if (req.substr(0, 4) == "HTTP") return 0;
  else if (req.substr(0, 7) == "CONNECT") return 2;
  else if (req.substr(0, 4) == "POST") return 3;
  else return -1;
}

int body_size(const string& header) {//GET, CONNECT: 0, CHUNKED: -1
  int type = request_type(header);
  if (type == 1 || type == 2) return 0;
  else {
    string content_length = header_content(header, "Transfer-Encoding");
    if (content_length.size() > 0 && content_length == "chunked") return -1;
    else {
      content_length = header_content(header, "Content-Length");
      if (content_length.size() > 0) return stoi(content_length);
      else return 0;
    }
  }
}
   
string header_content(const string& req, const string& name) {
  smatch res;
  regex pattern(name + ":(.+?)\r\n", regex_constants::icase);
  regex_search(req, res, pattern);
  if (res.empty()) return string();
  string re = res.str(1);
  if (re[0] == ' ')
    re = re.substr(re.find_first_not_of(' '));
  if (re.back() == ' ')
    re.erase(re.find_last_not_of(' ') + 1);
  return re;
}

void port_search(string& host, string& port, int is_http) {
  if (host.find_last_of(':') != string::npos) {
    port = host.substr(host.find_last_of(':') + 1);
    host.erase(host.find_last_of(':'));
  }
  else port = (is_http == 1 ? "80" : "443");
}

void delete_proxy_info(string& req) {
  string host = header_content(req, "Host");
  req.erase(req.find("http://" + host), host.size() + 7);
  regex pattern("(.*)Proxy-Connection: (.+?)(\r\n.*?)", regex_constants::icase);
  req = regex_replace(req, pattern, string("$1Connection: $2$3"));
}

void modify_req_info(string& req) {
  regex pattern2("(.*Connection: )(.+?)(\r\n.*?)", regex_constants::icase);
  req = regex_replace(req, pattern2, string("$1close$3"));
}

void recv_req_log(size_t id, string req_id, string hostname) {
  timespec wait;
  wait.tv_sec = 2;
  pthread_mutex_timedlock(&lock, &wait);
  time_t res = time(NULL);
  cout << id << ": \"" + req_id + "\" from " + hostname + " @ " + string(asctime(gmtime(&res))) << endl;
  pthread_mutex_unlock(&lock);
}

void cache_log(size_t id, size_t option, string expire) {
  timespec wait;
  wait.tv_sec = 2;
  pthread_mutex_timedlock(&lock, &wait);
  if (option == 0)
    cout << id << ": not in cache" << endl;
  else if (option == 1)
    cout << id << ": in cache, but expired at" + expire << endl;
  else if (option == 2)
    cout << id << ": in cache, requires validation" << endl;
  else if (option == 3)
    cout << id << ": in cache, valid" << endl;
  pthread_mutex_unlock(&lock);
}

void send_req_log(size_t id, string req_id, string hostname, size_t option) {
  timespec wait;
  wait.tv_sec = 2;
  pthread_mutex_timedlock(&lock, &wait);
  if (option == 0)
    cout << id << ": Requesting " + req_id + " from " + hostname << endl;
  else if (option == 1)
    cout << id << ": Received " + req_id + " from " + hostname << endl;
  else if (option == 2)
    cout << id << ": Responding " + req_id << endl;
  else if (option == 3)
    cout << id << ": Tunnel Close " << endl;
  pthread_mutex_unlock(&lock);
}

void cache_check_log(size_t id, string reason, size_t option) {
  timespec wait;
  wait.tv_sec = 2;
  pthread_mutex_timedlock(&lock, &wait);
  if (option == 0)
    cout << id <<": not cacheable because " + reason << endl;
  else if (option == 1)
    cout << id <<": cached, expired at " + reason << endl;
  else if (option == 2)
    cout << id <<": cached, but requires re-validation" << endl;
  pthread_mutex_unlock(&lock);
}

void http_connect(connec* c) {
  string hostname, port, req_id;

  req_id = c->from_client.substr(0, c->from_client.find("\r\n"));
  cache_cb* ccb = new cache_cb();
  try{
  hash<string> h;
  ccb->h_value = h(req_id);
  cache_cb* curr = NULL;

  hostname = header_content(c->from_client, "Host");
  port_search(hostname, port, 1);
  
  ccb->call = hostname;
  if (!req_id.empty() && !hostname.empty())
    recv_req_log(ccb->h_value, req_id, hostname);

  pthread_mutex_lock(&rwlock_vector[ccb->h_value % N]);
  if (cache_valid(*ccb) == 1) {
    size_t i = 0;
    curr = caching[ccb->h_value % N];
    for (;i < (curr->data.size());i++) {
      if (proxy_send(curr->data[i], curr->siz[i], c->connec_fd) == -1) break;
    }
    if (i != curr->data.size()) {
      delete caching[ccb->h_value % N];
      caching[ccb->h_value % N] = NULL;
      cache_log(ccb->h_value, 2, string());
    }
    else {
      cache_log(ccb->h_value, 3, string());
      delete c;
      pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
      delete ccb;
      return;
    }
  }
  pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);

  proxy_server p2 = proxy_server();
  if (hostname.empty() || p2.setup_socket(0, hostname.c_str(), port.c_str()) == -1) {
    delete ccb;
    delete c;
    return;
  }

  modify_req_info(c->from_client);
  delete_proxy_info(c->from_client);
  
  pthread_mutex_lock(&rwlock_vector[ccb->h_value % N]);
  curr = caching[ccb->h_value % N];
  if (curr != NULL && curr->h_value == ccb->h_value) {
    add_tag(c->from_client, "If-None-Match", curr->e_tag);
    char buf[32];
    fill_gmttime(buf, curr->last_modify);
    add_tag(c->from_client, "If-Modified-Since", buf);
  }
  pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
  if (proxy_send(c->from_client.data(), c->from_client.size(), p2.socket_fd) == -1) {
    delete ccb;
    delete c;
    return;
  }
  send_req_log(ccb->h_value, req_id, hostname, 0);

  pthread_mutex_lock(&rwlock_vector[ccb->h_value % N]);
  if (client_to_server(p2.socket_fd, c->connec_fd, *ccb) == 1) {
    curr = caching[ccb->h_value % N];
    curr->last_modify = time(NULL); // update after validation
    size_t i = 0;
    for (;i < (curr->data.size());i++) {
      if (proxy_send(curr->data[i], curr->siz[i], c->connec_fd) == -1) break;
    }
    cache_log(ccb->h_value, 2, string());
    delete c;
    pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
    delete ccb;
    return;
  }
  else if (ccb->max_age != -1) {
    if (caching[ccb->h_value % N] != NULL) delete caching[ccb->h_value % N];
    caching[ccb->h_value % N] = ccb;
    pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
  }
  else {
    pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
    delete ccb;
  }
  }
  catch (exception& e) {
    pthread_mutex_unlock(&rwlock_vector[ccb->h_value % N]);
    delete ccb;
    cout << string("Error: ") + string(e.what()) << endl;
  }
  delete c;
  return;
}

void https_connect(connec* c) {
  string hostname, port, req_id;
  
  proxy_send("HTTP/1.1 200 Connection Established\r\nConnection: close\r\n\r\n", strlen("HTTP/1.1 200 Connection Established\r\nConnection: close\r\n\r\n"), c->connec_fd);
  proxy_server p2 = proxy_server();
  hostname = header_content(c->from_client, "Host");
  port_search(hostname, port, 0);

  hash<string> h;
  req_id = c->from_client.substr(0, c->from_client.find("\r\n"));
  recv_req_log(h(req_id), req_id, hostname);
  send_req_log(h(req_id), "HTTP/1.1 200 Connection Established", string(), 2); 

  modify_req_info(c->from_client);
  if (hostname.empty() || p2.setup_socket(0, hostname.c_str(), port.c_str()) == -1) {
    send_req_log(h(req_id), string(), string(), 3);
    delete c;
    return;
  }
  pthread_t tid0, tid1;
  int fd0[2] = {c->connec_fd, p2.socket_fd};
  int fd1[2] = {p2.socket_fd, c->connec_fd};
  pthread_create(&tid0, NULL, client_to_server_https, (void *)fd0);
  pthread_create(&tid1, NULL, client_to_server_https, (void *)fd1);
  pthread_join(tid0, NULL);
  pthread_join(tid1, NULL);
  send_req_log(h(req_id), string(), string(), 3);
  delete c;
  return;
}

void fill_gmttime(char* buf, time_t t) {
  tm *tmp;
  tmp = gmtime(&t);
  if (strftime(buf, 32, "%a, %e %b %Y %X %Z", tmp) == 0) perror("Buffer for fill GMT time is insufficient");
}

cache_cb::cache_cb(): max_age(-1) {}

cache_cb::cache_cb(double max_age_in, time_t ctime): max_age(max_age_in), last_modify(ctime){}

cache_cb::~cache_cb() {
  for (char* p : data) delete [] p;
}

int cache_valid(cache_cb& ccb) {//not valid: -1, valid 1
  if (caching[ccb.h_value % N] != NULL && caching[ccb.h_value % N]->h_value == ccb.h_value && difftime(time(NULL), caching[ccb.h_value % N]->last_modify) < caching[ccb.h_value % N]->max_age) return 1;
  return -1;
}
    
int cache_check(string req, cache_cb& ccb) {//not cache: -1, cache 1, 304 0
  if (req.find("HTTP/1.1 304 Not Modified\r\n") != string::npos && caching[ccb.h_value % N] != NULL && caching[ccb.h_value % N]->h_value == ccb.h_value) { 
    cache_check_log(ccb.h_value, "Not 200", 0);
    return 0;
  }

  if (req.find("HTTP/1.1 200 OK\r\n") == string::npos) {
    cache_check_log(ccb.h_value, "Not 200", 0);  
    return -1;
  }

  string cache_info = header_content(req, "Cache-Control");
  if (cache_info.empty()) {
    cache_check_log(ccb.h_value, "No Cache-Control", 0);
    return -1;
  }

  if (cache_info.find("must-revalidate") != string::npos) {
    cache_check_log(ccb.h_value, string(), 2);
    ccb.e_tag = header_content(req, "Etag");
    ccb.max_age = 0;
    ccb.last_modify = time(NULL);
    return 1;
  }

  if (cache_info.find("max-age") != string::npos) {
    ccb.e_tag = header_content(req, "Etag");
    ccb.max_age = (double)stoi(cache_info.substr(cache_info.find('=') + 1));
    ccb.last_modify = time(NULL);
    time_t res = time(NULL);
    res += ccb.max_age;
    cache_check_log(ccb.h_value, string(asctime(gmtime(&res))), 1);
    return 1;
  }
  return -1;
}

void add_tag(string& req, string name, string value) {
  if (name.empty() || value.empty()) return;
  if (header_content(req, name).size() > 0) {
    regex pattern("(.*" + name + ": )(.+?)(\r\n.*?)", regex_constants::icase);
    req = regex_replace(req, pattern, string("$1" + value +"$3"));
  }
  else {
    regex pattern("(.*Host: .+?\r\n)(.*?)", regex_constants::icase);
    req = regex_replace(req, pattern, string("$1" + name + ": " + value + "\r\n$2"));
  }
}
