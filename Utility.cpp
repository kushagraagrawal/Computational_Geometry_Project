#include "Utility.h"
namespace cg{
	/**
	Function to read a set of points from file and
	store it in a vector.
	*/
	void readPointSet(char *file_name, std::vector<Point> & vect){
		std::ifstream file(file_name);
		if(!file.is_open()){
			std::cerr << "Input File \"" << file_name << "\" not found !!\n";
			exit(1);
		}
		cg::Point p;
		while((file >> p)){
			vect.push_back(p);
		}
	}
	
	/**
	Function to write a set of points
	from a vector to an output file.
	*/
	void writePointSet(char *file_name, const std::vector<Point> & vect){
		std::ofstream file(file_name);
		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		for(auto it=vect.begin();it!=vect.end();it++){
			file << *it << "\n";
		}
	}

	/**
	Function to find the turning direction of a	set of three points in the sequence p,q,r.
	It returns 1 for LEFT turn, 0 for COLLINEARITY and, -1 for RIGHT turn
	*/
	int turn_direction(const Point& p, const Point& q, const Point& r){
		// determinant value
		double det = (1*(q.x*r.y - q.y*r.x) - p.x*(1*r.y - q.y*1) + p.y*(1*r.x - q.x*1));
		if (det == 0.0){
			return 0;
		}
		else if (det > 0.0){
			return 1;
		}
		else return -1;
	}
	
	/**
	Function to find the euclidean distance between
	two points in Cartesian coordinate system.
	*/
	double euclideanDistance(const Point &a,const Point &b){
		return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
	}
	
	/**
	Function to find the polar angle of two points
	in cartesian coordinate system.
	*/
	double polarAngle(const Point &a,const Point &b){
		double angle = atan2(double(a.y-b.y),double(a.x-b.x));
		return ((angle>=0)?angle:(angle + 2*PI));
	}
}
