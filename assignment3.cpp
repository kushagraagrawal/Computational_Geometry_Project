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
		
		Point top_most = ch[0],bottom_most = ch[ch.size()-1];
		
		for(ll i=1;i<ch.size();i++){
			if(ch[i].y > top_most.y)
				top_most = ch[i];
			else if(ch[i].y==top_most.y)
				if(ch[i].x < top_most.x)
					top_most = ch[i];
					
			if(ch[i].y < bottom_most.y)
				bottom_most = ch[i];
			else if(ch[i].y == bottom_most.y)
				if(ch[i].x < bottom_most.y)
					bottom_most = ch[i];
		}
		DCEL D(ch);
		
		/*
		 * Finding the top and bottom vid
		 * */
		int vidtop,vidbot;
		for(ll i=0;i<D.vertex_record.size() -1 ;i++){
			if(D.vertex_record[i].point == top_most)
				vidtop = i;
			else if(D.vertex_record[i].point == bottom_most)
				vidbot = i;
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
