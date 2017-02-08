#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>

#include "Point.h"
#include "Utility.h"

namespace cg{
std::vector<Point> convex_hull_graham(const std::vector<Point> & S){
	// Copy S into new vector p
	std::vector<Point> p = S;
	
	// Find bottom most  point in p
	Point origin(p[0]);
	for(int i=1;i<p.size();i++){
		if(p[i] < origin ){
			origin = p[i];
		}
	}
	
	std::vector<PolarPoint> vect;
	// Find polar coordinates
	for(int i=0;i<p.size();i++){
		PolarPoint a;
		a.point = p[i];
		a.r 	= euclideanDistance(p[i],origin);
		a.theta = polarAngle(p[i],origin);
		vect.push_back(a);
	}
	
	//sorting
	std::sort(vect.begin(),vect.end(),compareTheta);
		
	int n = vect.size();
	bool valid[n];
	std::fill(valid,valid+n,true);
	
	// Check for invalid points in vect
	for(int i=1;i<n;i++){
		if(vect[i].r==0 or (i+1<n and vect[i].theta==vect[i+1].theta)){
			valid[i]=false;
		}
	}
	
	// Copy valid points back into p
	p.clear();
	for(int i=0;i<vect.size();i++){
		if(valid[i]){
			p.push_back(vect[i].point);
		}
	}
	
	// Find convex hull	
	std::stack<Point> stck;
	stck.push(p[0]);
	stck.push(p[1]);
	stck.push(p[2]);
	
	n = p.size();
	for(int k=3;k<n;k++){
		while(true){
			Point tp(stck.top());
			stck.pop();
			Point next_tp(stck.top());
			if(turn_direction(next_tp,tp,p[k])<=0)
				continue;
			else{
				stck.push(tp);
				break;
			}
		}
		stck.push(p[k]);
	}

	// Transfer from stack to vector	
	p.clear();
	while(!stck.empty()){
		p.push_back(stck.top());
		stck.pop();
	}
	return p;
}
}



int main(int argc,char *argv[]){

	// Read from file
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	std::cout << "Read File successfully.\n";
	
	std::vector<cg::Point> ch = cg::convex_hull_graham(p);
	std::cout << "Computed convex hull using Graham Scan.\n";
	
	// write to file
	cg::writePointSet(argv[2],ch);
	std::cout << "File written successfully.\n";
	return 0;
}
