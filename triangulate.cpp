#include <iostream>
#include <stack>
#include "Point.h"
#include "Utility.h"
#include "DCEL.h"

namespace cg{
	DCEL triangulate(DCEL p){
		std::sort(p.begin(),p.end(),compareXY);
		/*
		 * split vertices into two chains
		 * */
		 DCEL chain1,chain2;
		 bool flag1=true;
		 bool flag2 = true;
		 stack s;
		 if(s.empty()){
			s.push(p[0]);
			s.push(p[1]);
			for(int i=2;i<p.size();i++){
				DCEL temp = s.pop();
				for(int j=0;j<chain1.size();j++){
					if(p[i] == chain1[j])
						flag1 = true;
					else
						flag1 = false;
					if(temp == chain1[j])
						flag2 = true;
					else{
						flag2 = false;
					}
				}
				if ((flag1 && !flag2)|| (!flag1 && flag2)){
					// pop all vertices from s
					// insert into a diagonal from uj to each popped vertex except the last one
					// push u(j-1) and uj into S
				}
				else{
					//pop one vertex from S
					// pop other vertices from S as long as the diagonals from uj to them are inside P.
					// Push the last vertex that has been popped back into S
					//push uj onto S.
				}
			}
		}
	}
	
}
