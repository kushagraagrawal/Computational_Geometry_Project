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
				
				std::vector<int> points = verticesOfFace(i);
				std::vector<Point> h2;
				
				for(int i= 0;i<h2.size();i++)
					h2.push_back(vertex_record[points[i]]);
				
				std::sort(h2.begin(),h2.end(),compareYX);
				
				std::vector<Point> right,left;
				left.push_back(h2[0]);
				right.push_back(h2[0]);
				int j;
				for (int i=1;i<h2.size();i++){
					if(h2[i].y <= h2[i-1].y && h2[i].y <= h2[i+1].y){
						j = i;
						break;
					}
					else{
						right.push_back(h2[i]);					
					}
				}
				left.push_back(h2[j]);
				right.push_back(h2[j]);
				
				for(int i = j+1;i<h2.size();i++)
					left.push_back(h2[i]);
					
				/*
				 * now we have two separate chains. 
				 * */
				 std::stack s;
				 s.push(vertex_record[points[0]);
				 s.push(vertex_record[points[1]);
				 for(int i =2;i<points.size();i++){
					/*
					 * now to figure out if they on 2 different chains or same chain
					 * then perform ops
					 * */
				 }
		  }
	
	}
}
