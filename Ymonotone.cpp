#include "Ymonotone.h"
#include "DCEL.h"
#include "Status.h"
#include "Utility.h"
#include "Point.h"
#include <queue>
#include <utility>

namespace cg{
	// return true if A lies below B, using sweep_line comparison
	bool below(const cg::Point &A,const cg::Point &B){
		return ((A.y < B.y) or ( (A.y==B.y and A.x > B.x)));
	}


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
	
	void handle_start_vertex(cg::DCEL &D,int index,cg::Status &tau){
		std::pair<cg::Point,cg::Point> edge;
		const int v_size = D.vertex_record.size();
		edge.first  = D.vertex_record[index].point;
		edge.second = D.vertex_record[(index+1)%v_size].point;
		tau.insert(edge,index);
	}

	void handle_end_vertex(cg::DCEL &D,int index,cg::Status &tau){
		std::pair<cg::Point,cg::Point> edge;
		const int v_size = D.vertex_record.size();
		edge.first  = D.vertex_record[(index-1+v_size)%v_size].point;
		edge.second = D.vertex_record[index].point;
		int helper = tau.getHelper(edge);
		if(helper == MERGE_VERTEX)
			D.addEdge(index,helper);
		tau.remove(edge);
	}
	
	void handle_split_vertex(cg::DCEL &D,int index,cg::Status &tau){
		cg::Point v = D.vertex_record[index].point;
		auto edge = tau.findEdgeToLeft(v);
		int helper = tau.getHelper(edge);
		D.addEdge(index,helper);
		tau.setHelper(edge,index);
		
		std::pair<cg::Point,cg::Point> edge_i;
		edge_i.first = v;
		int v_size = D.vertex_record.size();
		edge_i.second = D.vertex_record[(index+1)%v_size].point;
		tau.insert(edge_i,index);
		
	}
	void handle_merge_vertex(cg::DCEL &D,int index,cg::Status &tau){
		handle_end_vertex(D,index,tau);	
		cg::Point v = D.vertex_record[index].point;
		auto edge = tau.findEdgeToLeft(v);
		int helper = tau.getHelper(edge);
		if(helper == MERGE_VERTEX){
			D.addEdge(index,helper);
		}
		tau.setHelper(edge,index);	
	}
	void handle_regular_vertex(cg::DCEL &D,int index,cg::Status &tau){
		bool interior_right;
		int v_size = D.vertex_record.size();
		cg::Point prev = D.vertex_record[(index-1+v_size)%v_size].point;
		cg::Point curr = D.vertex_record[index].point;
		cg::Point next = D.vertex_record[(index+1)%v_size].point;
		if(below(next,curr) and below(curr,prev))
			interior_right = true;
		else
			interior_right = false;
		if(interior_right){
			handle_end_vertex(D,index,tau);
			handle_start_vertex(D,index,tau);			
		}
		else{
			cg::Point v = D.vertex_record[index].point;
			auto edge = tau.findEdgeToLeft(v);
			int helper = tau.getHelper(edge);
			if(helper == MERGE_VERTEX){
				D.addEdge(index,helper);
			}
			tau.setHelper(edge,index);	
		}
	}
	
	void make_monotone(cg::DCEL &D){
		
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
			switch(vertex_type[index]){
				case START_VERTEX:	handle_start_vertex(D,index,tau);
									break;
				case END_VERTEX:	handle_end_vertex(D,index,tau);
									break;
				case SPLIT_VERTEX:	handle_split_vertex(D,index,tau);
									break;
				case MERGE_VERTEX:	handle_merge_vertex(D,index,tau);
									break;					
				case REG_VERTEX:	handle_regular_vertex(D,index,tau);
									break;
			}
		}
		D.printVertexRecord();
		D.printEdgeRecord();
		D.printFaceRecord();
	}

}