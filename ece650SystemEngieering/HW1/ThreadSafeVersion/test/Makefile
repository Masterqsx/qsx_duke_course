CC=gcc
CFLAGS=-O3 -fPIC -m32
WDIR=../

all: thread_test thread_test_malloc_free

thread_test: thread_test.c
	$(CC) $(CFLAGS) -I$(WDIR) -L$(WDIR) -Wl,-rpath=$(WDIR) -o $@ -g thread_test.c -lmymalloc -lpthread

thread_test_malloc_free: thread_test_malloc_free.c
	$(CC) $(CFLAGS) -I$(WDIR) -L$(WDIR) -Wl,-rpath=$(WDIR) -o $@ -g thread_test.c -lmymalloc -lpthread


clean:
	rm -f *~ *.o thread_test thread_test_malloc_free

clobber:
	rm -f *~ *.o
