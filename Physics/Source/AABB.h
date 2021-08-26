#ifndef AABB_H
#define AABB_H
#include "Vector3.h"
class AABB
{
public:
	Vector3 min;
	Vector3 max;
	AABB(Vector3 min, Vector3 max)
	{
		this->min = min;
		this->max = max;
	}
	
};

#endif