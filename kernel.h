#ifndef KERNEL_H
#define KERNEL_H

#include "Point.h"
#include "Utility.h"
#include <vector>
#include <list>
#include<numeric>
#include <iostream>
#include <utility>
#include <math.h>
#include <iterator>

namespace cg {

class Kernel {
	public:
		Kernel(const cg::Point& v);
		void update(const cg::Point &v);
		void close_polygon();
		std::vector<cg::Point> output();
		
	private:
		std::list<cg::Point> K;
		std::list<cg::Point>::iterator F, L;
		std::vector<cg::Point> polygon;
		bool get_intersection(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment, cg::Point& w);
		void cut_kernel(const std::list<cg::Point>::iterator& x1, const std::list<cg::Point>::iterator& x2);
		
		double crossproduct(cg::Point v2,cg::Point v1);
		bool checkifintersect(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment);
};

std::vector<cg::Point> construct_kernel(const std::vector<cg::Point>& P);

}

#endif
