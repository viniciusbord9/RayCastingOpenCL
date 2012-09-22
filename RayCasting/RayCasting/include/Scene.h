#pragma once
#include <vector>
#include <stdlib.h>
#include "SceneObject.h"
#include "Camera.h"
#include "Color.h"

using namespace std;

typedef struct Object{
    cl_float3 center;
    cl_uint4 color;
    float radius;
}obj;

typedef struct S{
    int count_objects;
    cl_uint4 background;
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

