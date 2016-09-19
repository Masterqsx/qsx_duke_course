TARGET = course1.7
SRCS = course1.7.cpp
OBJS = $(SRCS:.c=.o)
CC = g++
$(TARGET):$(OBJS)
	$(CC) -o $@ $^
run:
	./$(TARGET)
clean:
	rm $(TARGET)
