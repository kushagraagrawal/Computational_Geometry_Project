#include "Point.h"
#include "Utility.h"
#include<vector>
#include<iostream>
#include<list>
#include<algorithm>
#include<iomanip>
#include<chrono>

namespace cg{
	
	// lambda function for sort function
	bool compareXY(const Point& a, const Point& b){
		bool condition1 = (a.x > b.x);
		bool condition2 = (a.x == b.x);
		bool condition3 = (a.y > b.y);
		return (condition1 or(condition2 and condition3));
	}

	std::vector<Point> andrews(const std::vector<Point>& point_set){

		int n = point_set.size();
		std::vector<Point> point_set_sorted = point_set;
		
		//sorting on the basis of x-coordinate, if they are equal, sorted on the basis of y-coordinate
		std::sort(point_set_sorted.begin(),point_set_sorted.end(),compareXY);
		
		/*
		 * Declaration of the required vectors for the algorithm, Lupper, Llower and L
		 * */
		std::vector<Point> lup;
		std::vector<Point> ldown;
		
		
		 /*
		  * Pushing to Lupper now
		  * */
		 lup.push_back(point_set_sorted[0]);
		 lup.push_back(point_set_sorted[1]);
		 
		 for(int i=2;i<n;i++){
			 
			 lup.push_back(point_set_sorted[i]);
			 
			 while(lup.size() > 2){
				/*
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 * */
				if(turn_direction(*(lup.rbegin()),*(lup.rbegin()+1),*(lup.rbegin()+2))!= -1){
					/*
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 * */
							
							lup.erase(lup.end() -2);
				}
				else
					break;
			 }
		 }
		 /*
		  * Pushing to Ldown now
		  * */
		ldown.push_back(point_set_sorted[n-1]);
		ldown.push_back(point_set_sorted[n-2]);
		for(int i=n-3;i>=0;i--){
			ldown.push_back(point_set_sorted[i]);
			while(ldown.size() > 2){
				/*
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 * */
				if(turn_direction(*(ldown.rbegin()),*(ldown.rbegin()+1),*(ldown.rbegin()+2))!= -1){
					/*
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 * */
					ldown.erase(ldown.end() -2);
				}
				else
					break;
			}
		}
		/*
		 * To avoid duplicacy with Lupper, the first and the last element of Ldown will be deleted.
		 * */
		ldown.erase(ldown.begin());
		ldown.pop_back();		
		lup.insert(std::end(lup), std::begin(ldown),std::end(ldown));
		return lup;
	}	
}

int main(int argc, char* argv[]){

	std::cout<<std::setprecision(15);
	
	std::vector<cg::Point> p;
	cg::readPointSet(argv[1],p);
	std::cout<<"File read successfully.\n";
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::vector<cg::Point> ch = cg::andrews(p);
	// to calculate time taken
	std::cout<<"Completed convex hull using Andrew's.\n";
	std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() <<std::endl;
	
	cg::writePointSet(argv[2],ch);
	std::cout<<"File written successfully.\n";
	
}

