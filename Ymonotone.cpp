/** \file
Contains the function definitions of the monotonization of a regular polygon stored in a DCEL.
*/

#include "Ymonotone.h"
#include "DCEL.h"
#include "Status.h"
#include "Utility.h"
#include "Point.h"
#include <queue>
#include <utility>

namespace cg{

	

	/**
	A function to find the type of the vertex of the simple polygon(i.e start vertex/end vertex/split vertex/merge vertex/regular vertex).
	<b> Input:  </b>	DCEL D which stores the polygon, index of the vertex in vertex_record of DCEL. <br>
	<b> Output: </b>	The type of vertex i.e start vertex/end vertex/split vertex/merge vertex/regular vertex,
						denoted by 0,1,2,3 and 4 respectively.
	*/
	int typeOfVertex(const cg::DCEL &D,int index){
		int v_size = D.vertex_record.size();
		cg::Point prev = D.vertex_record[(index-1+v_size)%v_size].point;
		cg::Point curr = D.vertex_record[index].point;
		cg::Point next = D.vertex_record[(index+1)%v_size].point;
		double interior_angle = polarAngle(prev,curr,next);
		if(below(prev,curr) and below(next,curr) and interior_angle < 180)
			return START_VERTEX;
		else if(below(curr,prev) and below(curr,next) and interior_angle < 180)
			return END_VERTEX;
		else if (below(prev,curr) and below(next,curr) and interior_angle > 180)
			return SPLIT_VERTEX;
		else if (below(curr,prev) and below(curr,next) and interior_angle > 180)
			return MERGE_VERTEX;
		else
			return REG_VERTEX;
	}

	/**
	A function to handle a start vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/	
	void handle_start_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[] ){
		std::pair<cg::Point,cg::Point> edge;
		const int v_size = D.vertex_record.size();
		edge.first  = D.vertex_record[index].point;
		edge.second = D.vertex_record[(index+1)%v_size].point;
		tau.insert(edge,index);
		tau.print();
		std::cout << " Helper of "<< edge.first <<" "<<edge.second<< " set to " << tau.getHelper(edge) <<" (should be " << index <<")\n";
	}

	/**
	A function to handle an end vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/
	void handle_end_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]){
		std::pair<cg::Point,cg::Point> edge;
		const int v_size = D.vertex_record.size();
		edge.first  = D.vertex_record[(index-1+v_size)%v_size].point;
		edge.second = D.vertex_record[index].point;
		int helper = tau.getHelper(edge);
		std::cout << "Helper of " << edge.first << " " <<edge.second << " is " << helper <<"\n";
		if(vertex_type[helper] == MERGE_VERTEX)
			D.addEdge(index,helper);
		tau.remove(edge);
	}

	/**
	A function to handle a split vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/	
	void handle_split_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]){
//		std::cout << "handling split vertex\n";
		
		cg::Point v = D.vertex_record[index].point;
		std::cout << "Point "<< v <<"\n";
		auto edge = tau.findEdgeToLeft(v);
		std::cout <<"Edge\n" <<edge.first <<" " <<edge.second<<"\n";
		int helper = tau.getHelper(edge);
		std::cout << "Helper " << helper <<"\n";
		D.addEdge(index,helper);
		tau.setHelper(edge,index);
		
		std::pair<cg::Point,cg::Point> edge_i;
		edge_i.first = v;
		int v_size = D.vertex_record.size();
		edge_i.second = D.vertex_record[(index+1)%v_size].point;
		tau.insert(edge_i,index);
		
		std::cout << "handled split vertex\n";
	}
	
	/**
	A function to handle a merge vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/	
	void handle_merge_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]){
		handle_end_vertex(D,index,tau,vertex_type);	
		cg::Point v = D.vertex_record[index].point;
		auto edge_left = tau.findEdgeToLeft(v);
		int helper = tau.getHelper(edge_left);
		if(vertex_type[helper] == MERGE_VERTEX){
			D.addEdge(index,helper);
		}
		tau.setHelper(edge_left,index);	
	}
	
	/**
	A function to handle a regular vertex in the polygon.
	<b> Input: </b>  An object of DCEL class i.e D, index of the vertex, an object of Status class. <br>
	<b> Output: </b> none.
	*/	
	void handle_regular_vertex(cg::DCEL &D,int index,cg::Status &tau,const int vertex_type[]){
		bool interior_right;
		int v_size = D.vertex_record.size();
		cg::Point prev = D.vertex_record[(index-1+v_size)%v_size].point;
		cg::Point curr = D.vertex_record[index].point;
		cg::Point next = D.vertex_record[(index+1)%v_size].point;
		if(below(next,curr) and below(curr,prev))
			interior_right = true;
		else
			interior_right = false;
		std::cout << "Interior right: " << interior_right <<"\n";
		if(interior_right){
			handle_end_vertex(D,index,tau,vertex_type);
			handle_start_vertex(D,index,tau,vertex_type);		
		}
		else{
			cg::Point v = D.vertex_record[index].point;
			auto edge = tau.findEdgeToLeft(v);
			int helper = tau.getHelper(edge);
			if(vertex_type[helper] == MERGE_VERTEX){
				D.addEdge(index,helper);
			}
			tau.setHelper(edge,index);	
		}
	}
	
	/**
	A function to partition a simple polygon stored in a DCEL(in Anti-clockwise order),
	into a set of y-monotone polygons, by inserting edges in the DCEL.
	<b> Input: </b> A DCEL D consisting of a simple polygon. <br>
	<b> Output: </b> none.
	*/
	void make_monotone(cg::DCEL &D){
		std::cout << "\n---------------------Monotonizing----------------------\n";
		auto cmp = [](const cg::vertex &A,const cg::vertex &B){
			// return true if A lies below B
			return below(A.point,B.point);
		};
		std::priority_queue<cg::vertex, std::vector<cg::vertex>,decltype(cmp)> Q(cmp);
		
		// Push all vertices into Priority Queue
		int vertex_type[(D.vertex_record).size()];
		for(int i=0;i<(D.vertex_record).size();i++){
			vertex_type[i] = typeOfVertex(D,i);		// type of vertex with ith index, in D's vertex_record
			Q.push(D.vertex_record[i]);
		}
		std::cout << "Vertices successfully pushed into Q\n";
		cg::Status tau;
		while(!Q.empty()){
			cg::vertex v = Q.top();
			Q.pop();
			int index = v.edge_id;		// edge_id is same as vertex_id
			std::cout << "Handling p"<<index <<" " << v.point << "as " << vertex_type[index] <<"\n";
			switch(vertex_type[index]){
				case START_VERTEX:	handle_start_vertex(D,index,tau,vertex_type);
									break;
				case END_VERTEX:	handle_end_vertex(D,index,tau,vertex_type);
									break;
				case SPLIT_VERTEX:	handle_split_vertex(D,index,tau,vertex_type);
									break;
				case MERGE_VERTEX:	handle_merge_vertex(D,index,tau,vertex_type);
									break;					
				case REG_VERTEX:	handle_regular_vertex(D,index,tau,vertex_type);
									break;
			}
			std::cout << "Handled" << v.point << "\n----------------------\n";
		}
		std::cout << "\n---------------------Completed Monotone----------------------\n";
	}

}
