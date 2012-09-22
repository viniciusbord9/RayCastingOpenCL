#include "../include/Scene.h"
#include "../include/Sphere.h"


Scene::Scene(color *background)
{
	this->objts = new vector<SceneObject*>();
	this->background = background;
}

scene*
Scene::cast_struct(){
    scene *s = (scene*) malloc(sizeof(scene));
    s->background.x = (cl_uint) this->background->R;
    s->background.y = (cl_uint) this->background->G;
    s->background.z = (cl_uint) this->background->B;
    s->background.w = 0;
    s->count_objects = this->getObjects()->size();
    return s;
}

obj*
Scene::cast_objects(){
    obj* list_object = (obj*) malloc (this->objts->size()*sizeof(obj));
    for(int i = 0; i < this->objts->size(); i++){
        Sphere *obj = (Sphere*) this->objts->at(i);
        list_object[i].center.x = (cl_float) obj->center->x;
        list_object[i].center.y = (cl_float) obj->center->y;
        list_object[i].center.z = (cl_float) obj->center->z;
        cl_float r = (cl_float) obj->radius;
        list_object[i].radius = r;
        int R = (cl_uint) obj->cor->R;
        int G = (cl_uint) obj->cor->G;
        int B = (cl_uint) obj->cor->B;
        cl_uint4 color = {(cl_uint) R , (cl_uint) G, (cl_uint) B , (cl_uint) 0};
        list_object[i].color = color;


    }
    return list_object;
}


Scene::~Scene(void)
{
}


vector<SceneObject*>*
Scene::getObjects(){
    return this->objts;
}
