#pragma once
#include <vector>
#include <stdlib.h>
#include "Structs_OpenCL.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Color.h"

using namespace std;

class Scene
{
public:
	Scene(color *c);
	virtual ~Scene(void);
	scene_struct* cast_struct();
	vector<SceneObject*>* getObjects();
	vector<SceneObject*> *objts;
	Camera *camera;
	color *background;
};

