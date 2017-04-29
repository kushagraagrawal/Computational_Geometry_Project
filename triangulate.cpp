/** \file
Contains implementation of triangulation function.
*/
#include "triangulate.h"
#include "ConvexHull.h"

namespace cg{

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
	A function to triangulate all the y-monotone polygons stored in a DCEL. <br>
	All partitions stored in the DCEL should be y-monotone, for correct output.<br>
	<b> Input: </b> A DCEL object D. <br>
	<b> Output: </b> returns nothing, triangulates all partitions stored in D, by adding edges to it.
	*/
	void triangulate(cg::DCEL &D){

		int size_face_rec = D.face_record.size();
	  	for(int face=1;face < size_face_rec;face++){
	  	
			std::cout << "Face " << face << "\n";

			std::vector<int> points = D.verticesOfFace(face);
			
			for(auto x:points) std::cout << x <<" ";
			std::cout << "\n"; 
			
			std::vector<int> right,left;
			int top_id=points[0], bottom_id=points[0];
			
//			std::cout << "\nAt begin Top:"<< top_id << "\t Bottom:" << bottom_id <<"\n";
			
			for (int i=1;i<points.size();i++){
				if(below(D.vertex_record[top_id].point,D.vertex_record[points[i]].point)){
//					std::cout << "Top changed to " << points[i] << "\n";
					top_id = points[i];
				}
				if(below(D.vertex_record[points[i]].point,D.vertex_record[bottom_id].point)){
//					std::cout << "Bottom changed to " << points[i] << "\n";
					bottom_id = points[i];
				}
			}
			std::cout << "\nTop:"<< top_id << "\t Bottom:" << bottom_id <<"\n";

			// chain[i] stores whether ith vertex in D lies in the right chain or left chain. chain[i] = -1 for left, 1 for right
			int chain[D.vertex_record.size()];
			std::fill(chain,chain+D.vertex_record.size(),0);

			// Set chain of all vertices in Left chain to LEFT			
			left.push_back(top_id);
			while(left.back()!=bottom_id){
				int id = D.nextVertex(left.back(),face);
				chain[id]=LEFT;
				left.push_back(id);
			}
			
			// Set chain of all vertices in right chain to RIGHT			
			right.push_back(bottom_id);
			while(right.back()!=top_id){
				int id = D.nextVertex(right.back(),face);
				chain[id]=RIGHT;
				right.push_back(id);
			}
			std::reverse(right.begin(),right.end());
			
			std::cout << "Left\t";
			for(auto x:left) std::cout << x <<" ";
			std::cout << "\nRight\t";
			for(auto x:right) std::cout << x <<" ";
			std::cout << "\nChain: ";
			for(auto x:chain) std::cout << x <<" ";
			
			
			// Merge left and right chains into finallist, with y coordinate as priority.
			std::vector<int> finallist;
			int L=1,R=1;		// indexes in left and right chains respectively.
			finallist.push_back(left[0]);
			while (L!=left.size() and R!=right.size()){
				cg::Point L_point = D.vertex_record[left[L]].point;
				cg::Point R_point = D.vertex_record[right[R]].point;
				if(below(R_point,L_point)){
						finallist.push_back(left[L]);
						L++;
				}
				else{
					finallist.push_back(right[R]);
					R++;
				}
			}
			
			while(L!=left.size()){
				finallist.push_back(left[L]);
				L++;
			}
			while(R!=right.size()){
				finallist.push_back(right[R]);
				R++;
			}
			finallist.pop_back();
			
			std::cout << "\nMerged\n";
			for(auto x:finallist) std::cout << x <<" ";
			
			// Add edges in DCEL when needed, to triangulate.
		 	std::stack<int> stck;
			stck.push(finallist[0]);
			stck.push(finallist[1]);
			 
			for(int i=2;i<finallist.size()-1;i++){
				std::cout << "\nIteration i=" << i << "\n";
				//if they on 2 different chains			 
				if(chain[stck.top()]!= chain[finallist[i]]){
					std::cout << stck.top() <<" and " << finallist[i] << " lie on diff chain\n";
					while(!stck.empty()){
						if(stck.size()>1)
							D.addEdge(stck.top(),finallist[i]);
						stck.pop();
					}
					stck.push(finallist[i-1]);
					stck.push(finallist[i]);
				}
				// if they are on same chain
				else{
					std::cout << stck.top() <<" and " << finallist[i] << " lie on same chain\n";
					while(!stck.empty()){
						int top1 = stck.top();
						stck.pop();
						if(stck.empty()){
							stck.push(top1);
							stck.push(finallist[i]);
//							std::cout << "Pushed " << top1 << " & " << finallist[i] <<"\n";
							break;
						}
						int top2 = stck.top();
						
//						std::cout << "Popped " << top1 << " top2 = " << top2 <<"\n"; 
						
						cg::Point curr_point = D.vertex_record[finallist[i]].point;
						cg::Point top1_point = D.vertex_record[top1].point;
						cg::Point top2_point = D.vertex_record[top2].point;
						if(finallist[i]==4){
//						 	std::cout << turn_direction(curr_point,top1_point,top2_point) << "\t=\t" << chain[finallist[i]] << "\n";
						}
						if(turn_direction(curr_point,top1_point,top2_point)==chain[finallist[i]]){
							D.addEdge(top2,finallist[i]);
						}
						else{
							stck.push(top1);
							stck.push(finallist[i]);
//							std::cout << "Pushed " << top1 << " & " << finallist[i] <<"\n";
							break;
						}
					}
				}
				std::cout << "Finished i=" << i << "\n------------------------------------\n";
			}
			
			stck.pop();
			while(stck.size()>1){
				D.addEdge(stck.top(),finallist.back());
				stck.pop();
			}
			
		}
	
	}
	
}
