TARGET=q7_1
OBJECT=q7_1.o

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99

$(TARGET):$(OBJECT)
	$(CC) $(CFLAGS) -o $@ -g $^

run:
	./$(TARGET)

clean:
	rm *.o
