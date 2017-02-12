/** \file
Contains the main function to run Graham Scan's Algorithm. This program file reads a set of points in the cartesian space from the first command line arguement, computes the Convex Hull using Graham Scan's Algorithm and writes the output to file specified in the second command line arguement. <br>
To run, execute the following command in the directory containing the source code using the terminal:-
\code
$ make graham.o input_file.txt output_file.txt
\endcode

<b>Note:</b> It creates a new file if <b><em> output_file.txt </em></b> does not exist, or overwrites the existing file.

*/

#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>

#include "Point.h"
#include "Utility.h"
#include "ConvexHull.h"

int main(int argc,char *argv[]){

	// Read from file
	std::vector<cg::Point> p;
	
	clock_t beg = clock();
	cg::readPointSet(argv[1],p);
	
	std::cout << "Read File successfully in " << (float)(clock()-beg)/CLOCKS_PER_SEC << "\n";
	
	beg = clock();
	std::vector<cg::Point> ch = cg::convexHullGrahamScan(p);
	std::cout << "Computed convex hull using Graham Scan in " << (float)(clock()-beg)/CLOCKS_PER_SEC << "\n";
	
	// write to file
	cg::writePointSet(argv[2],ch);
	std::cout << "File written successfully.\n";
	return 0;
}


