#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>

#include "Point.h"
#include "Utility.h"
#include "ConvexHull.h"

int main(int argc,char *argv[]){

	std::cout << std::setprecision(15);
	
	// Read from file
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	std::cout << "Read file successfully.\n";
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	std::vector<cg::Point> ch = cg::convexHullJarvisMarch(p);
	
	std::cout<<"Completed convex hull using Jarvis March.\n";
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	std::cout << "Time taken to compute Convex Hull is = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"ms" <<std::endl;
	
	// write to file
	cg::writePointSet(argv[2],ch);
	std::cout << "File written successfully.\n";
}
