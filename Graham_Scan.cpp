#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>

#include "Point.h"
#include "Utility.h"

#define newl std::cout << "\n"

struct PolarPoint{
	cg::Point point;
	double r,theta;
};

bool compareTheta(const PolarPoint &a,const PolarPoint &b){
	bool condition1 = (a.theta < b.theta);
	bool condition2 = (a.theta == b.theta);
	bool condition3 = (a.r < b.r);
	return (condition1 or (condition2 and condition3));
}

int main(int argc,char *argv[]){

	//std::cout << std::setprecision(10);
	
	// Read from file
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	
	// Find bottom point in hull
	cg::Point origin(p[0]);
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
		a.r 	= cg::euclideanDistance(p[i],origin);
		a.theta = cg::polarAngle(p[i],origin);
		vect.push_back(a);
	}

//	for(auto q:vect) std::cout<< q.point<<" "<<q.r<<" "<<q.theta<<"\n";
	
	
	//sorting
	std::sort(vect.begin(),vect.end(),compareTheta);
	
//	newl;
	
//	for(auto q:vect){	std::cout<< q.point<<" "<<q.r<<" "<<q.theta<<"\n";	}
	
	
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
	std::stack<cg::Point> stck;
	stck.push(p[0]);
	stck.push(p[1]);
	stck.push(p[2]);
	
	n = p.size();
	for(int k=3;k<n;k++){
		while(true){
			cg::Point t(stck.top());
			stck.pop();
			cg::Point nt(stck.top());
			if(turn_direction(nt,t,p[k])<=0)
				continue;
			else{
				stck.push(t);
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
	
	// write to file
	writePointSet(argv[2],p);
return 0;
}
