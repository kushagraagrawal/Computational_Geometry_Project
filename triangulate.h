#ifndef TRIANGULATE_H_INCLUDED
#define TRIANGULATE_H_INCLUDED

#include<iostream>
#include<vector>
#include "Point.h"
#include "DCEL.h"
#include "Ymonotone.h"
#include "Utility.h"

namespace cg{

	void triangulate(cg::DCEL &D);
	
}
#endif
