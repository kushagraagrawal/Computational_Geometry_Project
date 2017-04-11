/** \file
Contains definition of triangulation function.
*/

#ifndef TRIANGULATE_H_INCLUDED
#define TRIANGULATE_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "Utility.h"

#define LEFT -1
#define RIGHT 1

namespace cg{
	/**
	A function to triangulate all the y-monotone polygons stored in a DCEL. <br>
	All partitions stored in the DCEL should be y-monotone, for correct output.<br>
	<b> Input: </b> A DCEL object D. <br>
	<b> Output: </b> returns nothing, triangulates all partitions stored in D, by adding edges to it.
	*/
	void triangulate(cg::DCEL &D);
	
}
#endif
