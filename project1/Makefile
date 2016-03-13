#Encoding utf-8
#makefile pre predmet IJC DU1
#Riesenie IJC-DU1, priklad 2.3.2011
#Autor: Pavol Loffay, xloffa00, FIT Brno

CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -lm 
CFLAGS_D=-std=c99 -Wall -pedantic -lm -DUSE_INLINE 


all:enumtest prvocisla prvocisla-inline

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

enum.o: enum.c enum.h error.h
	$(CC) $(CFLAGS) -c enum.c -o enum.o

enumtest.o: enumtest.c error.h enum.h
	$(CC) $(CFLAGS) -c enumtest.c -o enumtest.o

enumtest: enum.o error.o enumtest.o
	$(CC) $(CFLAGS) enum.o error.o enumtest.o -o enumtest



prvocisla.o: prvocisla.c error.h
	$(CC) $(CFLAGS) -c prvocisla.c -o prvocisla.o

prvocisla: error.o prvocisla.o
	$(CC) $(CFLAGS) error.o prvocisla.o -o prvocisla



prvocisla-inline.o: prvocisla.c error.h
	$(CC) $(CFLAGS_D) -c prvocisla.c -o prvocisla-inline.o

prvocisla-inline: error.o prvocisla-inline.o
	$(CC) $(CFLAGS_D) error.o prvocisla-inline.o -o prvocisla-inline


clean:
	-rm -f error.o enum.o enumtest.o prvocisla.o prvocisla-inline.o
