/** \file
Contains declaration of common utility fucntions.
*/

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "Point.h"


namespace cg{
	class DCEL;
	
	bool isConvex(const std::vector<Point> &P);
	Point circumcentre(const Point &A,const Point &B,const Point &C);


	/**
	A bool function to check if first point lies below second point.
	<b> Input: </b>  Two objects of Point class i.e A and B.
	<b> Output: </b> <em> true </em> if Point A lies below Point B(or to the right if both are on same horizontal line),
					 <em> false </em> otherwise.
	*/
	bool below(const cg::Point &A,const cg::Point &B);

	/**
	Function to write all edges of DCEL to output file
	<b> Input: </b> DCEL D which stores the the planar subdivision, file name to which edges of DCEL are to be written. <br>
	<b> Output: </b> returns nothing, writes the edges of the DCEL to output file in the format "x1 y1 x2 y2", where (x1,y1) and (x2,y2) 		are the end points of an edge.
	*/
	void writeEdges(cg::DCEL D,char *output_filename);
	/**
	* Function to read a set of points from file and store it in a vector.
	* <b> Input: </b> File name and set of points. <br>
	* <b> Output: </b> Parses the file "file_name" and writes the point to the vector vect
	*/
	void readPointSet(char *, std::vector<Point> & );
	
	/**
	* Function to write a set of points from a vector to an output file.
	* <b> Input: </b> File name and set of points.<br>
	* <b> Output: </b> Writes the vector "vect" to the file "file_name"	
	*/
	void writePointSet(char *, const std::vector<Point> & );
	
	/**
	* Function to find the turning direction of a	set of three points in the sequence p,q,r.
	* <b> Input: </b> Three points p,q,r. <br>
	* <b> Output: </b> 1 for Left Turn, 0 if the points are Collinear, -1 for Right Turn.
	*/
	int turn_direction(const Point&, const Point&, const Point&);
	
	/**
	* Function to find the polar angle of two points in cartesian coordinate system.
	* <b> Input: </b> 2 points i.e. a and b. <br>
	* <b> Output: </b> polar angle between a and b in cartesian coordinate system.
	*/
	double euclideanDistance(const Point&,const Point&);
	
	/**
	* Function to find the polar angle of two points in cartesian coordinate system.
	* <b> Input: </b> 2 points a and b. <br>
	* <b> Output: </b> polar angle between a and b in cartesian coordinate system.
	*/
	double polarAngle(const Point&,const Point&);
	
	/**
	* Function to find the interior angle formed by the three points of a simple polygon(in Anti-clockwise order) in cartesian coordinate system.
	* <b> Input: </b> 3 points i.e a, b and c of a simple polygon in anti-clockwise order. <br>
	* <b> Output: </b> Interior angle of the polygon, formed by these three points.
	*/
	double polarAngle(const Point &a,const Point &b,const Point&c);
	
	/**
	* Function to find bottommost point(or leftmost such point in case of a tie) in a point set defined in cartesian space.
	* <b> Input: </b> Vector of points (point_set) .<br>
	* <b> Output: </b> Index of bottommost point(or leftmost point in case of a tie) in the vector point_set.
	*/
	int indexOfBottomLeft(const std::vector<Point> &);
	
	/**
	* Compare two polar points by their theta
	* <b> Input: </b> 2 Polar Points a and b. <br>
	* <b> Output: </b> <ol><li> True if a's angle is less than b's theta or both are equal but a's radius is less than b's radius</li>
	* <li> False otherwise</li></ol>
	*/
	bool compareTheta(const PolarPoint &, const PolarPoint &);
	
	/**
	* Lambda function used for the sort function in andrews algorithm.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b><ol><li>True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger.</li>
	* <li>False otherwise.</li></ol>
	*/
	bool compareXY(const Point& a, const Point& b);
		/**
	* Lambda function used for the sort function on y coordinate(larger first), followed by x coordinate in case of a tie.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b> <ol> <li> True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger. </li>
	* 						<li> False otherwise. </li>
*					  </ol>
	*/
	bool compareYX(const Point& a, const Point& b);
}

#endif
