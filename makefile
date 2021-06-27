SHELL = /bin/sh
CC = gcc
CFLAGS = -march=native -pipe `pkg-config --cflags gtk+-3.0`
.SUFFIXES:
.SUFFIXES: .c .o .h


objects = fortune-gtk.o

fortune-gtk: $(objects)
	$(CC) $(CFLAGS) -O2 -o fortune-gtk $(objects) `pkg-config --libs gtk+-3.0`

$(objects) :

.PHONY : clean
clean :
	-rm fortune-gtk $(objects)

.PHONY : debug
debug : $(objects)
	$(CC) $(CFLAGS) -O0 -g -Wall -Wpedantic -o fortune-gtk $(objects) `pkg-config --libs gtk+-3.0`

.PHONY : format
format :
	clang-format -style="{BasedOnStyle: webkit, IndentWidth: 8}" -i *.{c,h}
