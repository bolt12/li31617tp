CC = gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`
STRUCTS = linkedListRevisions.o hashTArt.o hashTContrib.o

program: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) program.c -o program $(LIBS)

interface: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) interface.c -o interface $(LIBS)

test_hashTArt: $(STRUCTS)
	$(CC) $(CFLAGS) $(STRUCTS) test_hash.c -o test_hash $(LIBS)

hashTArt:
	$(CC) -c hashTArt.c

hashTContrib:
	$(CC) -c hashTContrib.c

llist:
	$(CC) -c linkedListRevisions.c

clean:
	rm -f program test_hash *.o
