#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "Point.h"

static const double PI = 3.1415926535;

namespace cg{

	void readPointSet(char *, std::vector<Point> & );
	void writePointSet(char *, const std::vector<Point> & );
	int turn_direction(const Point&, const Point&, const Point&);
	double euclideanDistance(const Point&,const Point&);
	double polarAngle(const Point&,const Point&);

}

#endif
