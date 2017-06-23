CC = gcc
CFLAGS = -g -Wall
SOURCES = caesar.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = caesar

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
