CPP = g++
CFLAGS = -std=c++11

test1.o: test1.cpp Point.o Utility.o convex.o
	$(CPP) $(CFLAGS) test1.cpp convex.o Point.o Utility.o -o test1.o
	@echo "\nUSE: python test_convex.py ./test1.o <algo_name> all-txt"
	@echo "Replace <algo_name> with graham/jarvis/andrew\n"
	@echo "USE: ./test1.o <input-file> <output-file> 1|2|3\n"

test2.o: test2.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o convex.o
	$(CPP) $(CFLAGS) test2.cpp Point.o DCEL.o Ymonotone.o tria.o Utility.o Status.o convex.o -o test2.o
	@echo "\nUSE: ./test2.o <Input File> <Output File1> <Output File2> <Output File3>"
	@echo "TO PLOT: python plot_poly.py <Output File1> <Output File2> <Output File3>\n"
	
test3.o : test3.cpp DCEL.o Point.o Ymonotone.o tria.o Utility.o Status.o convex.o
	$(CPP) $(CFLAGS) test3.cpp DCEL.o Point.o Ymonotone.o tria.o Utility.o Status.o convex.o -o test3.o
	@echo "\n./test3.o <input-file> circles.txt"
	@echo "python plot_poly.py out1.txt out2.txt out3.txt &"
	@echo "python plot_delaunay.py out4.txt circles.txt\n"

temp.o : temp.cpp Point.o
	$(CPP) $(CFLAGS) temp.cpp Point.o -o temp.o

tria.o: triangulate.cpp Point.o DCEL.o Utility.o Ymonotone.o convex.o
	$(CPP) $(CFLAGS) -c triangulate.cpp -o tria.o
	
convex.o: ConvexHull.cpp Utility.o Point.o
	$(CPP) $(CFLAGS) -c ConvexHull.cpp -o convex.o

Ymonotone.o: Ymonotone.cpp Point.o DCEL.o Utility.o Status.o
	$(CPP) $(CFLAGS) -c Ymonotone.cpp -o Ymonotone.o

Status.o: Status.cpp Point.o Utility.o
	$(CPP) $(CFLAGS) -c Status.cpp -o Status.o
	
Utility.o: Utility.cpp DCEL.o
	$(CPP) $(CFLAGS) -c Utility.cpp -o Utility.o
	
DCEL.o: DCEL.cpp Point.o
	$(CPP) $(CFLAGS) -c DCEL.cpp -o DCEL.o
	
Point.o: Point.cpp
	$(CPP) $(CFLAGS) -c Point.cpp -o Point.o
	
clean:
	rm -f *.o *.out
