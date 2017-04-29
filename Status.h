/** \file
Contains the function declaration of the Status used for polygon monotonization
*/
#ifndef STATUS_H_INCLUDED
#define STATUS_H_INCLUDED

#include<map>
#include<utility>
#include "Point.h"
#include "Utility.h"

namespace cg {
	/**
	A wrapper class of std::map in STL to implement the <b>Status</b> data-structure in SweepLine algorithms.
	It can be used to store the line-segments(along with their Helper) to the left of an event point in Monotonization module, to set or
	retrieve the helper of an edge in the current status, and to find the nearest edge to the left of an event point.
	*/
	class Status {
		private:
			struct compareEdge {
				/**
				A fucntion to order the edges in the status.
				*/
				bool operator() (const std::pair<cg::Point, cg::Point>& lhs, const std::pair<cg::Point, cg::Point>& rhs) {
					int dir = cg::turn_direction(rhs.first, rhs.second, lhs.first);
					return (dir == 1);
				}
			};
			/**
			An ordered map to store the edges in status.
			*/
			std::map< std::pair<cg::Point, cg::Point>, int, compareEdge> M;
			
		public:
			/**
			 * Function to insert a new edge and its helper into the status
			 * <b> Input: </b> The edge to be inserted and its helper
			 * <b> Output: </b> none
			 * */
			void insert(const std::pair<cg::Point, cg::Point>& edgeNew, int helper);
			/**
			 * Function to remove an edge from the status
			 * <b> Input: </b> The edge to be removed
			 * <b> Output: </b> none
			 * */
			void remove(const std::pair<cg::Point, cg::Point>& edgeRem);
			/**
			 * Function to find the edge to the left the point passed as a parameter
			 * <b> Input: </b> The point whose edge is to be found
			 * <b> Output: </b> The edge to the left of the point 'v' 
			 * */
			std::pair<cg::Point, cg::Point> findEdgeToLeft(const cg::Point& v);
			
			/**
			 * Function to return the helper of the edge passed as a parameter
			 * <b> Input: </b> The edge in question
			 * <b> Output: </b> returns the helper of the edge in question. Else returns -1
			 * */
			int getHelper(const std::pair<cg::Point, cg::Point>& edgeQuery);
			/**
			 * Function to set the helper of a given edge to the helper passed as a parameter
			 * <b> Input: </b> The edge whose helper is to be set and the helper 
			 * <b> Output: </b> none
			 * */
			void setHelper(const std::pair<cg::Point, cg::Point>& edgeQuery, int helper);
			/**
			 * Print function for the status
			 * */
			void print();
	};

}

#endif
