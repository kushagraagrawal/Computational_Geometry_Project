/** \file
Contains the function declarations of the monotonization of a regular polygon stored in a DCEL.
*/

#ifndef YMONOTONE_H_INCLUDED
#define YMONOTONE_H_INCLUDED

#include "DCEL.h"
#include "Status.h"
#include "Utility.h"
#include "Point.h"
#include <queue>

#define START_VERTEX	0
#define END_VERTEX		1
#define SPLIT_VERTEX	2
#define MERGE_VERTEX	3
#define REG_VERTEX		4

namespace cg{
	/**
	A function to find the type of the vertex of the simple polygon(i.e start vertex/end vertex/split vertex/merge vertex/regular vertex).
	<b> Input:  </b>	DCEL D which stores the polygon, index of the vertex in vertex_record of DCEL. <br>
	<b> Output: </b>	The type of vertex i.e start vertex/end vertex/split vertex/merge vertex/regular vertex,
						denoted by 0,1,2,3 and 4 respectively.
	*/

	int typeOfVertex(const cg::DCEL &D,int index);
	/**
	A function to partition a simple polygon stored in a DCEL(in Anti-clockwise order),
	into a set of y-monotone polygons, by inserting edges in the DCEL.
	<b> Input: </b> A DCEL D consisting of a simple polygon. <br>
	<b> Output: </b> none.
	*/
	void make_monotone(cg::DCEL &D);
	
	/**
	A bool function to check if first point lies below second point.
	<b> Input: </b>  Two objects of Point class i.e A and B.
	<b> Output: </b> <em> true </em> if Point A lies below Point B(or to the right if both are on same horizontal line),
					 <em> false </em> otherwise.
	*/
	bool below(const cg::Point &A,const cg::Point &B);
	
	/**
	A function to handle a start vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_start_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]);
	
	/**
	A function to handle an end vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_end_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]);
	
	/**
	A function to handle a split vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_split_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]);
	
	/**
	A function to handle a merge vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_merge_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]);
	
	/**
	A function to handle a regular vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_regular_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]);
}

#endif
