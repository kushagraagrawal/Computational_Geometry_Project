/** \file
* Contains declaration of DCEL data structure and its functions.
*/

#ifndef DCEL_H_INCLUDED
#define DCEL_H_INCLUDED

#include "Point.h"
#include <vector>

namespace cg{
	/**
	A structure to represent a vertex in Doubly conected Edge List(DCEL).
	*/
	struct vertex{
		cg::Point point;	//!< An object of Point class to store the coordinates of the vertex.
		int edge_id;		//!< An integer denoting the index of an arbitrary half-edge in edge_record, with the vertex as origin.
	};
	
	/**
	A structure to represent a face in Doubly conected Edge List(DCEL). <br>
	*/
	struct face{
		int edge_id;	//!< An integer denoting the index of an arbitrary half-edge on the boundary of the face.
	};
	
	/**
	A structure to represent an half-edge in Doubly conected Edge List(DCEL). <br>
	*/
	
	struct edge{
		int origin_id;		//!< the index of the origin vertex of the half-edge.
		int twinedge_id;	//!< the index of twin of the half-edge.
		int face_id;		//!< the index of the incident face(i.e the face to the left) of the half-edge.
		int nextedge_id;	//!< the index of the next half-edge on the boundary of the incident face.
		int prevedge_id;	//!< the index of the previous half-edge on the boundary of the incident face.
	};
	
	/**
	A DCEL is a data-structure used to represent the planar sub-division.
	Salient features: <br>
	<ul>
		<li> A DCEL stores a list of half-edges, a list of vertices, and a list of faces. </li>
		<li> These lists are unordered but interconnected by various pointers/indexes inside other lists.</li>
		<li> Edges(half-edges) are oriented in Anti-clockwise direction inside each face. </li>
		<li> Each edge is represented by two half-edges, one for each face. </li>
	</ul>
	*/
	class DCEL{
		public:
			std::vector<vertex> vertex_record;	//!< A vertex table to store all vertices.
			std::vector<face> face_record;		//!< A face table to store all faces.
			std::vector<edge> edge_record;		//!< An edge table to store all half-edges.
			
			DCEL();	//!< An empty Constructor.
			~DCEL();//!< A Deconstructor.
			DCEL(const std::vector<cg::Point> &point_set); 	//!< A constructor to build DCEL from a simple polygon(in Anti-clockwise order).
			std::vector<int> verticesOfFace(int fid);		//!< A function to find all vertices of a face.
			std::vector<int> edgesOfVertex(int vid);		//!< A function to find all edges originating from a vertex.	 
			int commonFace(const int vid1,const int vid2); 	//!< A function to find the common face between two vertices.
			void addEdge(const int vid1,const int vid2);	//!< A function to add an edge(two half-edges) between two vertices.
			int findEdge(int vid,int fid);			//!< A function to find the edge on the boundary of a face, originating from a vertex.
			bool adjacentVertices(const int vid1,const int vid2); //!< A bool function to check if two vertces are adjacent.
			
			// Only for debugging purpose
			void printVertexRecord(void);	//!< A function to print vertex table of the DCEL.
			void printEdgeRecord(void);		//!< A function to print edge table of the DCEL.
			void printFaceRecord(void);		//!< A function to print face table of the DCEL.
	};
}


#endif
