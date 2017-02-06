CPP = g++
CFLAGS = -std=c++11
graham.o: Graham_Scan.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) Graham_Scan.cpp Point.o Utility.o -o graham.o
	./graham.o data.txt output.txt
		
Point.o: Point.h Point.cpp
#	$(CPP) $(CFLAGS) Point.h
	$(CPP) $(CFLAGS) -c Point.cpp

Utility.o: Utility.h Utility.cpp
#	$(CPP) $(CFLAGS) Utility.h
	$(CPP) $(CFLAGS) -c Utility.cpp
	
clean:
	rm -f *.o *.out
