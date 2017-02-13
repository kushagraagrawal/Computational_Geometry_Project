/** \file
Contains the function definitions of three Convex Hull Algorithms i.e Graham Scan, Jarvis March and Andrew's algorithm.
*/

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
	const double INF = 1e10; // maximum coordinate value of a point
	
	/**
	* Graham Scan's Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order.
	*/
	std::vector<Point> convexHullGrahamScan(const std::vector<Point> & points);
	
	/**
	* Andrew's Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in Clockwise order.
	* */
	std::vector<Point> convexHullAndrews(const std::vector<Point>& point_set);
	
	/**
	* Jarvis March (Gift Wrapping) Algorithm to find the Convex Hull of a set of points S.
	* <b> Input: </b> A finite set of points(S) in cartesian plane, S = {s1,s2,...sn}.<br>
	* <b> Output:</b> The Convex Hull of S in anti-clockwise order.
	*/
	std::vector<Point> convexHullJarvisMarch(const std::vector<Point>& point_set);
}

#endif
