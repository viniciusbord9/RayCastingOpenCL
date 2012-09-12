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
    s->background[0] = this->background->R;
    s->background[1] = this->background->G;
    s->background[2] = this->background->B;
    return s;
}

obj*
Scene::cast_objects(){
    obj* list_object = (obj*) malloc (this->objts->size()*sizeof(obj));
    for(int i = 0; i < this->objts->size(); i++){
        Sphere *obj = (Sphere*) this->objts->at(i);
        cl_float3 center = {(cl_float) obj->center->x,(cl_float) obj->center->y, (cl_float) obj->center->z};
        list_object[i].center = center;
        list_object[i].radius = obj->radius;
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
