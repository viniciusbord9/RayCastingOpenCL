#ifndef STRUCTS_OPENCL_INCLUDED
#define STRUCTS_OPENCL_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <CL/cl.h>
#include <CL/opencl.h>
#include <CL/cl_platform.h>
#include "Vector.h"

typedef struct{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}color;

typedef struct C{
    cl_float3 right;
    cl_float3 forward;
    cl_float3 up;
    cl_float3 pos;
}camera;

typedef struct O{
    cl_float3 center;
    float radius;
}scene_object;

typedef struct S{
    camera cam;
    scene_object obj[4];
    color cor;
}scene;



#endif // STRUCTS_OPENCL_INCLUDED
