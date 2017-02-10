CPP = g++
CFLAGS = -std=c++11

graham.o: Graham_Scan.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) Graham_Scan.cpp Point.o Utility.o -o graham.o

jarvis.o: Jarvis_March.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) Jarvis_March.cpp Point.o Utility.o -o jarvis.o

Point.o: Point.h Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp

Utility.o: Utility.h Utility.cpp
	$(CPP) $(CFLAGS) -c Utility.cpp

andrew.o: andrews.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) andrews.cpp Point.o Utility.o -o andrew.o
	
clean:
	rm -f *.o *.out
