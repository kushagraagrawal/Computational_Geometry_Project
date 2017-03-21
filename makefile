CPP = g++
CFLAGS = -std=c++11

test.o: Point.o DCEL.o test.cpp
	$(CPP) $(CFLAGS) test.cpp Point.o DCEL.o -o test.o

DCEL.o: DCEL.cpp
	$(CPP) $(CFLAGS) -c DCEL.cpp -o DCEL.o
	
Point.o: Point.h Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o

clean:
	rm -f *.o *.out
