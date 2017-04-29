/** \file
Contains the main function to run triangulation module.
*/
#include <set>
#include <utility>
#include <chrono>

#include "Point.h"
#include "Utility.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"

int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);
	
	std::chrono::steady_clock::time_point time1 = std::chrono::steady_clock::now();
	cg::DCEL D(P);
	std::chrono::steady_clock::time_point time2 = std::chrono::steady_clock::now();
	
	cg::writeEdges(D, argv[2]);	
	
	
	std::chrono::steady_clock::time_point time3 = std::chrono::steady_clock::now();
	cg::make_monotone(D);
	std::chrono::steady_clock::time_point time4 = std::chrono::steady_clock::now();
	std::cout << "Made monotone\n";
	cg::writeEdges(D, argv[3]);
	

	std::chrono::steady_clock::time_point time5 = std::chrono::steady_clock::now();
	cg::triangulate(D);	
	std::chrono::steady_clock::time_point time6 = std::chrono::steady_clock::now();
		std::cout << "Triangulated\n";
	cg::writeEdges(D, argv[4]);
	
	std::cout << "DCEL:\t"  << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() <<" ms\n";
	std::cout << "Mono:\t"  << std::chrono::duration_cast<std::chrono::microseconds>(time4 - time3).count() <<" ms\n";
	std::cout << "Tria:\t"  << std::chrono::duration_cast<std::chrono::microseconds>(time6 - time5).count() <<" ms\n";
	std::cout << "Total:\t" << std::chrono::duration_cast<std::chrono::microseconds>(time2-time1+time4-time3+time6-time5).count() <<" ms\n";	
	return 0;
}


