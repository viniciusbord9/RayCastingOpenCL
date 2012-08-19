#pragma once
#include <iostream>
#include "Color.h"
#include "Ray.h"

using namespace std;

class SceneObject
{
public:
	SceneObject(void);
	virtual ~SceneObject(void);
	virtual int intersect(Ray *r) = 0;
	color *cor;

};

