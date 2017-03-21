/** \file
Contains defintions of functions in DCEL(Doubly Connected Edge List) class.
*/

#include "Point.h"
#include "DCEL.h"
#include <iostream>

namespace cg{

	DCEL::DCEL(){;}
	DCEL::~DCEL(){;}
	// DCEL constructor with vector of points in ACW order
	DCEL::DCEL(const std::vector<cg::Point> &point_set){
		int n = point_set.size();
		
		// store vertices and interior half-edges in this loop
		for(int i=0;i<n;i++){
			// store vertices
			cg::vertex v;
			v.point = point_set[i];
			v.edge_id = i;
			this->vertex_record.push_back(std::move(v));
			
			// store half-edges
			cg::edge e;
			e.origin_id = i;
			e.face_id=1;
			e.nextedge_id = (i+1)%n;
			e.prevedge_id = (i+n-1)%n;
			this->edge_record.push_back(std::move(e));
		}
		
		// store outer half-edges in CW order
		for(int i=0;i<n;i++){
			cg::edge e;
			e.origin_id = (n-i)%n;
			e.face_id = 0;
			e.nextedge_id = n + (i+1)%n;
			e.prevedge_id = n + (i+n-1)%n;
			this->edge_record.push_back(std::move(e));
		}
		// save twin edges
		for(int i=0;i<n;i++){
			edge_record[i].twinedge_id = 2*n-i-1;
			edge_record[2*n-i-1].twinedge_id = i;
		}
		
		// save faces(inner and outer)
		cg::face f0;
		f0.edge_id = n;
		face_record.push_back(std::move(f0));
		
		cg::face f1;
		f1.edge_id = 0;
		face_record.push_back(std::move(f1));		
	}
	
	// find the vertices of a face 
	std::vector<int> DCEL::verticesOfFace(int fid){
		if(fid >= face_record.size()){
			std::cerr<< "Face index " << fid << " out of bounds\n";
			exit(1);
		}
		std::vector<int> vertices;				// stores indices of vertices in vertex_record vector
		int eid = face_record[fid].edge_id;
		cg::edge e = edge_record[eid];
		do{
			vertices.push_back(e.origin_id);
			e = edge_record[e.nextedge_id];
		}while(e.nextedge_id != edge_record[eid].nextedge_id);

		return vertices;
	}
	
	//	find the edges originating from a vertex
	std::vector<int> DCEL::edgesOfVertex(int vid){
		if(vid >= vertex_record.size()){
			std::cerr<< "Vertex index " << vid << " out of bounds\n";
			exit(1);
		}
		std::vector<int> edge_ids;
		int eid = vertex_record[vid].edge_id;
		int temp_eid = eid;
		while(true){
			edge_ids.push_back(temp_eid);
			int twin_eid = edge_record[temp_eid].twinedge_id;
			int next_eid = edge_record[twin_eid].nextedge_id;
			if(next_eid==eid)
				break;
			temp_eid = next_eid;
		}
		return edge_ids;
	}
	
	void split_face(int eid,int vid){
		;
	}
	
	// ONLY FOR DEBUGGING
	void DCEL::printVertexRecord(void){
		std::cout << "Point\t" << "One edge\n";
		for(auto x:vertex_record){
			std::cout << x.point << "\t" << x.edge_id <<"\n";
		}
	}
	
	void DCEL::printEdgeRecord(void){
		std::cout << "Edge_ID\t" << "Orig_ID\t" << "Twin_ID\t" << "Face_ID\t" << "Next_ID\t" << "Prev_ID\n" ;
		int i=0;
		for(auto x:edge_record){
			std::cout << i++ <<"\t"<<x.origin_id<<"\t"<<x.twinedge_id<<"\t"<<x.face_id<<"\t"<<x.nextedge_id<<"\t"<<x.prevedge_id<<"\n";
		}
	}
	
	void DCEL::printFaceRecord(void){
		std::cout << "Face_ID\t" << "One edge\n";
		int i=0;
		for(auto x:face_record){
			std::cout << i++ << "\t" << x.edge_id <<"\n";
		}
	}
}
