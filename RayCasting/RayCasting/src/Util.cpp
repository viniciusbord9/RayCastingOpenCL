#include "../include/Util.h"


Util::Util(void)
{
}

Vector*
Util::make(double x, double y, double z){
	return new Vector(x,y,z);
}

Vector*
Util::minus(Vector *w, Vector *v){
	return new Vector((w->x - v->x),(w->y - v->y),(w->z - v->z));
}

Vector*
Util::plus(Vector *w, Vector *v){
	return new Vector((w->x + v->x),(w->y + v->y),(w->z + v->z));
}

double
Util::mult(Vector *w, Vector *v){
	return ((w->x * v->x)+(w->y * v->y)+(w->z * v->z));
}

Vector*
Util::mult_scalar(Vector *v, double n){
	return new Vector((v->x * n),(v->y * n),(v->z * n));
}


Vector*
Util::normal(Vector *v){
	double mag = Util::mag(v);
    double n = mag == 0 ? HUGE_VAL : 1 / mag;
    return mult_scalar(v, n);
}

double
Util::mag(Vector *v){
	return sqrt(mult(v,v));
}

Vector*
Util::cross(Vector *w, Vector *v)
{
            return new Vector(((w->y * v->z) - (w->z * v->y)),
                              ((w->z * v->x) - (w->x * v->z)),
                              ((w->x * v->y) - (w->y * v->x)));
}

Util::~Util(void)
{
}
