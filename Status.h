#ifndef STATUS_H_INCLUDED
#define STATUS_H_INCLUDED

#include<map>
#include<utility>
#include "Point.h"
#include "Utility.h"

namespace cg {	
	class Status {
		private:	
			struct compareEdge {
				bool operator() (const std::pair<cg::Point, cg::Point>& lhs, const std::pair<cg::Point, cg::Point>& rhs) {
					int dir = cg::turn_direction(rhs.first, rhs.second, lhs.first);
					return (dir == 1);
				}
			};
			std::map< std::pair<cg::Point, cg::Point>, int, compareEdge> M;
			
		public:
			void insert(const std::pair<cg::Point, cg::Point>& edgeNew, int helper = -1);
			void remove(const std::pair<cg::Point, cg::Point>& edgeRem);
			std::pair<cg::Point, cg::Point> findEdgeToLeft(const cg::Point& v);
			int getHelper(const std::pair<cg::Point, cg::Point>& edgeQuery);
			void setHelper(const std::pair<cg::Point, cg::Point>& edgeQuery, int helper);
	};

}

#endif
