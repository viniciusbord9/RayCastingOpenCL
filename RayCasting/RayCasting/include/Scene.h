#pragma once
#include <vector>
#include "SceneObject.h"
#include "Camera.h"
#include "Color.h"

using namespace std;

class Scene
{
public:
	Scene(color *c);
	virtual ~Scene(void);
	vector<SceneObject*>* getObjects();
	vector<SceneObject*> *objts;
	Camera *camera;
	color *background;
};

