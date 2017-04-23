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
		
		std::sort(interiorPoints.begin(),interiorPoints.end(),compareYX);

		/*
		 * find the top most and the bottom most points
		 * */
		DCEL D(ch);
		int vtopid = 0,vbotid = 0;
		for(ll i =1;i<ch.size();i++){
			if(below(D.vertex_record[vtopid].point,D.vertex_record[i].point)){
//					std::cout << "Top changed to " << points[i] << "\n";
					vtopid = ch[i];
				}
			if(below(D.vertex_record[i].point,D.vertex_record[vbotid].point)){
//				std::cout << "Bottom changed to " << points[i] << "\n";
				vbotid = ch[i];
			}
		}
		
		/*
		 * adding to DCEL 
		 * */
		D.addInnerVertex(interiorPoints[0],top_most,1);
		for(ll i=1;i<interiorPoints-1;i++){
			D.addInnerVertex(interiorPoints[i],D.vertex_record[D.vertex_record.size()-1],1);
		}
		D.addEdge(D.vertex_record[D.vertex_record.size()-1],vidbot);
		triangulate(D);
		
	}
}
