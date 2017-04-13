#include "Status.h"

namespace cg {
	void Status::insert(const std::pair<cg::Point, cg::Point>& edgeNew, int helper) {
		M.insert(std::make_pair(edgeNew, helper));
	}
	
	void Status::remove(const std::pair<cg::Point, cg::Point>& edgeRem) {
		auto x = M.find(edgeRem);
		if (x != M.end()) M.erase(x);
	}
	
	int Status::getHelper(const std::pair<cg::Point, cg::Point>& edgeQuery) {
		auto x = M.find(edgeQuery);
		if (x != M.end())
			return x->second;
		else
			return -1;
	}
	
	void Status::setHelper(const std::pair<cg::Point, cg::Point>& edgeQuery, int helper) {
		auto x = M.find(edgeQuery);
		if (x != M.end()) x->second = helper;
	}
	
	std::pair<cg::Point, cg::Point> Status::findEdgeToLeft(const cg::Point& v) {
		auto x = M.upper_bound(std::make_pair(v, cg::Point(0,0)));
		if (x != M.end()) return x->first;
	}
	void Status::print(){
		std::cout <<"map\n";
		for(auto tp:M){
			std::cout << tp.first.first <<" " <<tp.first.second <<" "<<tp.second<<"\n";
		}
	}
}
