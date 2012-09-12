#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "CL/cl.hpp"
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

