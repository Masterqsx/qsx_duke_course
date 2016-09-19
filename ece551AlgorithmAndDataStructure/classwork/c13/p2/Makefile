TARGET=code
OBJECT=code.o

CC=g++
CFLAGS=-Wall -Werror

$(TARGET):$(OBJECT)
	$(CC) $(CFLAGS) -o $@ -g $^

run:
	./$(TARGET) >answer.txt
