#include "Scene.h"


Scene::Scene(color *background)
{
	this->objts = new vector<SceneObject*>();
	this->background = background;
}


Scene::~Scene(void)
{
}


vector<SceneObject*>*
Scene::getObjects(){
    return this->objts;
}
