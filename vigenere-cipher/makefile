CC = gcc
CFLAGS = -g -Wall
SOURCES = vigenere.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = vigenere

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
