CPP = g++
CFLAGS = -std=c++11

main.o: main.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) main.cpp convex.o Point.o Utility.o -o main.o

convex.o: ConvexHull.h ConvexHull.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) -c ConvexHull.cpp -o convex.o

Point.o: Point.h Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o

Utility.o: Utility.h Utility.cpp
	$(CPP) $(CFLAGS) -c Utility.cpp -o Utility.o

clean:
	rm -f *.o *.out
