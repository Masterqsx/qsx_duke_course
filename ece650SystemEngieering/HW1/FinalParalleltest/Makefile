all:
	gcc -O3 -fPIC -m32 -pg -std=gnu99 -Wno-format -o libmymalloc.so -shared -g my_malloc.c -lpthread

clean:
	rm ./*.so
