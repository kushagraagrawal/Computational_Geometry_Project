#include "Point.h"
#include "Utility.h"
#include "kernel.h"
#include <iostream>
#include <vector>

int main(int argc,char *argv[]) {
	
	std::vector<cg::Point> P;
	if(argv[1]==NULL){
		std::cerr << "Input file missing\n";
		exit(1);
	}
	else{
		cg::readPointSet(argv[1], P);
	}
	
	auto Q = cg::construct_kernel(P);
	for(auto it = Q.begin(); it != Q.end(); it++)
		std::cout << *it << std::endl;
	if(argv[2]==NULL){
		std::cerr << "Output file missing\n";
		exit(1);
	}
	else{
		cg::writePointSet(argv[2], Q);
	}
	return 0;
}


