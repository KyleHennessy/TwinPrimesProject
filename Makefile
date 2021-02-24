#Kyle Hennessy 12/11/2020
#Makefile
#Contains commands to compile project

CC=g++
CFLAGS= -std=c++11 -fopenmp

#This rule says that each .o file depends on a cpp file of same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: finalversion.o
	$(CC) -o thefinalversion finalversion.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#deletes all .o files
CLEAN:
	rm *.o
