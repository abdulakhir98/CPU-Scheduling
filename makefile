all: l164265.o assign-2

l164265.o: l164265.cpp
	g++ l164265.cpp -c

assign-2: l164265.o
	g++ l164265.o -o assign-2
