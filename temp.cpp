#include<iostream>
#include<vector>
#include<numeric>
#include<utility>
#include "Point.h"

namespace cg{
	double crossproduct(cg::Point v2,cg::Point v1){
		return ((v2.x * v1.y) - (v1.x * v2.y));
	}
	bool checkifintersect(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment){
		
		double dy = halfline.second.y - halfline.first.y;
		double dx = halfline.second.x - halfline.first.x;
		cg::Point v1(halfline.first.x - segment.first.x, halfline.first.y - segment.first.y);
		cg::Point v2(segment.second.x - segment.first.x, segment.second.y - segment.first.y);
		cg::Point v3(-dy,dx);
		double tempproduct1 = crossproduct(v2,v1);
		double v2array[] = {v2.x,v2.y};
		double v3array[] = {v3.x,v3.y};
		double v1array[] = {v1.x,v1.y};
		double tempproduct2 = std::inner_product(v2array,v2array + 2,v3array,0);
		double tempproduct3 = std::inner_product(v1array,v1array + 2,v3array,0);
		
		double t1 = tempproduct1/tempproduct2;
		double t2 = tempproduct3/tempproduct2;
		
		if(t1>=0 && (t2>=0 && t2<=1))
			return true;
		return false;
	}
	bool Point_of_intersection(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment){
		if(checkifintersect(halfline,segment)){
			cg::Point r(halfline.second.x - halfline.first.x, halfline.second.y - halfline.first.y);
			cg::Point s(segment.second.x - segment.first.x, segment.second.y - segment.first.y);
			cg::Point qpdiff(segment.first.x - halfline.first.x, segment.first.y - halfline.first.y);
			double t = crossproduct(qpdiff,s)/crossproduct(r,s);
			std::cout<<"Point of intersection exists";
			std::cout<<(halfline.first.x + t*r.x)<<" "<<(halfline.first.y + t*r.y);
		}
		else{
			std::cout<<"no point of intersection exists"<<std::endl;
			return false;
		}
	}
	
}
int main(){
	cg::Point origin(1.0,1.0);
	cg::Point A(2.0,2.0);
	std::pair <cg::Point,cg::Point> halfline;
	std::pair <cg::Point,cg::Point> segment;
	cg::Point B(0.5,1.0);
	cg::Point C(0.5,0.0);
	halfline = std::make_pair(origin,A);
	segment = std::make_pair(B,C);
	cg::Point_of_intersection(halfline,segment);
}
