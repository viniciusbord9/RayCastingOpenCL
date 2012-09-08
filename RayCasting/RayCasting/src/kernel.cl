typedef struct Camera{
    float2 forward;
    float2 up;
    float2 right;
    float2 down;
}camera;

typedef struct Ray{
    float2 origin;
    float2 destiny;

}ray;

typedef struct SceneObject{
    float2 center;
    float radius;

}sceneObject;

int intersect(ray r){
    return 0;
}

typedef struct Scene{
    camera c;
    sceneObject so[3];

}scene;


__kernel void render(__global scene *s,int width,const int height)
{
    size_t tid = get_global_id(0);

}

