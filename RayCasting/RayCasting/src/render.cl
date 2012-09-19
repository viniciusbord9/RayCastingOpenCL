typedef struct{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}color;

typedef struct C{
    float3 pos;
    float3 forward;
    float3 up;
    float3 right;
}camera;

typedef struct Ray{
    float3 origin;
    float3 destiny;

}ray;

int intersect(ray r){
    return 0;
}

typedef struct Object{
    float3 center;
    float radius;

}obj;

typedef struct S{
    unsigned char background[3];
}scene;


__kernel void render(__global scene *s,__global camera *c,__global obj *list_objects, int width,int height,__write_only image2d_t image)
{
    int2 coord = (int2) (get_global_id(0),get_global_id(1));
    write_imageui(image,coord,(uint4)(0, 0, 0, 1));

}
