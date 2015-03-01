CC = g++
CCFLAGS = -g -std=c++11 -Wall 
INCLUDE_FLAGS = -I ../include/

%.o: %.cpp
	$(CC) -c $(INCLUDE_FLAGS) $(CCFLAGS) $<

all: main

bst: bst.o 
	$(CC) -o $@ bst.o 

debug: debug.o
	$(CC) -o $@ debug.o

interp: interp.o
	$(CC) -o $@ interp.o

main: main.o interp.o debug.o bst.o
	$(CC) -o $@ main.o interp.o debug.o bst.o

clean: 
	$(RM) *.o *.gch *.swp .DS_Store main interp


