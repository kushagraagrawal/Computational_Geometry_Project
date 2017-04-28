/** \file
 * File that implements the third assignment of CS F441 - Selected Topics in Computer Science.
 * The problem statement of the assignment is to use the already existing API developed in the previous assignments to create the triangulation of n given points in 2D plane.
 * 
 * */
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
	/**
	 * Function to find the triangulation of a set of points in 2D plane. This is accomplished by finding the convex hull of the set of 2D points and connecting the interior points to 
	 * form 2 y-monotone polygons. They are then triangulated using the triangulate function developed earlier.
	 * <b> Input: </b> A set of points in 2D space
	 * <b> Output: </b> the triangulation of the point set stored in the DCEL.
	 * */
	DCEL triangulatePoints(const std::vector<Point>& point_set){
		// calling Andrew's algorithm function to find convex hull of point_set and store it in hull.
		std::vector<Point> hull = cg::convexHullAndrews(point_set);

		std::cout << "\nPoints on Convex Hull:\n";
		for(auto x:hull) std::cout << x <<"\t";
		std::cout << "\n";
		// forming a set of the convex hull points
		std::set<std::pair<double,double> > hull_set;
		for(auto h: hull){
			hull_set.insert(std::make_pair(h.x, h.y));
		}
		// vector to store interior points, i.e. points not on the convex hull.
		std::vector<cg::Point> interior_points;
		for(auto p:point_set){
			auto pt = std::make_pair(p.x,p.y);
			if(hull_set.find(pt) == hull_set.end()){
				interior_points.push_back(p);
			}
		}
		// sorting the interior points on the basis of Y-coordinates 
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
		// Dividing the polygon formed into two y-monotone polygons by joining the top-most vertex of convex hull to the highest interior point, then that point to the next interior point and so on.
		if(interior_points.size()>0){
			D.addInnerVertex(interior_points[0],top_vertex_id,1);
//			D.printEdgeRecord();
			for(int i=1;i<interior_points.size();i++){
//				std::cout << interior_points[i] << "connected to " << D.vertex_record.size()-1 << "\n";
				D.addInnerVertex(interior_points[i],D.vertex_record.size()-1,1);
//				D.printEdgeRecord(); std::cout <<"\n\n";
			}
			// adding the lowest interior point and lowest point on CH to divide the convex hull into two polygons, i.e faces
			D.addEdge(D.vertex_record.size()-1,bottom_vertex_id);
		}
		std::cout <<"\nTriangulation started\n";
		cg::writeEdges(D,(char *)"out2.txt");
		cg::triangulate(D);
		return D;
	}
	/**
	 * Function to triangulate a set of points using Delaunay Triangulation.
	 * This is done by constructing an arbitrary triangulation T of point set S, pushing all non-locally interior edges of T on stack and mark them
	 * converting non-locally Delaunay edges to Delaunay edges.
	 * <b> Input: </b> A set of points in 2D space
	 * <b> Output: </b> the triangulation of the point set stored in the DCEL.
	 * */
	
	DCEL delaunay_Triangulation(const std::vector<Point>& point_set){
		DCEL D = triangulatePoints(point_set);
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
				is_interior[i] = is_interior[edge1.twinedge_id]=false;
			}
		}
		std::cout << "\nInterior edges:\t";
		for(int i=0;i<num_edges;i++){
			if(is_interior[i]) std::cout << i << " ";
		}
		std::cout <<"\n";
		
		int is_Del[num_edges];		// Bool array with -1 0 and 1
		std::fill(is_Del,is_Del+num_edges,-1);
		
		// Mark all interior edges as Non-delaunay
		std::stack<std::pair<int,int> > stck;
		for(int i=0;i<num_edges;i++){
			if(is_interior[i]){
				is_Del[i] = is_Del[D.edge_record[i].twinedge_id] = 0;
				stck.push({i,D.edge_record[i].twinedge_id});
			}
		}
		//Flipping the edges in the stack if they are not locally Delaunay
		while(!stck.empty()){
			int eid = stck.top().first;
			is_Del[eid]=is_Del[D.edge_record[eid].twinedge_id]=1;
			stck.pop();
			
			if(!D.isDelaunay(eid)){
				std::cout << "\nFlipping " << eid <<"\n";
				std::vector<int> adj_edges = D.flipEdge(eid);
				
				for(auto x:adj_edges){
					if(is_interior[x] && is_Del[x]==1)
						stck.push({x,D.edge_record[x].twinedge_id});
				}
			}
		}
		std::cout << "\nEdges remained\n";
		for(int i=0;i<num_edges;i++){
			if(is_interior[i] && !D.isDelaunay(i))
				std::cout << i <<" ";
		}
		std::cout <<"\n";
		cg::writeEdges(D,(char *)"out4.txt");
		return D;
	}
	
}

int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);

	cg::DCEL D = delaunay_Triangulation(P);
	
	std::ofstream file((char *)"circles.txt");

	if(!file.is_open()){
		std::cerr << "Output File not found\n";
		exit(1);
	}
	std::cout << "\nFaces:\n";
	for(int i=1;i<D.face_record.size();i++){
		std::vector<int> pid = D.verticesOfFace(i);
		for(auto x:pid) std::cout << x <<" ";
		std::cout << "\n";
		cg::Point A = D.vertex_record[pid[0]].point;
		cg::Point B = D.vertex_record[pid[1]].point;
		cg::Point C = D.vertex_record[pid[2]].point;
		cg::Point centre = cg::circumcentre(A,B,C);
		double radius = cg::euclideanDistance(centre,A);
		file << centre.x << " " << centre.y << " " <<radius << "\n";
	}
	return 0;
}


