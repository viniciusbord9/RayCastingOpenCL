#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include "CL/cl.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <CL/cl.h>
#include <CL/opencl.h>
#include <CL/cl_platform.h>
#include <SDKCommon.hpp>
#include <SDKApplication.hpp>
#include <SDKCommandArgs.hpp>
#include <SDKFile.hpp>
#include <SDKBitMap.hpp>
#include "Structs_OpenCL.h"
#include "Scene.h"
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Util.h"
#include "Color.h"
#include "SceneObject.h"
#include "OpenCLUtil.h"

#define OUTPUT_IMAGE "RayCastingImage.bmp"

using namespace std;

class RayCasting
{
public:
	RayCasting(int width, int height);
	virtual ~RayCasting(void);
	int render(Scene *scene);
	int parallelRender(Scene *scene);
	Vector* getPoint(int x, int y, Camera *camera);
	double recenter_x(int x);
	double recenter_y(int y);
	Scene* sceneDefault;
	color* traceRay(Ray *r, Scene *scene, int depth);
	SceneObject* minIntersect(Ray *r, Scene *scene);
private:
	static Scene* initSceneDefault();
	static int initAllegro();
	color*** initMatrixImage();
	color*** img;
	int width;
	int height;
	ALLEGRO_BITMAP *bitmap;
};

