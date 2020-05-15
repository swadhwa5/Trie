CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

all : cTreeTest tTreeTest

cTreeTest: CTreeTest.o CTree.o
	$(CC) -o cTreeTest CTreeTest.o CTree.o
CTreeTest.o: CTreeTest.cpp CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp
CTree.o: CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTree.cpp

tTreeTest: TTreeTest.o 
	$(CC) -o tTreeTest TTreeTest.o 
TTreeTest.o: TTreeTest.cpp Tree.inc Tree.h
	$(CC) $(CFLAGS) -c TTreeTest.cpp 

clean:
	rm -f *.o cTreeTest tTreeTest
