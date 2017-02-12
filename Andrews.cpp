/** \file
Contains the main function to run Andrew's Algorithm. 
This program file reads a set of points in the cartesian space from the first command line arguement,
computes the Convex Hull using Andrew's Algorithm and writes the output to file specified in the second command line arguement. <br>
To run, execute the following command in the directory containing the source code using the terminal:-
\code
$ make andrews.o input_file.txt output_file.txt
\endcode

<b>Note:</b> It creates a new file if <b><em> output_file.txt </em></b> does not exist, or overwrites the existing file.

*/

#include "Point.h"
#include "Utility.h"
#include "ConvexHull.h"
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>
#include <chrono>


int main(int argc, char* argv[]){

	std::cout<<std::setprecision(15);
	
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	std::cout<<"File read successfully.\n";
	
	// to calculate time taken
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::vector<cg::Point> ch = cg::andrews(p);
	std::cout<<"Completed convex hull using Andrew's.\n";
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	std::cout << "Time taken to compute Convex Hull is = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<"ms" <<std::endl;
	
	
	//write to file
	cg::writePointSet(argv[2],ch);
	std::cout<<"File written successfully.\n";
	
	return 0;
}

