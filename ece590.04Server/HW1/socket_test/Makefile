CC=g++
CFLAGS=-Werror -Wall -std=c++11 -g
SOURCE1=socket_client.cpp
SOURCE2=socket_server.cpp

all: client server

client:
	  $(CC) $(CFLAGS) $(SOURCE1) -o client

server:
		$(CC) $(CFLAGS) $(SOURCE2) -o server

clean:
	  rm -rf *.o *.~ client server *.dSYM
