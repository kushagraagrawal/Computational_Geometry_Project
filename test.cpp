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

	cg::DCEL D(P);

	cg::make_monotone(D);
	
return 0;
}
