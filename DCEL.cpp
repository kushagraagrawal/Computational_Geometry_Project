/** \file
Contains defintions of functions in DCEL(Doubly Connected Edge List) class.
*/

#include "DCEL.h"
#include "Point.h"
#include "Utility.h"
#include <iostream>
#include <algorithm>

namespace cg{
	// Flips edge <BD,DB> to  <AC,CA>
	
	std::vector<int> DCEL::flipEdge(int BD_id){
		int DC_id = this->edge_record[BD_id].nextedge_id;
		int CB_id = this->edge_record[DC_id].nextedge_id;
	
		int DB_id = this->edge_record[BD_id].twinedge_id;
		int BA_id = this->edge_record[DB_id].nextedge_id;
		int AD_id = this->edge_record[BA_id].nextedge_id;		
		
		int A_id = this->edge_record[AD_id].origin_id;
		int D_id = this->edge_record[DC_id].origin_id;
		int C_id = this->edge_record[CB_id].origin_id;
		int B_id = this->edge_record[BA_id].origin_id;
		
		int f_BCD = this->edge_record[BD_id].face_id;
		int f_ABD =	this->edge_record[DB_id].face_id;

		// For BD edge		
		this->edge_record[BD_id].origin_id = A_id;
		this->edge_record[BD_id].nextedge_id = CB_id;
		this->edge_record[BD_id].prevedge_id = BA_id;
		
		// For DB edge
		this->edge_record[DB_id].origin_id = C_id;
		this->edge_record[DB_id].nextedge_id = AD_id;
		this->edge_record[DB_id].prevedge_id = DC_id;
		
		// AD
		this->edge_record[AD_id].nextedge_id = DC_id;
		this->edge_record[AD_id].prevedge_id = DB_id;
		
		// DC
		this->edge_record[DC_id].nextedge_id = DB_id;
		this->edge_record[DC_id].prevedge_id = AD_id;
		this->edge_record[DC_id].face_id = f_ABD;
		
		// CB
		this->edge_record[CB_id].nextedge_id = BA_id;
		this->edge_record[CB_id].prevedge_id = BD_id;
		
		// BA
		this->edge_record[BA_id].nextedge_id = BD_id;
		this->edge_record[BA_id].prevedge_id = CB_id;
		this->edge_record[BA_id].face_id = f_BCD;
		
		this->vertex_record[B_id].edge_id = BA_id;
		this->vertex_record[D_id].edge_id = DC_id;		
		
		this->face_record[f_ABD].edge_id = AD_id;
		this->face_record[f_BCD].edge_id = CB_id;
		
		std::vector<int> adj_edges = {AD_id,DC_id,CB_id,BA_id};					
		return adj_edges;
	}
	// Two triangles ABD and BDC with a common edge BD and its twin DB ion the middle.
	// The CCW order of vertices is A, D, C, B
	bool DCEL::isDelaunay(int BD_id){
		int DC_id = this->edge_record[BD_id].nextedge_id;
		int CB_id = this->edge_record[DC_id].nextedge_id;
	
		int DB_id = this->edge_record[BD_id].twinedge_id;
		int BA_id = this->edge_record[DB_id].nextedge_id;
		int AD_id = this->edge_record[BA_id].nextedge_id;
		
		int f_BCD = this->edge_record[BD_id].face_id;
		int f_ABD =	this->edge_record[DB_id].face_id;
		
		std::vector<Point> Quad;		// In anti-clockwise order
		Quad.push_back(this->vertex_record[this->edge_record[AD_id].origin_id].point);		//	Point A
		Quad.push_back(this->vertex_record[this->edge_record[DC_id].origin_id].point);		//	Point D
		Quad.push_back(this->vertex_record[this->edge_record[CB_id].origin_id].point);		//	Point C
		Quad.push_back(this->vertex_record[this->edge_record[BA_id].origin_id].point);		//	Point B
		
		if(!isConvex(Quad)){
			return true;
		}
		
		Point centre1 = circumcentre(Quad[0],Quad[1],Quad[3]);
		Point centre2 = circumcentre(Quad[1],Quad[2],Quad[3]);
//		std::cout << Quad[0] << " " << Quad[1] << " " << Quad[3] << "\t" << centre1 <<"\n";
//		std::cout << Quad[1] << " " << Quad[2] << " " << Quad[3] << "\t" << centre2 <<"\n";
		
		if(euclideanDistance(centre1,Quad[2]) < euclideanDistance(centre1,Quad[0]))
			return false;
		else if(euclideanDistance(centre2,Quad[0]) < euclideanDistance(centre2,Quad[1]))
			return false;
		
		return true;
	}
	
	/**
	A function to join an inner point of a face to a vertex on the boundary of the face in DCEL.
	<b> Input: </b>	Inner Point(as Point object), vertex id of vertex on boundary, and face id. <br>
	<b> Output: </b> returns nothing, joins the point to the vertex on the boundary in DCEL.
	*/
	void DCEL::addInnerVertex(const cg::Point& inner,const int vid,const int fid){
			int n_vertices = this->vertex_record.size();
			int n_edges = this->edge_record.size();

			cg::vertex newVertex;
			cg::edge Edge1,Edge2;
			
			int v_nextEdge = findEdge(vid,fid);	// next edge of vid in inner face
			int v_prevEdge = this->edge_record[v_nextEdge].prevedge_id;
				
			
			Edge1.origin_id = vid;
			Edge1.face_id   = fid;
			Edge1.nextedge_id = Edge1.twinedge_id = n_edges+1;
			Edge1.prevedge_id = v_prevEdge;
			
			Edge2.origin_id = n_vertices;
			Edge2.face_id = fid;
			Edge2.nextedge_id = v_nextEdge;
			Edge2.prevedge_id = Edge2.twinedge_id = n_edges;
			
			
			newVertex.point = inner;
			newVertex.edge_id = n_edges+1;
			
			this->vertex_record.push_back(std::move(newVertex));
			this->edge_record.push_back(std::move(Edge1));
			this->edge_record.push_back(std::move(Edge2));			
			
			this->edge_record[v_prevEdge].nextedge_id = n_edges;
			this->edge_record[v_nextEdge].prevedge_id = n_edges+1;			
	}

	/**
	A function to find the index of next vertex of a given vertex in a face.
	<b> Input: </b>	Index of the current vertex and index of the common face.
	<b> Output: </b> Index of the next vertex in the same face.
	*/
	int DCEL::nextVertex(int vid,int fid){
		int eid = this->findEdge(vid,fid);
		eid = this->edge_record[eid].nextedge_id;
		return this->edge_record[eid].origin_id;
	}
	/**
	A function to extract all polygons from DCEL.
	<b> Input: </b>	None.
	<b> Output: </b> A 2D vector of indexes of vertices of polygon. Each vector in 2D vector corresponds to one polygon in DCEL.
	*/
	std::vector<std::vector<int> > DCEL::extractAllPolygons(void){
		std::vector<std::vector<int> > polygon;		// contains all polygons, polygon[i] refers to the ith polygon
		
		for(int i=1;i< (this->face_record).size();i++){
			std::vector<int> vertex_ids = this->verticesOfFace(i);		// contains ids of all vertices in ith face
			polygon.push_back(vertex_ids);
		}
		return polygon;
	}
	/**
	A function to find the common face between two vertices.
	<b> Input:  </b> Two indexes of the two vertices in the vertex table(vertex_record). <br>
	<b> Output: </b> index of the common face in face table(face_record) if only one common face exists. If there is no common
	face or more than one common faces, it returns -1.
	*/
	int DCEL::commonFace(const int vid1,const int vid2){
		// create visited array for the faces
		int f_size = face_record.size();
		bool visited[f_size];
		std::fill(visited,visited+f_size,false);
		
		std::vector<int> edges_ID1 = edgesOfVertex(vid1);
		std::cout << "\nEdges of Vertex " << vid1 <<": ";
		for(auto x:edges_ID1){
			std::cout << x <<" ";
			visited[edge_record[x].face_id]=true;
		}
		std::cout << "\n";
		std::vector<int> edges_ID2 = edgesOfVertex(vid2);
		
		std::vector<int> common;
		for(auto x:edges_ID2){
			if(edge_record[x].face_id!=0 && visited[edge_record[x].face_id])		// exclude outer face i.e f[0]
				common.push_back(edge_record[x].face_id);
		}
		std::cout <<"\nCommon Faces:\t";
		for(auto x:common) std::cout << x <<" ";
		std::cout <<"\n";
		
		if(common.size()==0){
			std::cerr << "No common face b/w " << vid1 << " & " << vid2 << "\n";
			exit(1);
		}
		else if(common.size()==1){
			return common[0];
		}
		else if(common.size()==2){
			return common[1];
		}
		
		return -1;
	}
	
	/**
	A function to find the edge on the boundary of a face, originating from a vertex.
	<b> Input:  </b> index of a face in the face_record, index of a vertex in the vertex_record <br>
	<b> Output: </b> index of the edge from the input vertex, on the boundary of the input face.
	*/
	int DCEL::findEdge(int vid,int fid){
		std::vector<int> edges_vid = edgesOfVertex(vid);
		std::cout << "\nEdges with vertex " << vid << ":\t";
		for(auto x:edges_vid){
			std::cout << x <<" ";
			if(edge_record[x].face_id == fid){
				return x;
			}
		}
		std::cout << "\n";
		this->printEdgeRecord();
		std::cerr << "No edge with vertex " << vid << " & face " << fid <<"\n";
		return -1;
	}
	
	/**
	A bool function to check if two vertces are adjacent.
	<b> Input:  </b> indexes of two vertices in the vertex_record. <br>
	<b> Output: </b> <em> true </em> if the two vertices are adjacent, <em> false </em> otherwise.
	*/
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

	/**
	An empty Constructor.
	*/
	DCEL::DCEL(){;}
	
	/**
	A constructor to build DCEL from a simple polygon(in Anti-clockwise order).
	<b> Input: </b> A vector of objects of Point class, representing a polygon in Anti-clockwise order. <br>
	<b> Output: </b> none.
	*/
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
		std::cout << "DCEL constructed\n";
	}
	
	/**
	A function to find all vertices of a face.
	<b> Input:  </b> index of a face in the face_record. <br>
	<b> Output: </b> A vector of indexes of all vertices on the boundary of the face.
	*/
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
	
	/**
	A function to find all edges originating from a vertex.
	<b> Input:  </b> index of a vertex in the vertex_record. <br>
	<b> Output: </b> A vector of indexes of all edges originating from the vertex.
	*/
	std::vector<int> DCEL::edgesOfVertex(int vid){
		if(vid >= this->vertex_record.size()){
			std:: cout << vid << ">" << vertex_record.size() <<"\n";
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
	/**
	A function to add an edge(two half-edges) between two vertices.
	These vertices must be non-adjacent and must have a common face. <br>
	<b> Input: </b> indexes of two vertices which need to be connected with a diagonal(two twin half-edges). <br>
	<b> Output: </b> none.
	*/
	// Add an edge between two vertices. Two half edges are formed between vertex(vid1) and vertex(vid2).
	void DCEL::addEdge(const int vid1,const int vid2){
		
		if(adjacentVertices(vid1,vid2)){
			std::cout << "Edge already exists b/w " << vid1 <<" & " << vid2 <<"\n";
			return;
		}
		
		int	fid = this->commonFace(vid1,vid2);
		int eid1 = this->findEdge(vid1,fid);
		int eid2 = this->findEdge(vid2,fid);		
		std::cout << "\nAdded edge b/w " << vid1 << " & " << vid2 << "\n";
		
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
		
		while(eid1!=indexh2){
			edge_record[eid1].face_id = face_record.size()-1;
			eid1 = edge_record[eid1].nextedge_id;
		}
	}
	
	
// ****************************************************************************	
	// ONLY FOR DEBUGGING
	
	/**
	A function to print vertex table of the DCEL.
	<b> Input: </b> none. <br>
	<b> Output: </b> none.
	*/
	void DCEL::printVertexRecord(void){
		std::cout << "Point\t" << "One edge\n";
		for(auto x:vertex_record){
			std::cout << x.point << "\t" << x.edge_id <<"\n";
		}
	}
	
	/**
	A function to print edge table of the DCEL.
	<b> Input: </b> none. <br>
	<b> Output: </b> none.
	*/
	void DCEL::printEdgeRecord(void){
		std::cout << "Edge_ID\t" << "Orig_ID\t" << "Twin_ID\t" << "Face_ID\t" << "Next_ID\t" << "Prev_ID\n" ;
		int i=0;
		for(auto x:edge_record){
			std::cout << i++ <<"\t"<<x.origin_id<<"\t"<<x.twinedge_id<<"\t"<<x.face_id<<"\t"<<x.nextedge_id<<"\t"<<x.prevedge_id<<"\n";
		}
	}
	
	/**
	A function to print face table of the DCEL.
	<b> Input: </b> none. <br>
	<b> Output: </b> none.
	*/
	void DCEL::printFaceRecord(void){
		std::cout << "Face_ID\t" << "One edge\n";
		int i=0;
		for(auto x:face_record){
			std::cout << i++ << "\t" << x.edge_id <<"\n";
		}
	}
}
