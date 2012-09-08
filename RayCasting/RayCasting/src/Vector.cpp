#include "../include/Vector.h"


Vector::Vector(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector_struct
Vector::cast_struct(){
    vector_struct *v = (vector_struct*) malloc(sizeof(vector_struct));
    v->x = this->x;
    v->y = this->y;
    v->z = this->z;
}

Vector::~Vector(void)
{
}
