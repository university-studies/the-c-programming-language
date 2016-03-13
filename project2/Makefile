# Encoding:    utf8
# File:        Makefile
# Compiled:    gcc 4.4
# Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
# Faculty:     FIT VUTBR
# Project:     DU2/b for IJC
# Date:        6.4.2011

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall 

CPP=c++
CPPFLAGS=-std=c++98 -pedantic -Wall  

OBJECTS=hash_function.o htable_init.o htable_lookup.o htable_clear.o htable_free.o htable_begin.o htable_end.o htable_iter_next.o
###############################################

all: tail tail2 wordcount wordcount-dynamic 

#tail tail2
################################################
tail.o:tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o

tail:tail.o
	$(CC) $(CFLAGS) tail.o -o tail


tail2.o:tail2.cc
	$(CPP) $(CPPFLAGS) -c tail2.cc -o tail2.o

tail2:tail2.o
	$(CPP) $(CPPFLAGS) tail2.o -o tail2


#fPIC
##########################################################
hash_function.o:hash_function.c htable.h
	$(CC) $(CFLAGS) -c -fPIC hash_function.c -o hash_function.o
htable_init.o:htable_init.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_init.c -o htable_init.o
htable_lookup.o:htable_lookup.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_lookup.c -o htable_lookup.o
htable_clear.o:htable_clear.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_clear.c -o htable_clear.o
htable_free.o:htable_free.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_free.c -o htable_free.o
htable_begin.o:htable_begin.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_begin.c -o htable_begin.o
htable_end.o:htable_end.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_end.c -o htable_end.o
htable_iter_next.o:htable_iter_next.c htable.h 
	$(CC) $(CFLAGS) -c -fPIC htable_iter_next.c -o htable_iter_next.o


#io.o wordcount.o
##########################################################
wordcount.o:wordcount.c io.h htable.h
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o
io.o:io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o


#Kniznice
##########################################################
#staticka kniznica
htable.a: $(OBJECTS)
	ar crs htable.a $(OBJECTS)

#dynamicka kniznica
htable.so:$(OBJECTS)
	$(CC) $(CFLAGS) -shared  $(OBJECTS) -o htable.so 


#wordcount wordcount-dynamic
##########################################################

wordcount: wordcount.o io.o htable.a
	$(CC) $(CFLAGS) -static wordcount.o io.o htable.a -o wordcount

wordcount-dynamic: wordcount.o io.o htable.so
	$(CC) $(CFLAGS) wordcount.o io.o htable.so -o wordcount-dynamic


#clean vymaze .o subory
##########################################################
clean:
	rm -f *.o
	
pack:
	zip xloffa00.zip *.c *.cc *.h Makefile
