GC=gcc
CFLAGS=-c -Wall
VPATH = ../src
SOURCES=$(shell basename -a `ls ../src/*.c`)
OBJECTS=$(SOURCES:.c=.o)

all: $(OBJECTS) test

test: $(OBJECTS)
	$(CC) $(OBJECTS) -o test

$(OBJECTS): $(SOURCES)

clean:
	rm *.o test
