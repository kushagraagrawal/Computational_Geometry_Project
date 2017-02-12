/** \file
Contains defintions of functions in Point class.
*/

#include "Point.h"
namespace cg{
	
	Point::Point(){
		x = 0.0;
		y = 0.0;
	}

	Point::Point(const Point& p){
		x = p.x;
		y = p.y;
	}

	Point::Point(double px, double py){
		x = px;
		y = py;
	}

	Point& Point::operator=(const Point& p){
		x = p.x;
		y = p.y;
	}

	std::ostream& operator<<(std::ostream& out, const Point& p){		return out << "(" << p.x << "," << p.y << ")";
	}

	std::istream& operator>>(std::istream& in, Point& p){
		return in >> p.x >> p.y;
	}
	
}
