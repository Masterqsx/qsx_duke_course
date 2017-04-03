CC=g++
CFLAGS=-Wall -static-libstdc++ -std=c++11 -g
#SOURCE1=socket_client.cpp
SOURCE2=*.cpp

all: clean proxy

#client:
#	  $(CC) $(CFLAGS) $(SOURCE1) -o client

proxy:
		$(CC) $(CFLAGS)  $(SOURCE2) -o proxy -lpthread

clean:
	  rm -rf *.o *.~ proxy *.dSYM
