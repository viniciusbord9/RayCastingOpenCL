#include "../include/structs_opencl.h"


scene* init_default_scene(color *c, Vector *camera_pos, Vector *camera_up, Vector *camera_forward, Vector *camera_right){
    cl_float3 center1 = {0.0, 1.0, 0.0 };
    scene_object obj1 = {center1,0.5};
    cl_float3 center2 = {0.0, 1.0, 0.0 };
    scene_object obj2 = {center2,0.5};
    scene *s = (scene*) malloc (sizeof(scene));
    s->camera = (camera*) malloc(sizeof(camera));

    s->camera->pos->x = (cl_float) camera_pos->x;
    s->camera->pos->y = (cl_float) camera_pos->y;
    s->camera->pos->z = (cl_float) camera_pos->z;

    s->camera->up->x = (cl_float) camera_up->x;
    s->camera->up->y = (cl_float) camera_up->y;
    s->camera->up->z = (cl_float) camera_up->z;

    s->camera->forward->x = (cl_float) camera_forward->x;
    s->camera->forward->y = (cl_float) camera_forward->y;
    s->camera->forward->z = (cl_float) camera_forward->z;

    s->camera->right->x = (cl_float) camera_right->x;
    s->camera->right->y = (cl_float) camera_right->y;
    s->camera->right->z = (cl_float) camera_right->z;
}



