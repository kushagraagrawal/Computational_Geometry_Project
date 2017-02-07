#include<vector>
#include<iostream>
#include <iomanip>
#include "Point.h"
#include "Utility.h"

const double INF = 1e10;

namespace cg{

struct PolarPoint{
	Point point;
	double r,theta;
};

std::vector<Point> convex_hull_jarvis(const std::vector<Point>& S){
	std::vector<Point> ch;
	
	//Ignore Empty point space
	if(S.size() == 0)
		return ch;
	
	//Deal with size = 2,3
	
	//Determine Initial Origin
	int k0, k;
	double min_y = INF;
	for(int i = 0; i < S.size(); i++){
		if(S[i].y < min_y){
			k0 = i;
			min_y = S[i].y;
		}
	}
	k = k0;
	//std::cout << k0 << std::endl;
	double theta0 = 0.0;
	int n=7;
	do{
		ch.push_back(S[k]);
		int j;
		double theta, r, theta_min = INF, r_min = INF;
		for(int i = 0; i < S.size(); i++){
			if(i != k){
				theta = fmod(polarAngle(S[i], *(ch.rbegin())) - theta0 + 360.0, 360.0);
				r = euclideanDistance(S[i], *(ch.rbegin()));
				if(theta < theta_min){
					theta_min = theta;
					r_min = r;
					j = i;
				} else if(theta == theta_min){
					if(r < r_min){
						r_min = r;
						j = i;
					}
				}
			}
		}	
		//std::cout << j << std::endl;
		k = j;
		theta0 = polarAngle(*(ch.rbegin()), *(ch.rbegin()+1));
	} while(k!=k0);
	return ch;
}

}

int main(int argc,char *argv[]){

	std::cout << std::setprecision(15);
	
	// Read from file
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	std::cout << "Read file successfully.\n";
	
	std::vector<cg::Point> ch = cg::convex_hull_jarvis(p);
	std::cout << "Computed convex hull using Jarvis March.\n";
	
	// write to file
	cg::writePointSet(argv[2],ch);
	std::cout << "File written successfully.\n";
}
