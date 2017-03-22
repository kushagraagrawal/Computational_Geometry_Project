/** \file
Contains defintions of functions in DCEL(Doubly Connected Edge List) class.
*/

#include "Point.h"
#include "DCEL.h"
#include <iostream>
#include <algorithm>

namespace cg{
	
	int DCEL::commonFace(const int vid1,const int vid2){
		// create visited array for the faces
		int f_size = face_record.size();
		bool visited[f_size];
		std::fill(visited,visited+f_size,false);
		
		std::vector<int> edges_ID1 = edgesOfVertex(vid1);
		for(auto x:edges_ID1){
			visited[edge_record[x].face_id]=true;
		}
		
		std::vector<int> edges_ID2 = edgesOfVertex(vid2);
		std::vector<int> common;
		for(auto x:edges_ID2){
			if(edge_record[x].face_id!=0 && visited[edge_record[x].face_id])		// exclude outer face i.e f[0]
				common.push_back(edge_record[x].face_id);
		}
		if(common.size()==1)
			return common[0];
		else{
			std::cerr << "Not exactly one common face b/w " << vid1 << " & " << vid2 << "\n";
			return -1;
		}
	}
	// find edge using vertex_id and face_id
	int DCEL::findEdge(int vid,int fid){
		std::vector<int> edges_vid = edgesOfVertex(vid);
		for(auto x:edges_vid){
			if(edge_record[x].face_id == fid){
				return x;
			}
		}
		std::cerr << "No edge with vertex " << vid << " & face " << fid <<"\n";
		return -1;
	}
	
	bool DCEL::adjacentVertices(const int vid1,const int vid2){
		int fid = commonFace(vid1,vid2);
		int eid1 = findEdge(vid1,fid);
		int eid2 = findEdge(vid2,fid);
		
		// No common face or no edge with given vertex and face
		if(fid==-1 || eid1==-1 || eid2==-1)
			return false;
		// check if one edge is next to other, or vice-versa.
		if(edge_record[eid1].nextedge_id == eid2 || edge_record[eid2].nextedge_id == eid1)
			return true;
		else
			return false;
	}


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
	
	// Add an edge between two vertices. Two half edges are formed between vertex(vid1) and vertex(vid2).
	void DCEL::addEdge(const int vid1,const int vid2){
		
		int fid = this->commonFace(vid1,vid2);
		int eid1 = this->findEdge(vid1,fid);
		int eid2 = this->findEdge(vid2,fid);		
		std::cout << "fid="<<fid <<" " << "eid1=" << eid1 << " " << "eid2=" << eid2 << "\n";
		
		cg::face new_face;
		new_face.edge_id = eid1;
		face_record.push_back(new_face);		// insert new face
		
		face_record[fid].edge_id = eid2;		//check for modifications later
		
		int indexh1 = edge_record.size();
		int indexh2 = indexh1+1;
		
		cg::edge h1,h2;
		h1.origin_id = vid1;
		h1.twinedge_id = indexh2;
		h1.face_id = fid;
		h1.nextedge_id = eid2;
		h1.prevedge_id = edge_record[eid1].prevedge_id;
		
		h2.origin_id = vid2;
		h2.twinedge_id = indexh1;
		h2.face_id = face_record.size()-1;
		h2.nextedge_id = eid1;
		h2.prevedge_id = edge_record[eid2].prevedge_id;
		
		edge_record.push_back(h1);
		edge_record.push_back(h2);
		
		edge_record[edge_record[eid1].prevedge_id].nextedge_id = indexh1;
		edge_record[edge_record[eid2].prevedge_id].nextedge_id = indexh2;
		edge_record[eid1].prevedge_id = indexh2;
		edge_record[eid2].prevedge_id = indexh1;
		
		std::cout << "Hello\n";
		while(eid1!=indexh2){
			std::cout << eid1 << " " << eid2 << "\n";
			edge_record[eid1].face_id = face_record.size()-1;
			eid1 = edge_record[eid1].nextedge_id;
		}
	}
	
	
// ****************************************************************************	
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