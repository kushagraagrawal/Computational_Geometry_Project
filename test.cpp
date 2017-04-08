#include <set>
#include <utility>
#include "Point.h"
#include "Utility.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"

namespace cg {
void writeAllEdges(const cg::DCEL& D, char* output_filename) {
	int n_faces = D.face_record.size();
	std::set<std::pair<int,int>> temp, temp_reverse;
	for(int f = 1; f < n_faces; f++) {
		std::vector<int> v = D.verticesOfFace(f);
		for(i = 0; i< v.size(); i++){
			auto edge = std::make_pair(v[i],v[(i+1)%v.size()), edge_ = std::make_pair(v[(1+1)%v.size()],v[i]);
			auto x = temp.find(edge), x_ = temp_reverse.find(egde_);
			if(x == temp.end() and x_ == temp_reverse.end()){
				temp.insert(edge);
				temp_reverse.insert(edge_);
			}
		}
	}
	std::ofstream file(output_filename);
	if(!file.is_open()){
		std::cerr << "Output File not found\n";
		exit(1);
	}
	file << std::setprecision(15);
	for(auto it = temp.begin(); it != temp.end(); it++){
		file << D.vertex_record[it->first].point.x << " " << D.vertex_record[it->first].point.y << " " << D.vertex_record[it->second].point.x << " " << D.vertex_record[it->second].point.y;
	}
}
}


int main(int argc, char* argv[]) {
	std::vector<cg::Point> P;
	cg::readPointSet(argv[1],P);
	cg::DCEL D(P);
	cg::make_monotone(D);
	cg::writeAllEdges(D, argv[2]);
	cg::triangulate(D);
	cg::writeAllEdges(D, argv[3]);
	return 0;
}


