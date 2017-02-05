#include "Point.h"
namespace cg{
	/**
	Constructors of Point Class
	*/
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
	
	bool operator<(const Point& p1, const Point& p2){
	    return (p1.x < p2.x) or (p1.x==p2.x and p1.y<p2.y);
	}
	
	bool operator>(const Point& p1, const Point& p2){
		return operator<(p2,p1);
	}
	
	bool operator<=(const Point& p1, const Point& p2){
		return !operator>(p1,p2);
	}

	bool operator>=(const Point& p1, const Point& p2){
		return !operator<(p1,p2);
	}

	bool operator==(const Point& p1, const Point& p2){
		return (p1.x == p2.x) and (p1.y == p2.y);
	}

	bool operator!=(const Point& p1, const Point& p2){
		return !operator==(p1,p2);
	}

	std::ostream& operator<<(std::ostream& out, const Point& p){
		return out << "(" << p.x << "," << p.y << ")";
	}

	std::istream& operator>>(std::istream& in, Point& p){
		return in >> p.x >> p.y;
	}
	
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
}
