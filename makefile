CPP = g++
CFLAGS = -std=c++11

graham.o: Graham_Scan.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) Graham_Scan.cpp convex.o Point.o Utility.o -o graham.o

jarvis.o: Jarvis_March.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) Jarvis_March.cpp Point.o Utility.o convex.o -o jarvis.o

andrews.o: Andrews.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) Andrews.cpp convex.o Point.o Utility.o -o andrews.o

convex.o: ConvexHull.h ConvexHull.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) -c ConvexHull.cpp -o convex.o

Point.o: Point.h Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o

Utility.o: Utility.h Utility.cpp
	$(CPP) $(CFLAGS) -c Utility.cpp -o Utility.o

clean:
	rm -f *.o *.out
