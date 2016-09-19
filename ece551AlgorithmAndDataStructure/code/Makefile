TARGET=midterm
OBJECT=midterm.o

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99

$(TARGET):$(OBJECT)
	$(CC) $(CFLAGS) -o $@ -g $^

run:
	./$(TARGET)

clean:
	rm *.o
