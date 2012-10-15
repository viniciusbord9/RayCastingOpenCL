#include <CL/cl.h>
#include <CL/opencl.h>
#include <CL/cl_platform.h>

#ifndef STRUCTS_OPENCL_INCLUDED
#define STRUCTS_OPENCL_INCLUDED

typedef struct V{
    float x;
    float y;
    float z;
}vector_struct;

typedef struct C{
    vector_struct forward;
    vector_struct up;
    vector_struct right;
    vector_struct pos;
}camera_struct;

typedef struct SO{
    vector_struct center;
    float radius;

}sceneobject;

typedef struct S{
    camera_struct *c;
    sceneobject so[3];

}scene_struct;


#endif // STRUCTS_OPENCL_INCLUDED
