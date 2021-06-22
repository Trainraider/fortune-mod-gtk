SHELL = /bin/sh
CC = gcc
CFLAGS =-O2 -march=native -pipe `pkg-config --cflags gtk+-3.0`
.SUFFIXES:
.SUFFIXES: .c .o .h


objects = fortune-gtk.o

fortune-gtk: $(objects)
	$(CC) $(CFLAGS) -o fortune-gtk $(objects) `pkg-config --libs gtk+-3.0`

$(objects) :

.PHONY : clean
clean :
	-rm fortune-gtk $(objects)

.PHONY : debug
debug : $(objects)
	$(CC) $(CFLAGS) -Wall -Wpedantic -o fortune-gtk $(objects) `pkg-config --libs gtk+-3.0`