#include <iostream>
#include <stack>
#include <vector>
#include "Point.h"
#include "Utility.h"
#include "DCEL.h"

namespace cg{
	DCEL triangulate(DCEL &p){
		
		 std::vector<std::vector<int> > polygons;
		  polygons = p.extractAllPolygons();
		  for(int i=0;i<polygons.size();i++){
				/*
				 * sorting the points
				 * lambda function - ymax first then xmin
				 * DCEL has a vector of struct (vertex) and each struct has a point from point class. 
				 * */
				std::sort(polygons[i].begin(),polygons[i].end(),compareYX);
					
			}
			std::vector<int> right,left;
			/*
			 * each vertex has point and edge id (vector of vertices).
			 * which has an edge record.
			 * D.vertexrecord[i].edgeid.
			 * */
			for(int i=1;i<polygons.size();i++){
				
			}
		 
		 
	
	}
}
