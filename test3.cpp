/** \file
 * File that implements the third assignment of CS F441 - Selected Topics in Computer Science.
 * The problem statement of the assignment is to use the already existing API developed in the previous assignments to create the triangulation of n given points in 2D plane.
 * 
 * */
#include <iostream>
#include <set>
#include <stack>
#include <string.h>
#include <utility>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"
#include "Utility.h"
#include "ConvexHull.h"

int main(int argc, char* argv[]){
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);
	
	if(argv[2]==NULL){
		std::cerr << "Enter normal/del as second arguement\n";
		exit(1);
	}
	if(strcmp(argv[2],"normal")==0){
		cg::DCEL D = cg::triangulatePoints(P);
		cg::writeEdges(D,(char *)"out3.txt");
	}
	else if(strcmp(argv[2],"del")==0){
		cg::DCEL D = delaunay_Triangulation(P);
		std::ofstream file((char *)"circles.txt");

		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		std::cout << "\nFaces:\n";
		for(int i=1;i<D.face_record.size();i++){
			std::vector<int> pid = D.verticesOfFace(i);
			for(auto x:pid) std::cout << x <<" ";
			std::cout << "\n";
			cg::Point A = D.vertex_record[pid[0]].point;
			cg::Point B = D.vertex_record[pid[1]].point;
			cg::Point C = D.vertex_record[pid[2]].point;
			cg::Point centre = cg::circumcentre(A,B,C);
			double radius = cg::euclideanDistance(centre,A);
			file << centre.x << " " << centre.y << " " <<radius << "\n";
		}
	}
	else{
		std::cerr << "Enter normal/del as second arguement\n";
		exit(1);
	}
		
	return 0;
}


