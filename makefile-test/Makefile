GC=gcc
CFLAGS=-c -Wall
SRCDIR=src
OBJDIR=obj
OBJECTS=$(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(shell basename -a `ls src/*.c`)))
TARGET := test
all: $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
