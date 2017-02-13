#include "ConvexHull.h"
#include <vector>
#include <algorithm>


namespace cg{
	/**
	* Graham Scan's Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order.
	*/
	std::vector<Point> convexHullGrahamScan(const std::vector<Point> & points){
	
		// Copy points vector into new vector temp
		// temp will contain the Convex Hull of points vector
		std::vector<Point> temp = points;
	
		// Find bottommost point in temp_points
		Point origin( temp[0] );
		
		for(int i=1 ; i<temp.size() ; i++){
			if( bottomOrLeft( temp[i], origin) ){
				origin = temp[i];
			}
		}
	
		// Store the corresponding polar coordinates of the points in temp in a new vector	
		std::vector<PolarPoint> vect;
		
		// Find polar coordinates
		for(int i=0 ; i<temp.size() ; i++){
			PolarPoint a;
			a.point = temp[i];
			a.r 	= euclideanDistance(temp[i], origin);
			a.theta = polarAngle(temp[i], origin);
			vect.push_back(a);
		}
	
		// Sort the points in increasing order of theta
		std::sort(vect.begin(), vect.end(), compareTheta);
		
		// Create a bool array to keep valid points in vect
		int n = vect.size();
		bool valid[n];
		std::fill(valid, valid+n, true);
	
		// Check for invalid points in vect
		for(int i=1 ; i<n; i++){
			if(vect[i].r==0 or (i+1<n and vect[i].theta == vect[i+1].theta) ){
				valid[i]=false;
			}
		}
	
		// Copy valid points back into p
		temp.clear();
		for(int i=0 ; i<vect.size() ; i++){
			if(valid[i]){
				temp.push_back(vect[i].point);
			}
		}
	
		// Find convex hull	using Graham Scan
		std::stack<Point> stck;
		stck.push(temp[0]);
		stck.push(temp[1]);
		stck.push(temp[2]);
	
		// Redefine the size of valid points
		n = temp.size(); 
		
		for(int k=3 ; k<n ; k++){
			while(true){
				Point tp(stck.top());		// Point on top of Stack initially
				stck.pop();
				Point next_tp(stck.top());	// Point next to top of stack initially
				if( turn_direction(next_tp, tp, temp[k]) <= 0)
					continue;
				else{
					stck.push(tp);
					break;
				}
			}
			stck.push(temp[k]);
		}

		// Transfer the points on Convex Hull from stack, back to temp vector.
		temp.clear();
		while(!stck.empty()){
			temp.push_back(stck.top());
			stck.pop();
		}
		return temp;
	}
	/**
	* Lambda function used for the sort function in andrews algorithm.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b><ol><li>True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger.</li>
	* <li>False otherwise.</li>
	*/	 
	bool compareXY(const Point& a, const Point& b){
	
		bool condition1 = (a.x > b.x);
		bool condition2 = (a.x == b.x);
		bool condition3 = (a.y > b.y);
		return (condition1 or(condition2 and condition3));
	}
	/**
	 * Andrew's Algorithm to find the Convex Hull of a set of points S.
	 * <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	 * <b> Output:</b> The Convex Hull of S in Clockwise order.
	 * */
	std::vector<Point> andrews(const std::vector<Point>& point_set){
		/**
		 * Main Function to calculate Convex Hull of a set of points "point_set" using Andrew's Algorithm.
		 **/
		int n = point_set.size();
		std::vector<Point> point_set_sorted = point_set;
		
		//sorting on the basis of x-coordinate, if they are equal, sorted on the basis of y-coordinate
		std::sort(point_set_sorted.begin(),point_set_sorted.end(),compareXY);
		
		/**
		 * Declaration of the required vectors for the algorithm, Lupper, Llower and L
		 * */
		std::vector<Point> lup;
		std::vector<Point> ldown;
		
		
		 /**
		  * Pushing to Lupper now
		  * */
		 lup.push_back(point_set_sorted[0]);
		 lup.push_back(point_set_sorted[1]);
		 
		 for(int i=2;i<n;i++){
			 
			 lup.push_back(point_set_sorted[i]);
			 
			 while(lup.size() > 2){
				/**
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 * */
				if(turn_direction(*(lup.rbegin()),*(lup.rbegin()+1),*(lup.rbegin()+2))!= -1){
					/**
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 * */
							
							lup.erase(lup.end() -2);
				}
				else
					break;
			 }
		 }
		 /**
		  * Pushing to Ldown now
		  * */
		ldown.push_back(point_set_sorted[n-1]);
		ldown.push_back(point_set_sorted[n-2]);
		for(int i=n-3;i>=0;i--){
			ldown.push_back(point_set_sorted[i]);
			while(ldown.size() > 2){
				/**
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 * */
				if(turn_direction(*(ldown.rbegin()),*(ldown.rbegin()+1),*(ldown.rbegin()+2))!= -1){
					/**
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 * */
					ldown.erase(ldown.end() -2);
				}
				else
					break;
			}
		}
		/**
		 * To avoid duplicacy with Lupper, the first and the last element of Ldown will be deleted.
		 * */
		ldown.erase(ldown.begin());
		ldown.pop_back();		
		lup.insert(std::end(lup), std::begin(ldown),std::end(ldown));
		return lup;
	}	
	 
}

