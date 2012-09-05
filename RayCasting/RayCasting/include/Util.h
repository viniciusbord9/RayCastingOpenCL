#pragma once
#include "Vector.h"
#include <math.h>
class Util
{
public:
	Util(void);
	virtual ~Util(void);
	static Vector* make(double x, double y, double z);
	static Vector* minus(Vector *w, Vector *v);
	static Vector* plus(Vector *w, Vector *v);
	static double mult(Vector *w, Vector *v);
	static Vector* mult_scalar(Vector *v, double n);
	static double mag(Vector *v);
	static Vector* normal(Vector *v);
	static Vector* cross(Vector *w, Vector *v);

};

