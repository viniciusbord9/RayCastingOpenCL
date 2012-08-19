#include "include/Camera.h"


Camera::Camera(Vector *pos, Vector *lookat)
{
	this->forward = Util::normal(Util::minus(lookat, pos));
	Vector down(0 , -1, 0);
	this->right = Util::mult_scalar(Util::normal(Util::cross(this->forward,&down)), 1.5);
	this->up = Util::mult_scalar(Util::normal(Util::cross(this->forward,this->right)), 1.5);
	this->pos = pos;

}



Camera::~Camera(void)
{
}
