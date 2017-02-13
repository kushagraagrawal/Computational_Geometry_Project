/** \file
Contains the function definitions of common utility functions.
*/

#include "Utility.h"
#include<iomanip>
namespace cg{
	
	/**
	* Function to read a set of points from file and store it in a vector.
	* <b> Input: </b> File name and set of points. <br>
	* <b> Output: </b> Parses the file "file_name" and writes the point to the vector vect
	*/
	void readPointSet(char *file_name, std::vector<Point> & vect){
		std::ifstream file(file_name);
		if(!file.is_open()){
			std::cerr << "Input File \"" << file_name << "\" not found !!\n";
			exit(1);
		}
		cg::Point p;
		while((file >> p)){
			vect.push_back(p);
		}
	}
	
	/**
	* Function to write a set of points from a vector to an output file.
	* <b> Input: </b> File name and set of points.<br>
	* <b> Output: </b> Writes the vector "vect" to the file "file_name"	
	*/
	void writePointSet(char *file_name, const std::vector<Point> & vect){
		std::ofstream file(file_name);
		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		file << std::setprecision(15);
		for(auto it=vect.begin();it!=vect.end();it++){
			file << it->x << " " << it->y << "\n";
		}
	}

	/**
	* Function to find the turning direction of a	set of three points in the sequence p,q,r.
	* <b> Input: </b> Three points p,q,r. <br>
	* <b> Output: </b> 1 for Left Turn, 0 if the points are Collinear, -1 for Right Turn.
	*/
	int turn_direction(const Point& p, const Point& q, const Point& r){
		// determinant value
		double det = (1*(q.x*r.y - q.y*r.x) - p.x*(1*r.y - q.y*1) + p.y*(1*r.x - q.x*1));
		if (det == 0.0){
			return 0;
		}
		else if (det > 0.0){
			return 1;
		}
		else return -1;
	}
	
	/**
	* Function to find the euclidean distance between two points in Cartesian coordinate system.
	* <b> Input: </b> 2 points a and b.<br>
	* <b> Output: </b> Euclidean distance between a and b.
	*/
	double euclideanDistance(const Point &a,const Point &b){
		return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
	}
	
	/**
	* Function to find the polar angle of two points in cartesian coordinate system.
	* <b> Input: </b> 2 points a and b. <br>
	* <b> Output: </b> polar angle between a and b in cartesian coordinate system.
	*/
	double polarAngle(const Point &a,const Point &b){
		return fmod((atan2(double(a.y-b.y),double(a.x-b.x)) + 2*PI),2*PI)* 180/PI;
	}
	
	/**
	* Function to find bottommost point(or leftmost such point in case of a tie) in a point set defined in cartesian space.
	* <b> Input: </b> Vector of points (point_set) .<br>
	* <b> Output: </b> Index of bottommost point(or leftmost point in case of a tie) in the vector point_set.
	*/
	int indexOfBottomLeft(const std::vector<Point> & point_set){
		int min_index=0;
		for(int i=1;i<point_set.size();i++){
			if(point_set[min_index].y > point_set[i].y)
				min_index = i;
			else if((point_set[min_index].y == point_set[i].y) and (point_set[min_index].x > point_set[i].x))
				min_index = i;
		}
		return min_index;
	}
	
	/**
	* Compare two polar points by their theta
	* <b> Input: </b> 2 Polar Points a and b. <br>
	* <b> Output: </b> <ol><li> True if a's angle is less than b's theta or both are equal but a's radius is less than b's radius</li>
	* <li> False otherwise</li></ol>
	*/
	bool compareTheta(const PolarPoint &a,const PolarPoint &b){
		bool condition1 = (a.theta < b.theta);
		bool condition2 = (a.theta == b.theta);
		bool condition3 = (a.r < b.r);
		return (condition1 or (condition2 and condition3));
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
}
