/** \file
Contains implementation of triangulation function.
*/

#include "triangulate.h"

namespace cg{
	/**
	A function to triangulate all the y-monotone polygons stored in a DCEL. <br>
	All partitions stored in the DCEL should be y-monotone, for correct output.<br>
	<b> Input: </b> A DCEL object D. <br>
	<b> Output: </b> returns nothing, triangulates all partitions stored in D, by adding edges to it.
	*/
	void triangulate(cg::DCEL &D){

		int size_face_rec = D.face_record.size();
	  	for(int face=1;face < size_face_rec;face++){
	  	
			std::cout << "Face " << face << "\n";

			std::vector<int> points = D.verticesOfFace(face);
			
			for(auto x:points) std::cout << x <<" ";
			std::cout << "\n"; 
			
			std::vector<int> right,left;
			int top_id=points[0], bottom_id=points[0];
			
//			std::cout << "\nAt begin Top:"<< top_id << "\t Bottom:" << bottom_id <<"\n";
			
			for (int i=1;i<points.size();i++){
				if(below(D.vertex_record[top_id].point,D.vertex_record[points[i]].point)){
//					std::cout << "Top changed to " << points[i] << "\n";
					top_id = points[i];
				}
				if(below(D.vertex_record[points[i]].point,D.vertex_record[bottom_id].point)){
//					std::cout << "Bottom changed to " << points[i] << "\n";
					bottom_id = points[i];
				}
			}
			std::cout << "\nTop:"<< top_id << "\t Bottom:" << bottom_id <<"\n";

			// chain[i] stores whether ith vertex in D lies in the right chain or left chain. chain[i] = -1 for left, 1 for right
			int chain[D.vertex_record.size()];
			std::fill(chain,chain+D.vertex_record.size(),0);

			// Set chain of all vertices in Left chain to LEFT			
			left.push_back(top_id);
			while(left.back()!=bottom_id){
				int id = D.nextVertex(left.back(),face);
				chain[id]=LEFT;
				left.push_back(id);
			}
			
			// Set chain of all vertices in right chain to RIGHT			
			right.push_back(bottom_id);
			while(right.back()!=top_id){
				int id = D.nextVertex(right.back(),face);
				chain[id]=RIGHT;
				right.push_back(id);
			}
			std::reverse(right.begin(),right.end());
			
			std::cout << "Left\t";
			for(auto x:left) std::cout << x <<" ";
			std::cout << "\nRight\t";
			for(auto x:right) std::cout << x <<" ";
			std::cout << "\nChain: ";
			for(auto x:chain) std::cout << x <<" ";
			
			
			// Merge left and right chains into finallist, with y coordinate as priority.
			std::vector<int> finallist;
			int L=1,R=1;		// indexes in left and right chains respectively.
			finallist.push_back(left[0]);
			while (L!=left.size() and R!=right.size()){
				cg::Point L_point = D.vertex_record[left[L]].point;
				cg::Point R_point = D.vertex_record[right[R]].point;
				if(below(R_point,L_point)){
						finallist.push_back(left[L]);
						L++;
				}
				else{
					finallist.push_back(right[R]);
					R++;
				}
			}
			
			while(L!=left.size()){
				finallist.push_back(left[L]);
				L++;
			}
			while(R!=right.size()){
				finallist.push_back(right[R]);
				R++;
			}
			finallist.pop_back();
			
			std::cout << "\nMerged\n";
			for(auto x:finallist) std::cout << x <<" ";
			
			// Add edges in DCEL when needed, to triangulate.
		 	std::stack<int> stck;
			stck.push(finallist[0]);
			stck.push(finallist[1]);
			 
			for(int i=2;i<finallist.size()-1;i++){
				std::cout << "\nIteration i=" << i << "\n";
				//if they on 2 different chains			 
				if(chain[stck.top()]!= chain[finallist[i]]){
					std::cout << stck.top() <<" and " << finallist[i] << " lie on diff chain\n";
					while(!stck.empty()){
						if(stck.size()>1)
							D.addEdge(stck.top(),finallist[i]);
						stck.pop();
					}
					stck.push(finallist[i-1]);
					stck.push(finallist[i]);
				}
				// if they are on same chain
				else{
					std::cout << stck.top() <<" and " << finallist[i] << " lie on same chain\n";
					while(!stck.empty()){
						int top1 = stck.top();
						stck.pop();
						if(stck.empty()){
							stck.push(top1);
							stck.push(finallist[i]);
//							std::cout << "Pushed " << top1 << " & " << finallist[i] <<"\n";
							break;
						}
						int top2 = stck.top();
						
//						std::cout << "Popped " << top1 << " top2 = " << top2 <<"\n"; 
						
						cg::Point curr_point = D.vertex_record[finallist[i]].point;
						cg::Point top1_point = D.vertex_record[top1].point;
						cg::Point top2_point = D.vertex_record[top2].point;
						if(finallist[i]==4){
//						 	std::cout << turn_direction(curr_point,top1_point,top2_point) << "\t=\t" << chain[finallist[i]] << "\n";
						}
						if(turn_direction(curr_point,top1_point,top2_point)==chain[finallist[i]]){
							D.addEdge(finallist[i],top2);
						}
						else{
							stck.push(top1);
							stck.push(finallist[i]);
//							std::cout << "Pushed " << top1 << " & " << finallist[i] <<"\n";
							break;
						}
					}
				}
				std::cout << "Finished i=" << i << "\n------------------------------------\n";
			}
			
			stck.pop();
			while(stck.size()>1){
				D.addEdge(finallist.back(),stck.top());
				stck.pop();
			}
			
		}
	
	}
	
}
