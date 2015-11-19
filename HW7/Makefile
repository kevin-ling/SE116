#************************************************************
# Makefile for HomeWork 7
#************************************************************
PROGRAM = HW7
CPP = main.cpp WriteCode.cpp
OBJECTS = WriteCode.o main.o
CPPOPTIONS = -fvisibility-inlines-hidden
CXXFLAGS = -Wall -std=c++11

all: $(PROGRAM)
check: $(PROGRAM)
	@./$(PROGRAM)
$(PROGRAM): $(OBJECTS)
	g++ -o $(PROGRAM) $(OBJECTS)
WriteCode.o: WriteCode.cpp WriteCode.h
	g++ -c $(CPPOPTIONS) WriteCode.cpp
HW6.o: main.cpp WriteCode.cpp WriteCode.h input.h
	g++ -c $(CPPOPTIONS) main.cpp
clean:
	-rm -f *.o *.a $(PROGRAM)
