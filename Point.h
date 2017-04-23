/** \file
* Contains declaration of Point class and PolarPoint structure
*/

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include<iostream>

namespace cg{
	/**
	A point representing a location in (x,y) coordinate space, specified in
	double precision. It can be used to store a set of <x,y> points, create a new point from
	given x,y coordinates.
	*/
	class Point{
	
		public:
			double x;	//!<	x coordinate of the point
			double y;	//!<	y coordinate of the point
			Point();	//!<	An empty constructor. Defaults to (0.0,0.0)
			Point(const Point& p);	//!<	A constructor using another point
			Point(double x, double y);	//!<	A constructor using x and y coordinates 
			Point& operator=(const Point& p);	//!<	Assignment operator overloaded for points
	};	
	
	std::ostream& operator<<(std::ostream&, const Point&);
	std::istream& operator>>(std::istream&, Point&);
	
	/** \brief
	A point representing a location in (r,Θ) coordinate space, specified in double precision.
	*/
	struct PolarPoint{
		cg::Point point;
		double r,theta;
	};
	
	
}

#endif
