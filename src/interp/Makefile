CXX = g++
CXXFLAGS = -g -std=c++11

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

all: interp

interp: interp.o 
	$(CXX) -o $@ interp.o 

clean: 
	$(RM) *.o *.gch *.swp .DS_Store interp 
