#include "../include/RayCasting.h"
#define TAM 100

//void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info, size_t cb, void *user_data);
int testeOpenCL();

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
	spherecolor->R = 0x0;
	spherecolor->G = 0x0;
	spherecolor->B = 0xff;
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
	for(unsigned int i = 0; i < objects->size(); i++){
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
	//bool init_addon = al_init_image_addon();
	bool saved = al_save_bitmap("imagem.bmp",this->bitmap);
	if(!saved){
        al_destroy_bitmap(this->bitmap);
        return -1;
	}
	return 0;
}

int
RayCasting::parallelRender(Scene *scene){

    cl_uint pixelSize = sizeof(streamsdk::uchar4);

    streamsdk::SDKBitMap inputBitmap;

    streamsdk::uchar4* pixelData = inputBitmap.getPixels();

    /***************************************************************************************/
    /*****               Declarando as variáveis para criar o kernel                   *****/
    /***************************************************************************************/
    std::vector<cl::Platform>   platforms;  /** -> lista para as plataformas    **/
    cl::Context                 context;    /** -> contexto                     **/
    std::vector<cl::Device>     devices;    /** -> devices                      **/
    cl::CommandQueue            queue;      /** -> queue                        **/
    cl::Program                 program;    /** -> program                      **/
    cl::Kernel                  kernel;     /** -> kernel                       **/
    cl_int                      err;

    /***************************************************************************************/
    /*****                    Getting available platforms                              *****/
    /***************************************************************************************/
    cl::Platform::get(&platforms);

    std::vector<cl::Platform>::iterator iter;

    for(iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        cout << "plataformas " << (*iter).getInfo<CL_PLATFORM_VENDOR>().c_str();
    }

    /***************************************************************************************/
    /*****                    Criando Contexto                                         *****/
    /***************************************************************************************/
    iter = platforms.begin();

    (*iter).getDevices(CL_DEVICE_TYPE_CPU,&devices);

    context = cl::Context(devices,NULL, NULL, NULL,&err);

    if(err != CL_SUCCESS)
    {
        cout << "erro ao criar o contexto";
    }

    /***************************************************************************************/
    /*****                    Emplilhando os comandos                                  *****/
    /***************************************************************************************/
    queue = cl::CommandQueue(context, devices[0]);

    /***************************************************************************************/
    /*****                    Obtendo Texto do Kernel                                  *****/
    /***************************************************************************************/
    std::ifstream file("src/render.cl");

    streamsdk::SDKFile kernelFile;
    std::string kernelPath = "src/render.cl";

    if(!kernelFile.open(kernelPath.c_str()))
    {
        std::cout << "Failed to load kernel file : " << kernelPath << std::endl;
        return SDK_FAILURE;
    }

    // create program source
    cl::Program::Sources source(1, std::make_pair(kernelFile.source().data(), kernelFile.source().size()));

    // Create program object
    program = cl::Program(context, source, &err);
    CHECK_OPENCL_ERROR(err, "Program::Program() failed.");

    /**
    while (file.good()){
        cout << (char) file.get();
    }
    file.close();

    std::string prog(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

    cl::Program::Sources source(1, std::make_pair(prog.c_str(),prog.length()+1));

    program = cl::Program(context, source, &err);
    CHECK_OPENCL_ERROR(err, "Program::Program() failed.");*/

    err = program.build(devices,"-w");
    //CHECK_OPENCL_ERROR(err, "Program::build() failed.");

    if (err != CL_SUCCESS) {
        std::cout << "\n ERRO: ao criar o kernel" ;
        if(err == CL_BUILD_PROGRAM_FAILURE)
        {
            std::string str = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]);

            std::cout << " \n\t\t\tBUILD LOG\n";
            std::cout << " ************************************************\n";
            std::cout << str << std::endl;
            std::cout << " ************************************************\n";
        }
    }

    kernel = cl::Kernel(program, "render", &err);
    CHECK_OPENCL_ERROR(err, "Kernel::Kernel() failed.");

    /**Criando imagem para passar como parâmetro*/
    cl_uchar4 *outputImageData = (cl_uchar4*)malloc(this->width * this->height * sizeof(cl_uchar4));

    CHECK_ALLOCATION(outputImageData, "Failed to allocate memory! (outputImageData)");

    // initializa the Image data to NULL
    memset(outputImageData, 0, width * height * pixelSize);

    cl::Image2D outputImage2D = cl::Image2D(context,CL_MEM_WRITE_ONLY,cl::ImageFormat(CL_RGBA,CL_UNSIGNED_INT8),this->width,this->height,0, NULL, &err);
    CHECK_OPENCL_ERROR(err, "cl::Image2D(...) failed.");

    scene_struct *s = scene->cast_struct();
    int w = this->width;
    int h = this->height;

    cl::Buffer a = cl::Buffer(context,CL_MEM_READ_ONLY, sizeof(scene_struct));
    cl::Buffer b = cl::Buffer(context,CL_MEM_READ_ONLY, sizeof(int));
    cl::Buffer c = cl::Buffer(context,CL_MEM_READ_ONLY, sizeof(int));
    //cl::Buffer d = cl::Buffer(context,CL_MEM_WRITE_ONLY,sizeof(this->width * this->height * sizeof(cl_uchar4)));

    err = queue.enqueueWriteBuffer(a,CL_TRUE,0 , sizeof(scene_struct),s);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(struct) failed.");

    err = queue.enqueueWriteBuffer(b,CL_TRUE,0 , sizeof(int),&b);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(width) failed.");

    err = queue.enqueueWriteBuffer(c,CL_TRUE,0 , sizeof(int),&c);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(height) failed.");

    cl::size_t<3> origin;
    origin[0] = 0;
    origin[1] = 0;
    origin[2] = 0;

    cl::size_t<3> region;
    region[0] = width;
    region[1] = height;
    region[2] = 1;

    cl::Event writeEvt;

    err = queue.enqueueWriteImage(outputImage2D, CL_TRUE, origin, region, 0, 0, outputImageData, NULL, &writeEvt);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(image) failed.");

    cl_int status;

    status = kernel.setArg(0,a);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(0) failed.");

    status = kernel.setArg(1,b);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(1) failed.");

    status = kernel.setArg(2,c);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(2) failed.");

    status = kernel.setArg(3, outputImage2D);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(3) failed.");


    size_t kernelWorkGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);

    cout << "\n workgroups " << kernelWorkGroupSize << "\n\n";

    cl::NDRange global(512);
    cl::NDRange local(1);

    cl::Event ndrEvt;
    status = queue.enqueueNDRangeKernel(kernel,NULL,global,local,0,&ndrEvt);
    CHECK_OPENCL_ERROR(status, "\n CommandQueue::senqueueNDRangeKernel(...) failed.");

    origin[0] = 0;
    origin[1] = 0;
    origin[2] = 0;

    region[0] = width;
    region[1] = height;
    region[2] = 1;

    cl::Event readEvt;

    status = queue.enqueueReadImage(outputImage2D, CL_TRUE, origin, region, 0, 0, outputImageData, NULL, &readEvt);
    CHECK_OPENCL_ERROR(status, "\n CommandQueue::senqueueNDRangeKernel(...) failed.");

    status = queue.flush();
    CHECK_OPENCL_ERROR(status, "\n CommandQueue::flush() failed.");

    cl_int eventStatus = CL_QUEUED;
    while(eventStatus != CL_COMPLETE)
    {
        status = readEvt.getInfo<cl_int>(
                    CL_EVENT_COMMAND_EXECUTION_STATUS,
                    &eventStatus);
        CHECK_OPENCL_ERROR(status, "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
    }

    cout << "\n\n imagem: " << sizeof(outputImageData) << "\n\n";

    //memcpy(pixelData, outputImageData, this->width * this->height * sizeof(cl_uchar4));

    // write the output bmp file
    /*if(!inputBitmap.write(OUTPUT_IMAGE))
    {
        std::cout << "Failed to write output image!" << std::endl;
        return SDK_FAILURE;
    }*/


    //queue.finish();

	return 0;
}


void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info, size_t cb, void *user_data)
{
    printf("Error while creating context or working in this context : %s", errinfo);
}


RayCasting::~RayCasting(void)
{
}
