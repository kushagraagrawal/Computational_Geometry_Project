#ifndef CONVEXHULL_H_INCLUDED
#define CONVEXHULL_H_INCLUDED

#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>

#include "Point.h"
#include "Utility.h"

namespace cg{
	/**
	* Graham Scan's Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order.
	*/
	std::vector<Point> convexHullGrahamScan(const std::vector<Point> & points);
	bool compareXY(const Point& a, const Point& b);
	std::vector<Point> andrews(const std::vector<Point>& point_set);
	
}

#endif
