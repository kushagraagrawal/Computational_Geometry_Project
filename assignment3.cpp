#include <iostream>
#include <set>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "triangulate.h"
#include "Utility.h"
#include "ConvexHull.h"
#define ll long long int

namespace cg{

	void assignment3(std::vector<Point> &point_set){
		std::vector<Point> ch;
		ch = convexHullAndrews(point_set);
	
		std::vector<Point>interiorPoints;
		std::vector<Point>::iterator it;
		
		it = std::set_difference(point_set.begin(),point_set.end(),ch.begin(),ch.end(),interiorPoints.begin());
		interiorPoints.resize(it - interiorPoints.begin());
		
		std::sort(interiorPoints.begin(),interiorPoints.end(),compareXY);

		Point left_most = ch[0],right_most = ch[0];
		 
		for(ll i=1;i<ch.size();i++){
			if(ch[i].x > right_most.x)
				right_most = ch[i];
			else if(ch[i].x==right_most.x)
				if(ch[i].y > ch[i].y)
					right_most = ch[i];
		}
		DCEL D(ch);
		/*
		* We now have the left and right most point on the Convex Hull.
		* The interior Points are sorted according to their X coordinates
		* */
		for(ll i=0;i<interiorPoints;i++){
		D.addInnerVertex(interiorPoints[i],/*vid of points*/,1)
		}
		triangulate(D);
		
	}
}
