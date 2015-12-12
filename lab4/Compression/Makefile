PROGRAM = Compression
CXX = g++
CXXFLAGS = -fvisibility-inlines-hidden -g -std=c++11

all: $(PROGRAM)
$(PROGRAM): Compression.cc huffman.cpp huffman.h pqueue.h
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) -L. Compression.cc huffman.cpp
clean:
	rm *.o *.tmp Compression -f
