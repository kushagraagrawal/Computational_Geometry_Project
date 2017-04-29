#include "kernel.h"
#include <string>
#define next_ccw(l,it) (std::next(it) != l.end())?std::next(it):l.begin()
#define next_cw(l,it) (it != l.begin())?std::prev(it):std::prev(l.end())

/**
A function to compute the cross product of two 2-D vectors.
<b> Input: </b>	Two points v1 and v2. <br>
<b> Output: </b> Returns the magnitude of the cross product of two 2-D vectors.
*/
double cg::Kernel::crossproduct(cg::Point v2,cg::Point v1){
		return ((v2.x * v1.y) - (v1.x * v2.y));
}

/**
A function to check whether a halfline and a line segment intersect
<b> Input: </b>	Two pairs of points - one for representing the halfline and the other representing a line segment <br>
<b> Output: </b> Returns a bool indicating if the halfline and the line segment intersect.
*/
bool cg::Kernel::checkifintersect(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment){
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

/**
A function to get the intersection of a halfline and a line segment.
<b> Input: </b>	Two pairs of points - one for representing the halfline and the other representing a line segment, and a pointer to a point
in which the intersection is stored. <br>
<b> Output: </b> Returns a bool indicating if the halfline and the line segment intersect.
*/
bool cg::Kernel::get_intersection(std::pair<cg::Point,cg::Point> halfline, std::pair<cg::Point,cg::Point> segment,  cg::Point& w){
		if(checkifintersect(halfline,segment)){
			cg::Point r(halfline.second.x - halfline.first.x, halfline.second.y - halfline.first.y);
			cg::Point s(segment.second.x - segment.first.x, segment.second.y - segment.first.y);
			cg::Point qpdiff(segment.first.x - halfline.first.x, segment.first.y - halfline.first.y);
			double t = crossproduct(qpdiff,s)/crossproduct(r,s);
			w = cg::Point(halfline.first.x + t*r.x, halfline.first.y + t*r.y);
			std::cout << "Halfline: " << halfline.first << halfline.second << ", Segment: " << segment.first << segment.second << ", Intersection: " << w << std::endl;
			return true;
		}
		else return false;
}

/**
A constructor which initializes the kernel with a bounding box.
<b> Input: </b>	A single point. <br>
<b> Output: </b> None.
*/
cg::Kernel::Kernel(const cg::Point& v) {
	double __INF = 10e3;
	K.push_back(cg::Point(__INF,__INF));
	K.push_back(cg::Point(-__INF,__INF));
	K.push_back(cg::Point(-__INF,-__INF));
	K.push_back(cg::Point(__INF,-__INF));
	polygon.push_back(v);
	F = K.begin(); L = K.begin();
}

/**
A function to cut the kernel between two points in counterclockwise direction.
<b> Input: </b>	Iterators to points in the kernel indicating the starting and ending points of the region to be cut. <br>
<b> Output: </b> None.
*/
void cg::Kernel::cut_kernel(const std::list<cg::Point>::iterator& x1, const std::list<cg::Point>::iterator& x2) {
	auto x = x1;
	while(x != x2){
		x = K.erase(x);
		if(x == K.end()) x = K.begin();
	}
	std::cout << "Cut Kernel.\n";
}

/**
A function to update the kernel by adding the next point in the polygon.
<b> Input: </b>	The next point in the polygon in counterclockwise direction. <br>
<b> Output: </b> None.
*/
void cg::Kernel::update(const cg::Point& v){
	if(K.size() < 3) return;
	polygon.push_back(v);
	std::cout << "No. of pts: " << polygon.size() << std::endl;
	std::list<cg::Point>::iterator x, x1, x2;
	if(polygon.size() < 3) {
		cg::Point w1, w2;
		x = K.begin();
		std::cout << "Step 1 started." << K.size() << std::endl;
		std::cout << *(polygon.rbegin()) << "--->" << *(polygon.rbegin() + 1) << std::endl;
		while(true) {
			std::cout << *x << "---" << *(next_ccw(K,x)) << "  ";
			if(get_intersection(std::make_pair(*(polygon.rbegin()), *(polygon.rbegin() + 1)), std::make_pair(*x,*(next_ccw(K,x))), w1))
				x1 = next_ccw(K,x);
			x = next_ccw(K,x);
			std::cout << w1 << std::endl;
			if (x == K.begin()){
				x1 = K.insert(x1,w1);
				break;
			}
		}
		while(true) {
			std::cout << *x << "---" << *(next_ccw(K,x)) << "  ";
			if(get_intersection(std::make_pair(*(polygon.rbegin() + 1), *(polygon.rbegin())), std::make_pair(*x,*(next_ccw(K,x))), w2))
				x2 = next_ccw(K,x);
			x = next_ccw(K,x);
			std::cout << w2 << "  " << std::endl;
			if (x == K.begin()){
				x2 = K.insert(x2,w2);
				break;
			}
		}
		std::cout << "Step 1" << std::endl; 
		cut_kernel(next_ccw(K,x1),x2);
		std::cout << "Step 1" << std::endl; 
		F = x1; L = x2;
		return;
	}
	int convex_test = cg::turn_direction(*(polygon.rbegin() + 2),*(polygon.rbegin() + 1), *(polygon.rbegin()));
	std::cout << convex_test << std::endl;
	if(convex_test != -1){
		std::cout << "Convex: " << std::endl;
		std::cout << "Processing: " << *(std::next(polygon.rbegin())) << std::endl;
		if(cg::turn_direction(*(polygon.rbegin() + 1), *(polygon.rbegin()), *L) == -1) {
			std::cout << "Case 1.\n";
			cg::Point w1, w2;
			x = L;
			bool intersected = false;
			while(true) {
				if(get_intersection(std::make_pair(*(polygon.rbegin() + 1), *(polygon.rbegin())), std::make_pair(*x,*(next_cw(K,x))),w1)){
					x1 = K.insert(x,w1);
					intersected = true;
					break;
				}
				x = next_cw(K,x);
				if(x == L) break;
			}
			if(not intersected){
				K.erase(K.begin(),K.end());
				return;
			}
			x = L;
			while(true) {
				if(get_intersection(std::make_pair(*(polygon.rbegin() + 1), *(polygon.rbegin())), std::make_pair(*x,*(next_ccw(K,x))),w2)){
					x2 = K.insert(next_ccw(K,x),w2);
					break;
				}
				x = next_ccw(K,x);
				if(x == F) break;
			}
			auto Q = output();
			for(auto it = Q.begin(); it != Q.end(); it++)
				std::cout << *it << std::endl;
			cut_kernel(next_ccw(K,x1),x2);
			x = x2;
			std::cout << "Updating L\n";
			while(x != K.end()) {
				if(cg::turn_direction(v,*x,*(next_ccw(K,x))) == 1){
					L = x;
					break;
				}
				x++;
			}
			std::cout << "Updated L = " << *L << std::endl;
		} else {
			std::cout << "Case 2.\n";
			x = L;
			while(x != K.end()) {
				if(cg::turn_direction(v,*x,*(next_ccw(K,x))) == 1){
					L = x;
					break;
				}
				x++;
			}
		}
		std::cout << "Updating F\n";
		x = F;
		do {
			if(cg::turn_direction(v,*x,*(next_ccw(K,x))) != 1){
				F = x;
				break;
			}
			x = next_ccw(K,x);
		} while(x != F);
		std::cout << "Updated F = " << *F << std::endl;
	} else {
		std::cout << "Reflex.\n";
		std::cout << "Processing: " << *(std::next(polygon.rbegin())) << std::endl;
		if(cg::turn_direction(*(polygon.rbegin() + 1), *(polygon.rbegin()), *F) == -1) {
			cg::Point w1, w2;
			x = F;
			bool intersected = false;
			while(true) {
				if(get_intersection(std::make_pair(*(polygon.rbegin()), *(polygon.rbegin() + 1)), std::make_pair(*x,*(next_ccw(K,x))),w1)){
					x1 = K.insert(next_ccw(K,x),w1);
					intersected = true;
					break;
				}
				x = next_ccw(K,x);
				if(x == F) break;
			}
			if(not intersected){
				K.erase(K.begin(),K.end());
				return;
			}
			x = F;
			while(true) {
				if(get_intersection(std::make_pair(*(polygon.rbegin()), *(polygon.rbegin() + 1)), std::make_pair(*x,*(next_cw(K,x))),w2)) {
					x2 = K.insert(x,w2);
					break;
				}
				x = next_cw(K,x);
				if(x == L) break;
			}
			auto Q = output();
			for(auto it = Q.begin(); it != Q.end(); it++)
				std::cout << *it << std::endl;
			cut_kernel(next_ccw(K,x2),x1);
			F = x2;
			std::cout << "Updated F = " << *F << std::endl;
			}
		else {
			std::cout << "Updating F" << std::endl;
			x = F;
			while(x != K.end()) {
				if(cg::turn_direction(v,*x,*(next_ccw(K,x))) == 1){
					F = x;
					break;
				}
				x++;
			}
			std::cout << "Updated F = " << *F << std::endl;
		}
		std::cout << "Updating L" << std::endl;
		x = L;
		while(x != K.end()) {
			if(cg::turn_direction(v,*x,*(next_ccw(K,x))) == 1){
				L = x;
				break;
			}
			x++;
		}
		std::cout << "Updated L = " << *L << std::endl;
	}
}

/**
A function to update the kernel by closing the polygon.
<b> Input: </b>	None. <br>
<b> Output: </b> None.
*/
void cg::Kernel::close_polygon(){
	update(polygon[0]);
}

/**
A function to output the kernel as a vector of points.
<b> Input: </b>	None. <br>
<b> Output: </b> None.
*/
std::vector<cg::Point> cg::Kernel::output() {
	std::vector<cg::Point> ans;
	for(auto it = K.begin(); it != K.end(); it++)
		ans.push_back(*it);
	return ans;
}

/**
A function to construct the kernel of a polygon.
<b> Input: </b>	A vector of points containing the polygon in counterclockwise direction. <br>
<b> Output: </b> A vector of points containing the kernel in counterclockwise direction.
*/
std::vector<cg::Point> cg::construct_kernel(const std::vector<cg::Point>& P) {
	int n = P.size();
	Kernel K(P[0]);
	std::cout << "Kernel constructed." << std::endl;
	for(int i = 1; i < n; i++){
		K.update(P[i]);
		std::cout << "Added pt #" << i << std::endl;
		auto Q = K.output();
		for(auto it = Q.begin(); it != Q.end(); it++)
			std::cout << *it << std::endl;
		std::string str = std::to_string(i) + "_test1.txt";
		cg::writePointSet(&str[0u],Q);
	}
	K.close_polygon();
	return K.output();
}
