#include <iostream>
#include <stack>
#include <vector>
#include "Point.h"
#include "Utility.h"
#include "DCEL.h"

namespace cg{
	DCEL triangulate(DCEL &D){
		
		 std::vector<std::vector<int> > polygons;
		  polygons = D.extractAllPolygons();
		  for(int face=1;face<polygons.size();face++){
				
				std::vector<int> points = D.verticesOfFace(face);
				//std::vector<Point> h2;
				
				//for(int i= 0;i<h2.size();i++)
					//h2.push_back(D.vertex_record[points[i]]);
				
				
				std::vector<int> right,left;
				int top_id=points[0], bottom_id=points[0];
				for (int i=1;i<points.size();i++){
					if(below(D.vertex_record[top_id].point,D.vertex_record[i].point){
						top_id = i;
					}
					if(below(D.vertex_record[i].point,D.vertex_record[bottom_id].point){
						bottom_id = i;
					}
				}
				
				
				left.push_back(top_id);
				while(left.back()!=bottom_id){
					int id = nextVertex(left.back(),face);
					left.push_back(id);
				}
				
				// similarly for right. start from bottom and to the top	
				// reverse right.
				
				// merge subroutine. comparing left and right vectors on y-coordinate. use below() function.
				// obtain final list
				/*
				 * now we have two separate chains. 
				 * */
				 
				 std::stack<int> s;
				 s.push(points[0]);
				 s.push(points[1]);
				 
				 for(int i =2;i<points.size();i++){
					/*
					 * now to figure out if they on 2 different chains or same chain
					 * then perform ops
					 * */
					 int temppoint = s.pop();
					 if(!onSameChain(temppoint,vertex_record[points[i]],left,right)){
						D.addEdge(temppoint,i);
						while(s.size()>1){
							
							something.addEdge(s.pop(),i);
						}
						s.push(points[i-1]);
						s.push(points[i]);
					 }
					 else{
						//D.addEdge(temppoint,i);
						while(1){
							temppoint = s.pop();
							
							
							
							else
							break;
						//keep popping
						//s.push(last vertex popped from s
						//s.push(i);
					 }
						s.push(temppoint);
						s.push(i);
					}
				 }
				//add diagonals to all stack vertices except first and last one to un.
				int i=0,size_of_stack = s.size();
				while(!s.empty()){
					if(i==0){
						i++;
						continue;
					}
					else if(i== size_of_stack -1 )
						break;
					else
						something.addEdge(s.pop(),points[points.size() -1]);
						
				}
		  }
	
	}
}
