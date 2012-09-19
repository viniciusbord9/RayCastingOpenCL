#include "../include/Camera.h"


Camera::Camera(Vector *pos, Vector *lookat)
{
	this->forward = Util::normal(Util::minus(lookat, pos));
	Vector down(0 , -1, 0);
	this->right = Util::mult_scalar(Util::normal(Util::cross(this->forward,&down)), 1.5);
	this->up = Util::mult_scalar(Util::normal(Util::cross(this->forward,this->right)), 1.5);
	this->pos = pos;

}

camera*
Camera::cast_struct(){
    camera *c = (camera*) malloc(sizeof(camera));

    c->pos.x = (cl_float) this->pos->x;
    c->pos.y = (cl_float) this->pos->y;
    c->pos.z = (cl_float) this->pos->z;

    c->right.x = (cl_float) this->right->x;
    c->right.y = (cl_float) this->right->y;
    c->right.z = (cl_float) this->right->z;

    c->up.x = (cl_float) this->up->x;
    c->up.y = (cl_float) this->up->y;
    c->up.z = (cl_float) this->up->z;

    c->forward.x = (cl_float) this->forward->x;
    c->forward.y = (cl_float) this->forward->y;
    c->forward.z = (cl_float) this->forward->z;

    return c;

}


Camera::~Camera(void)
{
}
