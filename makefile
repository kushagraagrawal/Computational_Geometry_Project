CPP = g++
CFLAGS = -std=c++11
test.o: Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o test.cpp
	$(CPP) $(CFLAGS) test.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o -o test.o

test_status.o: Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o test_status.cpp
	$(CPP) $(CFLAGS) test_status.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o -o test_status.o

DCEL.o: DCEL.cpp
	$(CPP) $(CFLAGS) -c DCEL.cpp -o DCEL.o
	
Point.o: Point.h Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o

Ymonotone.o: Ymonotone.cpp Ymonotone.h
	$(CPP) $(CFLAGS) -c Ymonotone.cpp -o Ymonotone.o

tria.o: triangulate.cpp triangulate.h
	$(CPP) $(CFLAGS) -c triangulate.cpp -o tria.o
	
Utility.o: Utility.cpp Utility.h
	$(CPP) $(CFLAGS) -c Utility.cpp -o Utility.o
	
Status.o: Status.cpp Status.h
	$(CPP) $(CFLAGS) -c Status.cpp -o Status.o
clean:
	rm -f *.o *.out
