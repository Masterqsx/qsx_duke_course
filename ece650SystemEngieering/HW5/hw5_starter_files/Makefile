CC=gcc
CFLAGS=-O3 -std=gnu99
EXTRAFLAGS=`mysql_config --cflags --libs`

all: test

test: main.c exerciser.h exerciser.c query_funcs.h query_funcs.c
	$(CC) $(CFLAGS) -o test main.c exerciser.c query_funcs.c $(EXTRAFLAGS)

clean:
	rm -f *~ *.o test

clobber:
	rm -f *~ *.o
