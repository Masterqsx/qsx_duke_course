CC=g++
CFLAGS=-Wall -static-libstdc++ -std=c++11 -g
SOURCE2=*.cpp

all: clean proxy

proxy:
		$(CC) $(CFLAGS)  $(SOURCE2) -o proxy -lpthread

clean:
	  rm -rf *.o *.~ proxy *.dSYM
