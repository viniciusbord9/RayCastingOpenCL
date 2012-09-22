#pragma OPENCL EXTENSION cl_amd_printf : enable
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

typedef struct Object{
    float3 center;
    uint4 color;
    float radius;

}obj;

typedef struct S{
    int count_objects;
    uint4 background;
}scene;

int intersect(ray r,obj obj){
    float3 dst = {(r.origin.x - obj.center.x ),(r.origin.y - obj.center.y ),(r.origin.z - obj.center.z)};
    float a = (dst.x * r.destiny.x) + (dst.y * r.destiny.y) + (dst.z * r.destiny.z);
    float b = (dst.x * dst.x) + (dst.y * dst.y) + (dst.z * dst.z) - (obj.radius * obj.radius);
    float c = a*a - b;
    if(c > 0)
		return 1;

	return 0;
}


__kernel void render(__global scene *s,__global camera *c,__global obj *list_objects, int width,int height,__write_only image2d_t image)
{
    int2 coord = (int2) (get_global_id(0),get_global_id(1));
    //printf("\n %d %d",coord.x, coord.y);
    //write_imageui(image,coord,(uint4)(255, 0, 0, 1));
    if(coord.x < width && coord.y < height){
        float3 v1 = c->right * ((coord.x - (width/2.0))/(2.0 * width));
        float3 v2 = c->up *  (-1*(coord.y - (height/2.0))/(2.0 * height));
        float3 v3 = v1 + v2;
        float3 v4 = c->forward + v3;
        float3 v5 = normalize(v4);
        ray r = {c->pos, v5};
        int i = 0;
        uint4 color;
        while(i < s->count_objects){
            if(intersect(r,list_objects[i]) == 1){
                 printf("achou");
                 color = (uint4) ((uint) list_objects[i].color.x , (uint) list_objects[i].color.y, (uint) list_objects[i].color.z, list_objects[i].color.w);
            }else{
                 color = (uint4) ((uint) s->background.x , (uint) s->background.y, (uint) s->background.z, (uint) s->background.w);
            }
            i++;
        }
        write_imageui(image,coord,color);
        //write_imageui(image,coord,(uint4)(0, 255, 0, 1));
    }
}
