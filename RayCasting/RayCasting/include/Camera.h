#pragma once
#include "Vector.h"
#include "Util.h"

class Camera
{
public:
	Camera(void);
	Camera(Vector *pos,Vector *lookat);
	virtual ~Camera(void);
	Vector *pos;
	Vector *forward;
	Vector *up;
	Vector *right;
};

