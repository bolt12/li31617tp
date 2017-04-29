CC = gcc
CC = gcc
CFLAGS = -O2 -Wall -fopenmp -D_GNU_SOURCE -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`
STRUCTS = interface.o linkedListRevisions.o avl.o hashTArt.o hashTContrib.o

program: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) program.c -o program $(LIBS)

interface: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) interface.c -o interface $(LIBS)

test_hashTArt: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) test_hash.c -o test_hash $(LIBS)


avl:
	$(CC) -c -O2 avl.c

hashTContrib:
	$(CC) -c -O2 hashTContrib.c

hashTArt:
	$(CC) -c -O2 hashTArt.c

llist:
	$(CC) -c -O2 linkedListRevisions.c

clean:
	rm -f program test_hash *.o
