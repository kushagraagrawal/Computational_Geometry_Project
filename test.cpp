#include <set>
#include <utility>
#include "Point.h"
#include "Utility.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"

namespace cg {

	/**
	Function to write all edges of DCEL to output file
	*/
	void writeEdges(cg::DCEL D,char *output_filename){
		int n_edges = D.edge_record.size();
		bool valid[n_edges];
		std::fill(valid,valid+n_edges,true);
		
		std::ofstream file(output_filename);

		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		else{
			std::cout << "Opened file " << output_filename << "\n";
		}
		for(int i=0;i<n_edges;i++){
			if(valid[i]){
				int p1_id = D.edge_record[i].origin_id;
				int twin_id = D.edge_record[i].twinedge_id;
				int p2_id = D.edge_record[twin_id].origin_id;
				cg::Point p1 = D.vertex_record[p1_id].point;
				cg::Point p2 = D.vertex_record[p2_id].point;				
				file << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
				valid[twin_id]=false;
			}
		}
	}
}


int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);
	cg::DCEL D(P);
	cg::Point pt(5,3);
	D.addInnerVertex(pt,7,1);
	cg::writeEdges(D, argv[2]);	
/*	cg::make_monotone(D);
	cg::writeEdges(D, argv[2]);
	cg::triangulate(D);
	cg::writeEdges(D, argv[3]);
*/
	return 0;
}


