#pragma once
#include "Vector.h"

class Ray
{
public:
	Ray(void);
	virtual ~Ray(void);
	Vector *origin;
	Vector *direction;
};

