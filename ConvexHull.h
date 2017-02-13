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
	
	/**
	* Lambda function used for the sort function in andrews algorithm.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b><ol><li>True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger.</li>
	* <li>False otherwise.</li>
	*/
	bool compareXY(const Point& a, const Point& b);
	
	/**
	 * Andrew's Algorithm to find the Convex Hull of a set of points S.
	 * <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	 * <b> Output:</b> The Convex Hull of S in Clockwise order.
	 * */
	std::vector<Point> andrews(const std::vector<Point>& point_set);
	
}

#endif
