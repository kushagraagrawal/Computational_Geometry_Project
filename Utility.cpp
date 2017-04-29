/** \file
Contains the function definitions of common utility functions.
*/

#include "Utility.h"
#include "DCEL.h"
#include<iomanip>
#include<vector>

namespace cg{
	/**
	 * Function to find if the polygon represented by the set of points is convex or not
	 * <b> Input: </b> Vector of Points P
	 * <b> Output: </b> true if the Polygon is convex. False otherwise
	 * */
	bool isConvex(const std::vector<Point> &P){
		if(P.size()<=2){
			std::cerr << "In isConvex: Polygon has less than 3 edges\n";
			exit(1);
		}
		if(P.size()==3){
			return true;
		}
		int sz = P.size();
		for(int i=0;i<sz;i++){
			double interior_angle = polarAngle(P[i],P[(i+1)%sz],P[(i+2)%sz]);
			if(interior_angle >= 180.00)
				return false;
		}
		return true;
	}
	/**
	 * Function to find the circumcentre of the triangle formed by points A, B, C
	 * <b> Input: </b> Points A,B,C
	 * <b> Output: </b> Circumcentre of the triangle 
	 * */
	Point circumcentre(const Point &A,const Point &B,const Point &C){
		double D =  2*( A.y*C.x + B.y*A.x - B.y*C.x - A.y*B.x -C.y*A.x + C.y*B.x);
		if(D==0){
			std::cerr << A << " " << B <<" & " << C << " are collinear\n";
			exit(1);
		}
		double x_centre = ((double)(B.y-C.y)*(A.x*A.x + A.y*A.y) + (C.y-A.y)*(B.x*B.x + B.y*B.y) + (A.y-B.y)*(C.x*C.x + C.y*C.y)) / (double)D ;
		double y_centre = ((C.x-B.x)*(A.x*A.x + A.y*A.y) + (A.x-C.x)*(B.x*B.x + B.y*B.y) + (B.x-A.x)*(C.x*C.x + C.y*C.y)) / (double)D ;
		return Point(x_centre,y_centre);
	}


	/**
	A bool function to check if first point lies below second point.
	<b> Input: </b>  Two objects of Point class i.e A and B.
	<b> Output: </b> <em> true </em> if Point A lies below Point B(or to the right if both are on same horizontal line),
					 <em> false </em> otherwise.
	*/
	bool below(const cg::Point &A,const cg::Point &B){
		return ((A.y < B.y) or ( (A.y==B.y and A.x > B.x)));
	}

	/**
	Function to write all edges of DCEL to output file
	<b> Input: </b> DCEL D which stores the the planar subdivision, file name to which edges of DCEL are to be written. <br>
	<b> Output: </b> returns nothing, writes the edges of the DCEL to output file in the format "x1 y1 x2 y2", where (x1,y1) and (x2,y2) 		are the end points of an edge.
	*/
	void writeEdges(cg::DCEL D,char *output_filename){
		int n_edges = D.edge_record.size();
		bool valid[n_edges];
		std::fill(valid,valid+n_edges,true);
		
		std::ofstream file(output_filename);

		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		else{
//			std::cout << "Writing DCEL to " << output_filename << "\n";
		}
		for(int i=0;i<n_edges;i++){
			if(valid[i]){
				int p1_id = D.edge_record[i].origin_id;
				int twin_id = D.edge_record[i].twinedge_id;
				int p2_id = D.edge_record[twin_id].origin_id;
				cg::Point p1 = D.vertex_record[p1_id].point;
				cg::Point p2 = D.vertex_record[p2_id].point;				
				file << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
				valid[twin_id]=false;
			}
		}
	}
	
	
	/**
	* Function to read a set of points from file and store it in a vector.
	* <b> Input: </b> File name and set of points. <br>
	* <b> Output: </b> Parses the file "file_name" and writes the point to the vector vect
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
		if(vect.size()==0){
			std::cerr << "\nInput File \"" << file_name << "\" is empty. Please check it.\n";
			exit(1);
		}
	}
	
	/**
	* Function to write a set of points from a vector to an output file.
	* <b> Input: </b> File name and set of points.<br>
	* <b> Output: </b> Writes the vector "vect" to the file "file_name"	
	*/
	void writePointSet(char *file_name, const std::vector<Point> & vect){
		std::ofstream file(file_name);
		if(!file.is_open()){
			std::cerr << "Output File not found\n";
			exit(1);
		}
		file << std::setprecision(15);
		for(auto it=vect.begin();it!=vect.end();it++){
			file << it->x << " " << it->y << "\n";
		}
	}

	/**
	* Function to find the turning direction of a	set of three points in the sequence p,q,r.
	* <b> Input: </b> Three points p,q,r. <br>
	* <b> Output: </b> 1 for Left Turn, 0 if the points are Collinear, -1 for Right Turn.
	*/
	int turn_direction(const Point& p, const Point& q, const Point& r){
		// determinant value
		//double epsilon = 1e-10;
		double det = (1*(q.x*r.y - q.y*r.x) - p.x*(1*r.y - q.y*1) + p.y*(1*r.x - q.x*1));
				if (det == 0.0){
			return 0;
		}
		else if (det > 0.0){
			return 1;
		}
		else return -1;
		/*
		if (det > epsilon){
			return 1;
		}
		else if (det < -epsilon){
			return -1;
		}
		else return 0;
		*/
	}
	
	/**
	* Function to find the euclidean distance between two points in Cartesian coordinate system.
	* <b> Input: </b> 2 points a and b.<br>
	* <b> Output: </b> Euclidean distance between a and b.
	*/
	double euclideanDistance(const Point &a,const Point &b){
		return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
	}
	
	/**
	* Function to find the polar angle of two points in cartesian coordinate system.
	* <b> Input: </b> 2 points i.e. a and b. <br>
	* <b> Output: </b> polar angle between a and b in cartesian coordinate system.
	*/
	double polarAngle(const Point &a,const Point &b){
		return fmod((atan2(double(a.y-b.y),double(a.x-b.x)) + 2*M_PI),2*M_PI)* 180/M_PI;
	}
	
	/**
	* Function to find the interior angle formed by the three points of a simple polygon(in Anti-clockwise order) in cartesian coordinate system.
	* <b> Input: </b> 3 points i.e a, b and c of a simple polygon in anti-clockwise order. <br>
	* <b> Output: </b> Interior angle of the polygon, formed by these three points.
	*/
	double polarAngle(const Point &a,const Point &b,const Point&c){
		double theta1 = polarAngle(b,a);
		double theta2 = polarAngle(c,b);
		return fmod((180.0 + theta1-theta2+360),360);
	}
	
	/**
	* Function to find bottommost point(or leftmost such point in case of a tie) in a point set defined in cartesian space.
	* <b> Input: </b> Vector of points (point_set) .<br>
	* <b> Output: </b> Index of bottommost point(or leftmost point in case of a tie) in the vector point_set.
	*/
	int indexOfBottomLeft(const std::vector<Point> & point_set){
		int min_index=0;
		for(int i=1;i<point_set.size();i++){
			if(point_set[min_index].y > point_set[i].y)
				min_index = i;
			else if((point_set[min_index].y == point_set[i].y) and (point_set[min_index].x > point_set[i].x))
				min_index = i;
		}
		return min_index;
	}
	
	/**
	* Compare two polar points by their theta
	* <b> Input: </b> 2 Polar Points a and b. <br>
	* <b> Output: </b> <ol><li> True if a's angle is less than b's theta or both are equal but a's radius is less than b's radius</li>
	* <li> False otherwise</li></ol>
	*/
	bool compareTheta(const PolarPoint &a,const PolarPoint &b){
		bool condition1 = (a.theta < b.theta);
		bool condition2 = (a.theta == b.theta);
		bool condition3 = (a.r < b.r);
		return (condition1 or (condition2 and condition3));
	}
	
	/**
	* Lambda function used for the sort function in andrews algorithm.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b> <ol> <li> True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger. </li>
	* 						<li> False otherwise. </li>
*					  </ol>
	*/	 
	bool compareXY(const Point& a, const Point& b){
	
		bool condition1 = (a.x > b.x);
		bool condition2 = (a.x == b.x);
		bool condition3 = (a.y > b.y);
		return (condition1 or(condition2 and condition3));
	}
	
	/**
	* Lambda function used for the sort function on y coordinate(larger first), followed by x coordinate in case of a tie.
	* <b> Input: </b> Two points a and b belonging to set of points S. <br>
	* <b> Output: </b> <ol> <li> True if a's x-coordinate is larger than b or if both are same and a's y-coordinate is larger. </li>
	* 						<li> False otherwise. </li>
*					  </ol>
	*/
	bool compareYX(const Point& a, const Point& b){
		
		bool condition1 = (a.y > b.y);
		bool condition2 = (a.y == b.y);
		bool condition3 = (a.y < b.y);
		return (condition1 or(condition2 and condition3)); 
	}
}
