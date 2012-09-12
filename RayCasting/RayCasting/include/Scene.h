#pragma once
#include <vector>
#include <stdlib.h>
#include "SceneObject.h"
#include "Camera.h"
#include "Color.h"

using namespace std;

typedef struct Object{
    cl_float3 center;
    float radius;
}obj;

typedef struct S{
    unsigned int background[3];
}scene;

class Scene
{
public:
	Scene(color *c);
	virtual ~Scene(void);
	scene* cast_struct();
	obj* cast_objects();
	vector<SceneObject*>* getObjects();
	vector<SceneObject*> *objts;
	Camera *camera;
	color *background;
};

