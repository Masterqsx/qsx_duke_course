1. The proxy in default will open on port 8000
2. You can specify customized port (must larger than 1024) through the first command line argument
3. This proxy could handle https request and http request from client no larger than 8 KB.
example:
  ./proxy # proxy is running on port 8000
  ./proxy 8080 # proxy is running on port 8080
