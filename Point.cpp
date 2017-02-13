/** \file
Contains defintions of functions in Point class.
*/

#include "Point.h"
namespace cg{
	/**
	* Default constructor.
	* <b> Input: </b> No input.<br>
	* <b> Output: </b> sets x and y to 0,0
	*/
	Point::Point(){
		x = 0.0;
		y = 0.0;
	}
	/**
	* Copy Constructor
	* <b> Input: </b> Point P. <br>
	* <b> Output: </b> Sets value of x and y to x and y of Point p
	*/
	Point::Point(const Point& p){
		x = p.x;
		y = p.y;
	}
	/**
	* Constructor using x and y coordinates
	* <b> Input: </b> x and y coordinates px and py. <br>
	* <b> Output: </b> Assigns px to x and py to y.
	*/
	Point::Point(double px, double py){
		x = px;
		y = py;
	}
	/**
	* Assignment operator overloaded for points
	* <b> Input: </b> point P.<br>
	* <b> Output: </b> Sets value of x and y to x and y of Point p
	*/
	Point& Point::operator=(const Point& p){
		x = p.x;
		y = p.y;
	}
	/**
	* function to output coordinates of Point p
	*/
	std::ostream& operator<<(std::ostream& out, const Point& p){		return out << "(" << p.x << "," << p.y << ")";
	}
	/**
	* function to collect coordinates from user or a file and store of a point P
	*/
	std::istream& operator>>(std::istream& in, Point& p){
		return in >> p.x >> p.y;
	}
	
}
