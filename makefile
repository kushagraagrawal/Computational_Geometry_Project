CPP = g++
CFLAGS = -std=c++11

test1.o: test1.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) test1.cpp convex.o Point.o Utility.o -o test1.o

test2.o: test2.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o 
	$(CPP) $(CFLAGS) test2.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o -o test2.o
	
test3.o : test3.cpp DCEL.o Point.o Ymonotone.o tria.o Utility.o Status.o convex.o
	$(CPP) $(CFLAGS) test3.cpp DCEL.o Point.o Ymonotone.o tria.o Utility.o Status.o convex.o -o test3.o
	
convex.o: ConvexHull.cpp Utility.o Point.o
	$(CPP) $(CFLAGS) -c ConvexHull.cpp -o convex.o

tria.o: triangulate.cpp Point.o DCEL.o Utility.o Ymonotone.o
	$(CPP) $(CFLAGS) -c triangulate.cpp -o tria.o
	
Ymonotone.o: Ymonotone.cpp Point.o DCEL.o Utility.o Status.o
	$(CPP) $(CFLAGS) -c Ymonotone.cpp -o Ymonotone.o

Status.o: Status.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) -c Status.cpp -o Status.o
	
Utility.o: Utility.cpp Point.o DCEL.o
	$(CPP) $(CFLAGS) -c Utility.cpp -o Utility.o
	
DCEL.o: DCEL.cpp Point.o
	$(CPP) $(CFLAGS) -c DCEL.cpp -o DCEL.o
	
Point.o: Point.h
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o
	
clean:
	rm -f *.o *.out
