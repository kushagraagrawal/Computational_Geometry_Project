/** \file
* Contains declaration of DCEL data structure and its functions
*/

#ifndef DCEL_H_INCLUDED
#define DCEL_H_INCLUDED

#include "Point.h"
#include <vector>
namespace cg{
	struct vertex{
		cg::Point point;
		int edge_id;
	};
	struct face{
		int edge_id;
	};
	struct edge{		// half-edge
		int origin_id;
		int twinedge_id;
		int face_id;
		int nextedge_id;
		int prevedge_id;
	};
	class DCEL{
		public:
			std::vector<vertex> vertex_record;
			std::vector<face> face_record;
			std::vector<edge> edge_record;
			
			DCEL();
			~DCEL();
			DCEL(const std::vector<cg::Point> &point_set);
			std::vector<int> verticesOfFace(int fid);
			std::vector<int> edgesOfVertex(int vid);
			void split_face(int eid,int vid);
			
			// Only for debugging purpose
			void printVertexRecord(void);
			void printEdgeRecord(void);
			void printFaceRecord(void);

	};
}


#endif
