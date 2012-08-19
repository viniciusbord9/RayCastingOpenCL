#pragma once
#include "SceneObject.h"
#include "Ray.h"
#include "Vector.h"
#include "Util.h"

class Sphere : public SceneObject
{
public:
	Sphere(void);
	Sphere(Vector *center, double radius);
	~Sphere(void);
	int intersect(Ray *r);
	Vector *center;
	double radius;
};

