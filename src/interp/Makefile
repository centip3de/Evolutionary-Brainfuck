CC = g++
CCFLAGS = -g -std=c++11
INCLUDE_FLAGS = -I ../../include/

%.o: %.cpp
	$(CC) -c $(INCLUDE_FLAGS) $(CCFLAGS) $<

all: interp

interp: interp.o 
	$(CC) -o $@ interp.o 

clean: 
	$(RM) *.o *.gch *.swp .DS_Store interp 

