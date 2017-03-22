#ifndef YMONOTONE_H_INCLUDED
#define YMONOTONE_H_INCLUDED

#include "DCEL.h"
#include "Status.h"
#include "Utility.h"
#include "Point.h"
#include <queue>

#define START_VERTEX	0
#define END_VERTEX		1
#define SPLIT_VERTEX	2
#define MERGE_VERTEX	3
#define REG_VERTEX		4

namespace cg{
	void make_monotone(cg::DCEL &D);
	bool below(const cg::Point &A,const cg::Point &B);
	
	void handle_start_vertex(cg::DCEL &D,int index,cg::Status &tau);
	void handle_end_vertex(cg::DCEL &D,int index,cg::Status &tau);
	void handle_split_vertex(cg::DCEL &D,int index,cg::Status &tau);
	void handle_merge_vertex(cg::DCEL &D,int index,cg::Status &tau);
	void handle_regular_vertex(cg::DCEL &D,int index,cg::Status &tau);
}

#endif
