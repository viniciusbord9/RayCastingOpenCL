#include "../include/OpenCLUtil.h"

OpenCLUtil::OpenCLUtil()
{
    //ctor
}

OpenCLUtil::~OpenCLUtil()
{
    //dtor
}

size_t
OpenCLUtil::shrRoundUp( int group_size, int global_size ){
     int r = global_size % group_size;
     if( r == 0 )
           return global_size;

     return global_size + group_size - r;
}
