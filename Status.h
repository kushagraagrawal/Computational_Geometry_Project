#ifndef STATUS_H_INCLUDED
#define STATUS_H_INCLUDED
#include <map>
#include <utility>
#include <algorithm>
#include "Point.h"
#include "Utility.h"

namespace cg {	
	class Status {
		private:
			struct compareEdge {
				bool operator() (const std::pair<cg::Point, cg::Point>& lhs, const std::pair<cg::Point, cg::Point>& rhs) {
					double y_ref = std::min(lhs.first.y,rhs.first.y);
					double x_lhs = lhs.first.x - (lhs.first.x - lhs.second.x)/(lhs.first.y - lhs.second.y)*(lhs.first.y - y_ref);
					double x_rhs = rhs.first.x - (rhs.first.x - rhs.second.x)/(rhs.first.y - rhs.second.y)*(rhs.first.y - y_ref);
					return x_lhs < x_rhs;
				}
			};
			std::map< std::pair<cg::Point, cg::Point>, int, compareEdge> M;
			
		public:
			void insert(const std::pair<cg::Point, cg::Point>& edgeNew, int helper = -1);
			void remove(const std::pair<cg::Point, cg::Point>& edgeRem);
			std::pair<cg::Point, cg::Point> findEdgeToLeft(const cg::Point& v);
			int getHelper(const std::pair<cg::Point, cg::Point>& edgeQuery);
			void setHelper(const std::pair<cg::Point, cg::Point>& edgeQuery, int helper);
						/**
			 * Print function for the status
			 * */
			void print();
	};
	

}
#endif
