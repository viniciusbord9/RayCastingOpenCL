#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "CL/cl.hpp"
#include "Vector.h"
#include "Util.h"

typedef struct C{
    cl_float3 pos;
    cl_float3 forward;
    cl_float3 up;
    cl_float3 right;
}camera;

class Camera
{
public:
	Camera(void);
	Camera(Vector *pos,Vector *lookat);
	camera* cast_struct();
	virtual ~Camera(void);
	Vector *pos;
	Vector *forward;
	Vector *up;
	Vector *right;
};

