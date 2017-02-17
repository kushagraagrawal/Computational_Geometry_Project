/** \file
Contains the function declarations of three Convex Hull Algorithms i.e Graham Scan, Jarvis March and Andrew's algorithm.
*/

#include "ConvexHull.h"
#include <vector>
#include <algorithm>


namespace cg{
	/**
	* Graham Scan's Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order. <br>
	*/
	
	/** Here is a small example on how to use this function.
	\code
		#include "ConvexHull.h"
		#include "Utility.h"
		#include "Point.h"
		#include <iostream>

		int main(int argc,char* argv[]){
	
			double a[6][2] = {{4,5},{0,0},{1.1,0},{0,2.1},{0.8,0.2},{20,50}};
			std::vector<cg::Point> v;
			cg::Point temp;
			for (int i=0;i<6;i++){
				temp.x = a[i][0];
				temp.y = a[i][1];
				v.push_back(temp);
			}
	
			std::vector<cg::Point> result;
	
			std::cout << "Using Graham's Scan Algorithm to find Convex Hull.\n";
			result = cg::convexHullGrahamScan(v);
	
			for(int i=0;i<result.size();i++){
				std::cout << result[i].x <<" "<< result[i].y << std::endl;
			}	
			return 0;
		}
	\endcode
	Output <br>
	\code
		Using Graham's Scan Algorithm to find Convex Hull.
		0 2.1
		20 50
		4 5
		1.1 0
		0 0
	\endcode
	*/
	std::vector<Point> convexHullGrahamScan(const std::vector<Point> & point_set){
	
		// Copy points vector into new vector temp
		// temp will contain the Convex Hull of points vector
		std::vector<Point> temp = point_set;
	
		// Find bottommost point in point_set
		int min_index = indexOfBottomLeft(point_set);
		Point origin = point_set[min_index];
	
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
	
		// Sort the points in increasing order of theta (in case of a tie, sort by r)
		std::sort(vect.begin(), vect.end(), compareTheta);
		
		// Create a bool array to keep valid points in vect
		int n = vect.size();
		std::vector<bool> valid(n,true);
	
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
	
		// Corner case for |point_set|=2
		if(temp.size()==0){
			std::cerr << "Point set is empty. Please check input file\n";
			exit(1);
		}
		else if(temp.size()<=2){
			return temp;
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
		
		// reverse the vector to keep anti-clockwise order
		std::reverse(temp.begin(),temp.end());
		return temp;
	}
	
	/**
	 * Andrew's Algorithm to find the Convex Hull of a set of points S.
	 * <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	 * <b> Output:</b> The Convex Hull of S in Clockwise order.
	 * 
	 */
	std::vector<Point> convexHullAndrews(const std::vector<Point>& point_set){
		/*
		 * Main Function to calculate Convex Hull of a set of points "point_set" using Andrew's Algorithm.
		 *
		 */
		int n = point_set.size();
		std::vector<Point> point_set_sorted = point_set;
		
		//sorting on the basis of x-coordinate, if they are equal, sorted on the basis of y-coordinate
		std::sort(point_set_sorted.begin(),point_set_sorted.end(),compareXY);
		
		/*
		 * Declaration of the required vectors for the algorithm, Lupper, Llower and L
		 *
		 */
		std::vector<Point> lup;
		std::vector<Point> ldown;
		
		
		 /*
		  * Pushing to Lupper now
		  *
		  */
		 lup.push_back(point_set_sorted[0]);
		 lup.push_back(point_set_sorted[1]);
		 
		 for(int i=2;i<n;i++){
			 
			 lup.push_back(point_set_sorted[i]);
			 
			 while(lup.size() > 2){
				/*
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 *
				 */
				if(turn_direction(*(lup.rbegin()),*(lup.rbegin()+1),*(lup.rbegin()+2))!= -1){
					/*
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 *
					 */	
						lup.erase(lup.end() -2);
				}
				else
					break;
			 }
		 }
		 /*
		  * Pushing to Ldown now
		  *
		  */
		ldown.push_back(point_set_sorted[n-1]);
		ldown.push_back(point_set_sorted[n-2]);
		for(int i=n-3;i>=0;i--){
			ldown.push_back(point_set_sorted[i]);
			while(ldown.size() > 2){
				/*
				 * We can only check for right or left turns if the vector contains more than 2 elements.
				 * The function turn_direction will return 1 for Left Turn, 0 for Collinearity and -1 for RIGHT TURN
				 *
				 */
				if(turn_direction(*(ldown.rbegin()),*(ldown.rbegin()+1),*(ldown.rbegin()+2))!= -1){
					/*
					 * The middle point of the last three points is deleted since the three points do not make a right turn
					 *
					 */
					ldown.erase(ldown.end() -2);
				}
				else
					break;
			}
		}
		/*
		 * To avoid duplicacy with Lupper, the first and the last element of Ldown will be deleted.
		 *
		 */
		ldown.erase(ldown.begin());
		ldown.pop_back();		
		lup.insert(std::end(lup), std::begin(ldown),std::end(ldown));
		return lup;
	}	
	
	/**
	* Jarvis March (Gift Wrapping) Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order.
	*/

	std::vector<Point> convexHullJarvisMarch(const std::vector<Point>& point_set){
		
		std::vector<Point> ch; //Convex Hull Output
	
		// Trivial case for |point_set| <= 2
		if(point_set.size()==0){
			std::cerr << "Point set is empty. Please check input file\n";
			exit(1);
		}
		else if(point_set.size()<=2){
			return point_set;
		}
	
		//Determine Initial Origin
		int k0 = indexOfBottomLeft(point_set), k = k0, count = 0;
		double theta0 = 0.0; //angle of previous edge, relative to which all angles are computed
		do{

			ch.push_back(point_set[k]);
			int j;
			double theta, r, theta_min = INF, r_min = INF;
			for(int i = 0; i < point_set.size(); i++){
				if(i != k){
					theta = fmod(polarAngle(point_set[i], *(ch.rbegin())) - theta0 + 360.0, 360.0);//ensures angles are between zero and 360
					r = euclideanDistance(point_set[i], *(ch.rbegin()));
					//check if the point makes the smallest angle
					if(theta < theta_min){
						theta_min = theta;
						r_min = r;
						j = i;
					} else if(theta == theta_min){ //handling for equal angle, closest point is chosen
						if(r < r_min){
							r_min = r;
							j = i;
						}
					}
				}
			}	
			k = j;
	
			//updating angle newest edge of convex hull makes with x-axis
			theta0 = polarAngle(*(ch.rbegin()), *(ch.rbegin()+1));
			count++;
		} while(k!=k0 and count < point_set.size());

		return ch;
	}
}

