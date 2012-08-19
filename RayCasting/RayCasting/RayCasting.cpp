#include "include/RayCasting.h"
#define TAM 200


RayCasting::RayCasting(const int width, const int height)
{
	this->width = width;
	this->height = height;
	this->sceneDefault = RayCasting::initSceneDefault();
	if(RayCasting::initAllegro()==0){
        //this->display = al_create_display(width, height);
        this->bitmap = al_create_bitmap(width,height);
	}
}

int
RayCasting::initAllegro(){
    if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
   return 0;
}

Scene*
RayCasting::initSceneDefault(){
	color *background = (color*) malloc (sizeof(color));
	background->R = 0x0;
	background->G = 0x0;
	background->B = 0x0;
	Scene *scene = new Scene(background);
	Vector *origin = new Vector(0,1,0);
	Sphere *sphere = new Sphere(origin, 0.5);
	color *spherecolor = (color*) malloc(sizeof(color));
	spherecolor->R = 0xff;
	spherecolor->G = 0x0;
	spherecolor->B = 0x0;
	sphere->cor = spherecolor;
	vector<SceneObject*> *l = scene->objts;
	l->push_back((SceneObject*) sphere);
	scene->camera = new Camera(new Vector(3,2,0),new Vector(-1.0,0.5,0.0));
	return scene;
}

double
RayCasting::recenter_x(int x){
	return (x - (this->width / 2.0)) / (2.0 * this->width);
}

double
RayCasting::recenter_y(int y){
	return -(y - (this->height / 2.0)) / (2.0 * this->height);
}

Vector*
RayCasting::getPoint(int x, int y, Camera *camera){
	Vector *v1 = Util::mult_scalar(camera->right,this->recenter_x(x));
	Vector *v2 = Util::mult_scalar(camera->up,this->recenter_y(y));
	Vector *v3 = Util::plus(v1,v2);
	v3 = Util::plus(camera->forward,v3);
	Vector *v4 = Util::normal(v3);
	return v4;
}

color*
RayCasting::traceRay(Ray *r, Scene *scene, int depth){

	SceneObject *obj = minIntersect(r,scene);
	if(obj == NULL){
		return 	scene->background;
	}
	return obj->cor;
}

SceneObject*
RayCasting::minIntersect(Ray *r, Scene *scene){
	SceneObject *obj = NULL;
	vector<SceneObject*> *objects = scene->getObjects();
	for(int i = 0; i < objects->size(); i++){
		SceneObject *sobj = objects->at(i);
		if(sobj->intersect(r)==1)
			obj = sobj;
	}
	return obj;
}

int
RayCasting::render(Scene *scene){
	for(int i = 0; i < this->width; i++){
		for(int j = 0 ; j < this->height; j++){
			Ray *r = new Ray();
			r->origin = scene->camera->pos;
			r->direction = this->getPoint(i,j,scene->camera);
			color *cor = this->traceRay(r,scene,0);
            al_set_target_bitmap(this->bitmap);
            al_put_pixel(i, j,  al_map_rgb(cor->R, cor->G, cor->B));
		}
	}
	bool init_addon = al_init_image_addon();
	bool saved = al_save_bitmap("imagem.bmp",this->bitmap);
	if(!saved){
        al_destroy_bitmap(this->bitmap);
        return -1;
	}
	return 0;
}

int
RayCasting::parallelRender(Scene *scene){

	int *matriz_a = (int*) malloc(TAM*(sizeof(int)));
	int *matriz_b = (int*) malloc(TAM*(sizeof(int)));
	int *result = (int*) malloc(TAM*(sizeof(int)));

	for(int i = 0; i < TAM; i++){
		matriz_a[i] = rand()%100;
		matriz_b[i] = rand()%100;
	}

	cl_uint num_entries = 1;
	cl_uint available;
	cl_uint num_device;
	size_t src_size = 0;


	cl_device_id *device_id = (cl_device_id*) malloc(sizeof(cl_device_id));

	cl_platform_id *platform_id = (cl_platform_id*) malloc(sizeof(cl_platform_id));

	/*
	Retorna um conjunto de plataformas
	*/
	clGetPlatformIDs(num_entries,platform_id, &available);

	/*
	insere em "device_id" uma lista de dispositívos que suportam OpenCL
	O Atributo CL_DEVICE_TYPE_ALL define que podem ser retornadas todas os dispositivos
	*/
	clGetDeviceIDs(platform_id[0],CL_DEVICE_TYPE_ALL,num_entries, device_id,&num_device);

	//é atributo opcional, mas preciso estudar.
	//cl_context_properties *context_properties = (cl_context_properties*) malloc(sizeof(cl_context_properties));

	cl_int *error = NULL;

	//verificar o context_properties
	cl_context context= clCreateContext(NULL,num_device,device_id,NULL,NULL,error);

	const int mem_size = sizeof(int)*TAM;
	cl_mem matriz_a_d = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_size, matriz_a, error);
	cl_mem matriz_b_d = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_size, matriz_b, error);
	cl_mem result_d = clCreateBuffer(context, CL_MEM_WRITE_ONLY, mem_size, NULL, error);

	const char *source = "__kernel void add_vector(__global const int *a, __global const int *b, __global int *result, const int ordem)\n \
{\n \
	int id = get_global_id(0);\n \
	\n \
	if(id < ordem)\n \
		result[id] = b[id] + a[id];\n \
	\n \
}";

	cl_int erro = NULL;

	cl_command_queue queue = clCreateCommandQueue(context, *device_id, 0, error);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source, NULL,&erro);

	if (!program) {
		return -1;
	}

	erro = clBuildProgram(program,1,device_id,NULL,NULL,NULL);
	if(erro != CL_SUCCESS){
		return -1;
	}

	char* build_log;
	size_t log_size;
	clGetProgramBuildInfo(program, *device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	build_log = new char[log_size+1];
	clGetProgramBuildInfo(program, *device_id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
	build_log[log_size] = '\0';
	cout << build_log << endl;
	delete[] build_log;

	cl_kernel vector_add_kernel = clCreateKernel(program, "add_vector", &erro);

	if(erro != CL_SUCCESS){
		return -1;
	}

	const int size = TAM;

	erro = clSetKernelArg(vector_add_kernel, 0, sizeof(cl_mem), &matriz_a_d);
	erro |= clSetKernelArg(vector_add_kernel, 1, sizeof(cl_mem), &matriz_b_d);
	erro |= clSetKernelArg(vector_add_kernel, 2, sizeof(cl_mem), &result_d);
	erro |= clSetKernelArg(vector_add_kernel, 3, sizeof(size_t),&size);

	if(erro != CL_SUCCESS){
		return -1;
	}


	const size_t local_ws = 512;	// Number of work-items per work-group
	// shrRoundUp returns the smallest multiple of local_ws bigger than size
	const size_t global_ws = OpenCLUtil::shrRoundUp(local_ws, size);

	erro = clEnqueueNDRangeKernel(queue, vector_add_kernel, 1, NULL, &global_ws, &local_ws, 0, NULL, NULL);

	if(erro != CL_SUCCESS){
		return -1;
	}

	int* check = (int*) malloc (TAM*sizeof(int));
	clEnqueueReadBuffer(queue, result_d, CL_TRUE, 0, mem_size, check, 0, NULL, NULL);

	for(int i =0 ; i< TAM; i++){
		printf("%d",matriz_a[i]);
		printf("\t + %d",matriz_b[i]);
		printf("\t = %d\n",check[i]);
	}

    return 0;

}


RayCasting::~RayCasting(void)
{
}
