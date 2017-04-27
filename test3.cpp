#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"
#include "Utility.h"
#include "ConvexHull.h"

namespace cg{

	DCEL triangulatePoints(const std::vector<Point>& point_set){

		std::vector<Point> hull = cg::convexHullAndrews(point_set);

		std::cout << "\nPoints on Convex Hull:\n";
		for(auto x:hull) std::cout << x <<"\t";
		std::cout << "\n";

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
		std::cout << "\nInterior Points:\n";
		for(auto x:interior_points) std::cout << x <<"\t";
		std::cout << "\n";
		/*
		 * find the top most and the bottom most points
		 * */
		DCEL D(hull);
		cg::writeEdges(D,(char *)"out1.txt");	
		
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
		std::cout << "\nTop of Hull's id: "<< top_vertex_id << "\n";
		std::cout << "Bottom of Hull's id: "<< bottom_vertex_id << "\n\n";		

		if(interior_points.size()>0){
			D.addInnerVertex(interior_points[0],top_vertex_id,1);
//			D.printEdgeRecord();
			for(int i=1;i<interior_points.size();i++){
//				std::cout << interior_points[i] << "connected to " << D.vertex_record.size()-1 << "\n";
				D.addInnerVertex(interior_points[i],D.vertex_record.size()-1,1);
//				D.printEdgeRecord(); std::cout <<"\n\n";
			}
			D.addEdge(D.vertex_record.size()-1,bottom_vertex_id);
		}
//		D.printVertexRecord();
//		D.printEdgeRecord();
//		D.printFaceRecord();
		std::cout <<"\nTriangulation started\n";
		cg::writeEdges(D,(char *)"out2.txt");
		cg::triangulate(D);
		return D;
	}
	
	DCEL delaunay_Triangulation(const std::vector<Point>& point_set){
		DCEL D = triangulatePoints(point_set);
		D.printEdgeRecord();
		cg::writeEdges(D,(char *)"out3.txt");
		// Find all interior edges
		int num_edges = D.edge_record.size();
		bool is_interior[num_edges];
		std::fill(is_interior,is_interior+num_edges,true);		// All edges are interior initially
		
		// Remove all external edges from is_interior, Keep only one half-edge for each interior edge
		for(int i=0;i<num_edges;i++){
			if(is_interior[i]==false)
				continue;
			auto edge1 = D.edge_record[i];
			auto edge2 = D.edge_record[edge1.twinedge_id];
			if(edge1.face_id ==0 || edge2.face_id==0){
				is_interior[i]=false;
			}
			is_interior[edge1.twinedge_id]=false;
		}
		std::cout << "\nInterior edges:\t";
		for(int i=0;i<num_edges;i++){
			if(is_interior[i]) std::cout << i << " ";
		}
		std::cout <<"\n";
		
		int is_Del[num_edges];		// Bool array with -1 0 and 1
		std::fill(is_Del,is_Del+num_edges,-1);
		
		// Mark all interior edges as Non-delaunay
		std::stack<int> stck;
		for(int i=0;i<num_edges;i++){
			if(is_interior[i]){
				is_Del[i] = 0;
				stck.push(i);
			}
		}
		
		while(!stck.empty()){
			int eid = stck.top();
			is_Del[eid]=1;
			stck.pop();
			
			if(!D.isDelaunay(eid)){
				std::cout << "\nFlipping " << eid <<"\n";
				std::vector<int> adj_edges = D.flipEdge(eid);
				for(auto x:adj_edges){
					if(is_interior[x] && is_Del[x]==1)
						stck.push(x);
				}
			}
		}
		cg::writeEdges(D,(char *)"out4.txt");
		return D;
	}
	
}

int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);

	cg::DCEL D = delaunay_Triangulation(P);
//	cg::writeEdges(D, argv[2]);
//	D.printEdgeRecord();
//	D.printVertexRecord();
//	D.printFaceRecord();
	return 0;
}


