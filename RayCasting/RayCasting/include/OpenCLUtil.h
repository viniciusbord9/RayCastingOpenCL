#ifndef OPENCLUTIL_H
#define OPENCLUTIL_H
#include <CL/opencl.h>


class OpenCLUtil
{
    public:
        OpenCLUtil();
        virtual ~OpenCLUtil();
        static size_t shrRoundUp( int group_size, int global_size );
    protected:
    private:

};

#endif // OPENCLUTIL_H
