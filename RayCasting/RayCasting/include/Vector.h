#pragma once
#include <stdlib.h>
#include "Structs_OpenCL.h"
class Vector
{
public:
	Vector(double x, double y, double z);
	virtual ~Vector(void);
    vector_struct cast_struct();
	double x;
	double y;
	double z;


};

