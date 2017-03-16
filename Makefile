CC=gcc
CFLAGS=-Wall -g `pkg-config --cflags libxml-2.0`
LIBS=`pkg-config --libs libxml-2.0`

install:
	$(CC) $(CFLAGS) program.c -o program $(LIBS)

clean:
	rm -f program
