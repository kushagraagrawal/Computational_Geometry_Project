#include <iostream>
#include <set>
#include <utility>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"
#include "Utility.h"
#include "ConvexHull.h"

namespace cg{

	DCEL assignment3(const std::vector<Point>& point_set){

		std::vector<Point> hull = cg::convexHullAndrews(point_set);
		
		std::set<std::pair<double,double> > hull_set;
		for(auto h: hull){
			hull_set.insert(std::make_pair(h.x, h.y));
		}
		
		std::vector<cg::Point> interior_points;
		for(auto p:point_set){
			auto pt = std::make_pair(p.x,p.y);
			if(hull_set.find(pt) == hull_set.end()){
				interior_points.push_back(p);
			}
		}
		
		std::sort(interior_points.begin(),interior_points.end(),compareYX);
		for(auto x:interior_points) std::cout << x <<"\n";
		
		/*
		 * find the top most and the bottom most points
		 * */
		DCEL D(hull);
		
		int top_vertex_id = 0,bottom_vertex_id = 0;
		for(int i=1;i<hull.size();i++){
			if(below(D.vertex_record[top_vertex_id].point,D.vertex_record[i].point)){
//					std::cout << "Top changed to " << points[i] << "\n";
					top_vertex_id = i;
				}
			if(below(D.vertex_record[i].point,D.vertex_record[bottom_vertex_id].point)){
//				std::cout << "Bottom changed to " << points[i] << "\n";
				bottom_vertex_id  = i;
			}
		}
		
		
		/*
		 * adding to DCEL 
		 *
		 */
		D.addInnerVertex(interior_points[0],top_vertex_id,1);
		for(int i=1;i<interior_points.size()-1;i++){
			D.addInnerVertex(interior_points[i],D.vertex_record.size()-1,1);
		}
		D.addEdge(D.vertex_record.size()-1,bottom_vertex_id);
		D.printEdgeRecord();
		cg::triangulate(D);
		return D;
	}
}

int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);

	cg::DCEL D = assignment3(P);
	cg::writeEdges(D, argv[2]);	
	
	return 0;
}


