#include "../include/Scene.h"


Scene::Scene(color *background)
{
	this->objts = new vector<SceneObject*>();
	this->background = background;
}


Scene::~Scene(void)
{
}

scene_struct*
Scene::cast_struct(){
    camera_struct *cam = (camera_struct*) malloc(sizeof(camera_struct));
    cam->pos = this->camera->pos->cast_struct();
    cam->forward = this->camera->forward->cast_struct();
    cam->right = this->camera->right->cast_struct();
    cam->up = this->camera->up->cast_struct();

    scene_struct *s = (scene_struct*) malloc(sizeof(scene_struct));
    s->c = cam;
    return s;
}

vector<SceneObject*>*
Scene::getObjects(){
    return this->objts;
}
