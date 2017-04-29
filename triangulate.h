/** \file
Contains definition of triangulation function.
*/

#ifndef TRIANGULATE_H_INCLUDED
#define TRIANGULATE_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "Utility.h"
#include "ConvexHull.h"

#define LEFT -1
#define RIGHT 1

namespace cg{
	/**
	 * Function to triangulate a set of points using Delaunay Triangulation.
	 * This is done by constructing an arbitrary triangulation T of point set S, pushing all non-locally interior edges of T on stack and mark them
	 * converting non-locally Delaunay edges to Delaunay edges.
	 * <b> Input: </b> A set of points in 2D space
	 * <b> Output: </b> the triangulation of the point set stored in the DCEL.
	 * */
	
	cg::DCEL delaunay_Triangulation(const std::vector<Point>& point_set);
	
	/**
	 * Function to find the triangulation of a set of points in 2D plane. This is accomplished by finding the convex hull of the set of 2D points and connecting the interior points to 
	 * form 2 y-monotone polygons. They are then triangulated using the triangulate function developed earlier.
	 * <b> Input: </b> A set of points in 2D space
	 * <b> Output: </b> the triangulation of the point set stored in the DCEL.
	 * */
	cg::DCEL triangulatePoints(const std::vector<Point>& point_set);
	

	/**
	A function to triangulate all the y-monotone polygons stored in a DCEL. <br>
	All partitions stored in the DCEL should be y-monotone, for correct output.<br>
	<b> Input: </b> A DCEL object D. <br>
	<b> Output: </b> returns nothing, triangulates all partitions stored in D, by adding edges to it.
	*/
	void triangulate(cg::DCEL &D);
	
}

#endif
