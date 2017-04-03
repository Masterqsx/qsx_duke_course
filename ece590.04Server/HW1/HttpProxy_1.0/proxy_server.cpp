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

proxy_server::proxy_server() {}

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
 if (option == 1) {//start as server
    int yes = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 
    setsockopt(socket_fd, SOL_SOCKET, SO_LINGER, &yes, sizeof(int));
    if (::bind(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen) == -1) {
      perror("Error: cannot bind");
      return -1;
    }
    
 }
  else if (option == 0) {//start as client
    if (connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen) == -1) {
      perror("Error: cannot connect\n");
      return -1;
    }
  }
  freeaddrinfo(host_info_list); 
  return socket_fd;
}

void proxy_server::server_listen() {
  if (listen(socket_fd, 20) == -1) {
    perror("Error: cannot listen\n");
    return;
  }
}

proxy_server::~proxy_server() {
  shutdown(socket_fd, SHUT_RDWR);  
  usleep(10);
  close(socket_fd);
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

void http_connect(connec* c) {
  string hostname, port;

  try{
    hostname = header_content(c->from_client, "Host");
    port_search(hostname, port, 1);
  
    proxy_server p2 = proxy_server();
    if (hostname.empty() || p2.setup_socket(0, hostname.c_str(), port.c_str()) == -1) {
      delete c;
      return;
    }

    modify_req_info(c->from_client);
    delete_proxy_info(c->from_client);

    if (proxy_send(c->from_client.data(), c->from_client.size(), p2.socket_fd) == -1) {
      delete c;
      return;
    }

    client_to_server(p2.socket_fd, c->connec_fd);
  }
  catch (exception& e) {
    cout << string("Error: ") + string(e.what()) << endl;
  }
  delete c;
  return;
}

void https_connect(connec* c) {
  string hostname, port;
  
  proxy_send("HTTP/1.1 200 Connection Established\r\nConnection: close\r\n\r\n", strlen("HTTP/1.1 200 Connection Established\r\nConnection: close\r\n\r\n"), c->connec_fd);
  proxy_server p2 = proxy_server();
  hostname = header_content(c->from_client, "Host");
  port_search(hostname, port, 0);


  modify_req_info(c->from_client);
  if (hostname.empty() || p2.setup_socket(0, hostname.c_str(), port.c_str()) == -1) {
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
  delete c;
  return;
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
