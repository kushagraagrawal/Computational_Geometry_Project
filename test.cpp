#include<bits/stdc++.h>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "Utility.h"
#include "Status.h"
using namespace std;

int main(){
	int n;
	cin >> n;
	std::vector<cg::Point> P(n);
	for(int i=0;i<n;i++){
		cin >> P[i].x >> P[i].y;
	}
	// cosntruct DCEL D from P
	cg::DCEL D(P);
	
	// Make all polygons in D monotone
	cg::make_monotone(D);
	
	// Extract all monotone polygons from D
	std::vector< std::vector<cg::Point> > P_all;		// contains all monotone polygons from D
	for(int i=1;i<D.face_record.size();i++){
		std::vector<int> v_id = D.verticesOfFace(i);		// contains ids of all vertices in ith face
		std::vector<cg::Point> P;
		for(auto x:v_id){
			P.push_back(D.vertex_record[x].point);
		}
		P_all.push_back(P);
	}
	
	// Print all monotone polygons
	for(auto x:P_all){
		for(auto p:x){
			std::cout << p << " ";
		}
		std::cout << "\n";
	}
return 0;
}
