/** \file
Contains the main function to run the algorithms to find convex hull of a set of points. This program file reads a set of points in the cartesian space from the first command line arguement, computes the Convex Hull using Graham Scan's Algorithm and writes the output to file specified in the second command line arguement. <br>
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
#include <chrono>

#include "Point.h"
#include "Utility.h"
#include "ConvexHull.h"

int main(int argc,char *argv[]){

	std::cout<<std::setprecision(15);
	
	char *input_file = argv[1];			// file to read input points
	char *output_file = argv[2];		// file to write Convex Hull
	int choice = atoi(argv[3]);			// choice to determine which algorithm to use
	std::vector<cg::Point> point_set; 	// contains the input points
	std::vector<cg::Point> ch;			// contains the Convex hull of input points
	
	// Read from file

	cg::readPointSet(input_file,point_set);
	
	std::cout << "Read file successfully\n";
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	switch(choice){
		case 1:	ch = cg::convexHullGrahamScan(point_set);
				std::cout<<"Completed convex hull using Graham's Scan.\n";	
				break;
		case 2: ch = cg::convexHullJarvisMarch(point_set);
				std::cout<<"Completed convex hull using Jarvis March.\n";	
				break;
		case 3: ch = cg::convexHullAndrews(point_set);
				std::cout<<"Completed convex hull using Andrew's Algorithm.\n";	
				break;
		default: std::cerr << "Third agruement should be 1 or 2 or 3\n";
	}

	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	std::cout << "Time taken to compute Convex Hull is = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<" ms" <<std::endl;
	
	// write to file
	cg::writePointSet(output_file,ch);
	std::cout << "File written successfully.\n";
	return 0;
}


