#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include<iostream>

namespace cg{
	class Point{
	
		public:
			double x,y;
		
			Point();
			Point(const Point& p);
			Point(double x, double y);
		
			Point& operator=(const Point& p);
	};	
	
	bool operator<(const Point&, const Point&);
	bool operator>(const Point&, const Point&);
	bool operator<=(const Point&, const Point&);
	bool operator>=(const Point&, const Point&);
	bool operator==(const Point&, const Point&);
	bool operator!=(const Point&, const Point&);
	std::ostream& operator<<(std::ostream&, const Point&);
	std::istream& operator>>(std::istream&, Point&);
	int turn_direction(const Point&, const Point&, const Point&);
}

#endif
