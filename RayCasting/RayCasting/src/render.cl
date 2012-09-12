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


float3
normal(float3 v){
    float3 w1 = (v.x * v.x) + (v.y + v.y) + (v.z + v.z);
    float value = w1.x + w1.y + w1.z;
    float mag = sqrt(value);
    float n = mag == 0 ? HUGE_VAL : 1 / mag;
    float3 w = v * n;
    return w;
}

__kernel void render(__global scene *s,__global camera *c,__global obj *list_objects, int width,int height,__write_only image2d_t image)
{
    int2 coord = (int2) (get_global_id(0),get_global_id(1));
    if(coord.x < width && coord.y < height){
        float3 v1 = c->right * ((coord.x - (width/2.0))/(2.0 * width));
        float3 v2 = c->up * (-(coord.y - (height/2.0))/(2.0 * height));
        float3 v3 = v1 + v2;
        float3 v4 = c->forward + v3;
        v4 = normal(v4);
        ray r = {c->pos, v4};
    }

}
