/** \file
Contains the function definition of the Status used for polygon monotonization
*/
#include "Status.h"

namespace cg {
	/**
	 * Function to insert a new edge and its helper into the status
	 * <b> Input: </b> The edge to be inserted and its helper
	 * <b> Output: </b> none
	 * */
	void Status::insert(const std::pair<cg::Point, cg::Point>& edgeNew, int helper) {
		M.insert(std::make_pair(edgeNew, helper));
	}
	/**
	 * Function to remove an edge from the status
	 * <b> Input: </b> The edge to be removed
	 * <b> Output: </b> none
	 * */
	void Status::remove(const std::pair<cg::Point, cg::Point>& edgeRem) {
		auto x = M.find(edgeRem);
		if (x != M.end()) M.erase(x);
	}
	/**
	 * Function to return the helper of the edge passed as a parameter
	 * <b> Input: </b> The edge in question
	 * <b> Output: </b> returns the helper of the edge in question. Else returns -1
	 * */
	int Status::getHelper(const std::pair<cg::Point, cg::Point>& edgeQuery) {
		auto x = M.find(edgeQuery);
		if (x != M.end())
			return x->second;
		else
			return -1;
	}
	/**
	 * Function to set the helper of a given edge to the helper passed as a parameter
	 * <b> Input: </b> The edge whose helper is to be set and the helper 
	 * <b> Output: </b> none
	 * */
	void Status::setHelper(const std::pair<cg::Point, cg::Point>& edgeQuery, int helper) {
		auto x = M.find(edgeQuery);
		if (x != M.end()) x->second = helper;
	}
	/**
	 * Function to find the edge to the left the point passed as a parameter
	 * <b> Input: </b> The point whose edge is to be found
	 * <b> Output: </b> The edge to the left of the point 'v' 
	 * */
	std::pair<cg::Point, cg::Point> Status::findEdgeToLeft(const cg::Point& v) {
		auto x = M.upper_bound(std::make_pair(v, cg::Point(0,0)));
		if (x != M.end()) return x->first;
	}
	/**
	 * Print function for the status
	 * */
	void Status::print(){
		std::cout <<"map\n";
		for(auto tp:M){
			std::cout << tp.first.first <<" " <<tp.first.second <<" "<<tp.second<<"\n";
		}
	}
}
