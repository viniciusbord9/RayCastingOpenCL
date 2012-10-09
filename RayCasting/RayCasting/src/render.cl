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
    float3 dst = obj.center - r.origin;
    float a = dot(dst, r.destiny);
    float b = dot(dst, dst) - (obj.radius * obj.radius);
    float c = a*a - b;
    if(c > 0.0f){
		return 1;
    }

	return 0;
}

float recenterX(float x, float width){
    return (x - (width/2.0))/(2.0 * width);
}

float recenterY(float y, float height){
    return (-(y - (height/2.0))/(2.0 * height));
}

float3 getPoint(float width, float height, float x, float y,camera c)
{
     float3 v1 = recenterX(x,width) * c.right;
     float3 v2 = recenterY(y,height) * c.up;
     float3 v3 = v1 + v2;
     float3 v4 = v3 + c.forward;
     //printf("\n %f %f %f",v1.x, v1.y, v1.z);
     return normalize(v4);
}


__kernel void render(__global scene *s,__global camera *c,__global obj *list_objects,const int width,const int height,__write_only image2d_t image)
{
    int2 coord = (int2) (get_global_id(0),get_global_id(1));
    //printf("\n %d", width);
    //write_imageui(image,coord,(uint4)(255, 0, 0, 1));
    //printf("\n %f %f %f",c->forward.x, c->forward.y, c->forward.z);
    float3 v1 = getPoint((float) width,(float) height,(float) coord.x,(float) coord.y,*c);
    ray r = {c->pos, v1};
    size_t i = 0;
    uint4 color;
    //printf("\n%f, %f, %f ", v1.x, v1.y, v1.z);
    color = (uint4) ((uint) s->background.x , (uint) s->background.y, (uint) s->background.z, (uint) s->background.w);
    while(i < s->count_objects){
        //printf("%d",i);
        if(intersect(r,list_objects[i]) == 1){
             color = (uint4) ((uint) list_objects[i].color.x + color.x , (uint) list_objects[i].color.y + color.y, (uint) list_objects[i].color.z + color.z, list_objects[i].color.w + color.w);
        }
        i++;
    }
    write_imageui(image,coord,color);
    //write_imageui(image,coord,(uint4)(0, 255, 0, 1));
}
