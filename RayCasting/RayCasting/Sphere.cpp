#include "Sphere.h"


Sphere::Sphere(Vector *center, double radius):SceneObject()
{
	this->center = center;
	this->radius = radius;
}

int
Sphere::intersect(Ray *r){
	Vector *dst = new Vector((r->origin->x - this->center->x),(r->origin->y - this->center->y),(r->origin->z - this->center->z));
	double a = Util::mult(dst,r->direction);
	double b = Util::mult(dst,dst) - (this->radius*this->radius);
	double c = a*a - b;

	if(c > 0)
		return 1;

	return 0;


}

Sphere::~Sphere(void)
{
}
