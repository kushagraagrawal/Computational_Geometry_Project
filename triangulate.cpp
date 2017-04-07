#include "triangulate.h"
#define LEFT 1
#define RIGHT 2
namespace cg{
	void triangulate(DCEL &D){
		
		int size_face_rec = D.face_record.size();
	  	for(int face=1;face < size_face_rec;face++){
	  	
			std::cout << "Face " << face << "\n";
			
			std::vector<int> points = D.verticesOfFace(face);
			
			for(auto x:points) std::cout << x <<" ";
			std::cout << "\n";
			
			std::vector<int> right,left;
			int top_id=points[0], bottom_id=points[0];
			
			std::cout << "\nAt begin Top:"<< top_id << "\t Bottom:" << bottom_id <<"\n";
			
			for (int i=1;i<points.size();i++){
				if(below(D.vertex_record[top_id].point,D.vertex_record[points[i]].point)){
					std::cout << "Top changed to " << points[i] << "\n";
					top_id = points[i];
				}
				if(below(D.vertex_record[points[i]].point,D.vertex_record[bottom_id].point)){
					std::cout << "Bottom changed to " << points[i] << "\n";
					bottom_id = points[i];
				}
			}
			std::cout << "\nTop:"<< top_id << "\t Bottom:" << bottom_id <<"\n";

			int chain[D.vertex_record.size()];		// 1 for left, 2 for right
			std::fill(chain,chain+D.vertex_record.size(),0);
			
			left.push_back(top_id);
			while(left.back()!=bottom_id){
				int id = D.nextVertex(left.back(),face);
				chain[id]=LEFT;
				left.push_back(id);
			}
			
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
			
			
			std::cout << "\n------------------\n";
			
			
			// merge subroutine. comparing left and right vectors on y-coordinate. use below() function.
			// obtain final list
			/*
			 * now we have two separate chains. 
			 * */
			 vector<int> finallist;
				int left_tra=0,right_tra = 0;
				while (left_tra!=left.size() and right_tra!=right.size()){
					if(D.vertex_record[left[left_tra]].point.y <= D.vertex_record[right[right_tra]].point.y){
							finallist.push_back(left[left_tra]);
							left_tra++;
					}
					else{
						finallist.push_back(right[right_tra]);
						right_tra++;
					}
				}
				
				while(left_tra!=left.size()){
					finallist.push_back(left[left_tra]);
					left_tra++;
				}
				while(right_tra!=right.size()){
					finallist.push_back(right[right_tra]);
					right_tra++;
				}
			 
			 std::stack<int> s;
			 s.push(finallist[0]);
			 s.push(finallist[1]);
			 
			 for(int i =2;i<finallist.size();i++){
				/*
				 * now to figure out if they on 2 different chains or same chain
				 * then perform ops
				 * */
				 int temppoint = s.pop();
				 if(chain[temppoint]!= chain[i]){
					D.addEdge(temppoint,i);
					while(s.size()>1){
						
						something.addEdge(s.pop(),i);
					}
					s.push(finallist[i-1]);
					s.push(finallist[i]);
				 }
				 else{
					//D.addEdge(temppoint,i);
					while(1){
						temppoint = s.pop();
						
						
						
						else
						break;
					//keep popping
					//s.push(last vertex popped from s
					//s.push(i);
				 }
					s.push(temppoint);
					s.push(i);
				}
			 }
			//add diagonals to all stack vertices except first and last one to un.
			int i=0,size_of_stack = s.size();
			while(!s.empty()){
				if(i==0){
					i++;
					continue;
				}
				else if(i== size_of_stack -1 )
					break;
				else
					D.addEdge(s.pop(),points[points.size() -1]);
					
			}
			#endif
		}
	
	}
}
