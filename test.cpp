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
	std::vector< std::vector<int> > polygon = D.extractAllPolygons();
	
	for(auto p:polygon){
		for(int id:p){
			cout << D.vertex_record[id].point << " ";
		}
		cout << "\n";
	}
return 0;
}
