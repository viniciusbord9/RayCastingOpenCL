#include "../include/RayCasting.h"
#define TAM 100

//void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info, size_t cb, void *user_data);
int testeOpenCL();

RayCasting::RayCasting(const int width, const int height)
{
    this->sampleCommon = new streamsdk::SDKCommon();
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
	/*esfera 1*/
	Vector *origin = new Vector(0,1,0);
	Sphere *sphere = new Sphere(origin, 0.2);
	color *spherecolor = (color*) malloc(sizeof(color));
	spherecolor->R = 0x0;
	spherecolor->G = 0xff;
	spherecolor->B = 0x0;
	sphere->cor = spherecolor;

	/*esfera 2*/
    Vector *origin1 = new Vector(1,1,0);
	Sphere *sphere1 = new Sphere(origin1, 0.2);
	color *spherecolor1 = (color*) malloc(sizeof(color));
	spherecolor1->R = 0xff;
	spherecolor1->G = 0x0;
	spherecolor1->B = 0x0;
	sphere1->cor = spherecolor1;

	/*esfera 3*/
	Vector *origin2 = new Vector(0.5,1,-0.2);
	Sphere *sphere2 = new Sphere(origin2, 0.2);
	color *spherecolor2 = (color*) malloc(sizeof(color));
	spherecolor2->R = 0x0;
	spherecolor2->G = 0x0;
	spherecolor2->B = 0xff;
	sphere2->cor = spherecolor2;

	/*esfera 4*/
	Vector *origin3 = new Vector(0.5,1,0.5);
	Sphere *sphere3 = new Sphere(origin3, 0.2);
	color *spherecolor3 = (color*) malloc(sizeof(color));
	spherecolor3->R = 0xff;
	spherecolor3->G = 0xaf;
	spherecolor3->B = 0xaf;
	sphere3->cor = spherecolor3;

	/*esfera 5*/
	Vector *origin4 = new Vector(0.5,1,0.2);
	Sphere *sphere4 = new Sphere(origin4, 0.2);
	color *spherecolor4 = (color*) malloc(sizeof(color));
	spherecolor4->R = 0x0;
	spherecolor4->G = 0x0;
	spherecolor4->B = 0xff;
	sphere4->cor = spherecolor4;

	/*esfera 6*/
	Vector *origin5 = new Vector(0.5,1,0.5);
	Sphere *sphere5 = new Sphere(origin5, 0.2);
	color *spherecolor5 = (color*) malloc(sizeof(color));
	spherecolor5->R = 0xff;
	spherecolor5->G = 0xaf;
	spherecolor5->B = 0xaf;
	sphere5->cor = spherecolor5;

	/*esfera 7*/
	Vector *origin6 = new Vector(0,1,1);
	Sphere *sphere6 = new Sphere(origin6, 0.2);
	color *spherecolor6 = (color*) malloc(sizeof(color));
	spherecolor6->R = 0x0;
	spherecolor6->G = 0xff;
	spherecolor6->B = 0x0;
	sphere6->cor = spherecolor6;

	/*esfera 8*/
    Vector *origin7 = new Vector(1,1,-0.7);
	Sphere *sphere7 = new Sphere(origin7, 0.2);
	color *spherecolor7 = (color*) malloc(sizeof(color));
	spherecolor7->R = 0xff;
	spherecolor7->G = 0x0;
	spherecolor7->B = 0x0;
	sphere7->cor = spherecolor7;

	/*esfera 9*/
	Vector *origin8 = new Vector(0.5,0.5,-0.2);
	Sphere *sphere8 = new Sphere(origin8, 0.2);
	color *spherecolor8 = (color*) malloc(sizeof(color));
	spherecolor8->R = 0x0;
	spherecolor8->G = 0x0;
	spherecolor8->B = 0xff;
	sphere8->cor = spherecolor8;

	/*esfera 10*/
	Vector *origin9 = new Vector(0.5,0.5,-0.5);
	Sphere *sphere9 = new Sphere(origin9, 0.2);
	color *spherecolor9 = (color*) malloc(sizeof(color));
	spherecolor9->R = 0xff;
	spherecolor9->G = 0xaf;
	spherecolor9->B = 0x00;
	sphere9->cor = spherecolor9;

	/*esfera 11*/
	Vector *origin10 = new Vector(0,1,0.2);
	Sphere *sphere10 = new Sphere(origin10, 0.2);
	color *spherecolor10 = (color*) malloc(sizeof(color));
	spherecolor10->R = 0x0;
	spherecolor10->G = 0xaf;
	spherecolor10->B = 0xbf;
	sphere10->cor = spherecolor10;

	/*esfera 12*/
	Vector *origin11 = new Vector(1.2,1,0.5);
	Sphere *sphere11 = new Sphere(origin11, 0.2);
	color *spherecolor11 = (color*) malloc(sizeof(color));
	spherecolor11->R = 0xff;
	spherecolor11->G = 0xaf;
	spherecolor11->B = 0xaf;
	sphere11->cor = spherecolor11;

	vector<SceneObject*> *l = scene->objts;
	l->push_back((SceneObject*) sphere);
	l->push_back((SceneObject*) sphere1);
	l->push_back((SceneObject*) sphere2);
	l->push_back((SceneObject*) sphere3);
//    l->push_back((SceneObject*) sphere4);
//	l->push_back((SceneObject*) sphere5);
//    l->push_back((SceneObject*) sphere6);
//	l->push_back((SceneObject*) sphere7);
//	l->push_back((SceneObject*) sphere8);
//    l->push_back((SceneObject*) sphere9);
//	l->push_back((SceneObject*) sphere10);
//    l->push_back((SceneObject*) sphere11);

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
    int timer = this->sampleCommon->createTimer();
    this->sampleCommon->resetTimer(timer);
    this->sampleCommon->startTimer(timer);
	for(int i = 0; i < this->width; i++){
		for(int j = 0 ; j < this->height; j++){
			Ray *r = new Ray();
			r->origin = scene->camera->pos;
			r->direction = this->getPoint(i,j,scene->camera);
			color *cor = this->traceRay(r,scene,0);
            //al_set_target_bitmap(this->bitmap);
            //al_put_pixel(i, j,  al_map_rgb(cor->R, cor->G, cor->B));
		}
	}
    this->sampleCommon->stopTimer(timer);
    double time = (double)(this->sampleCommon->readTimer(timer));
    cout << "\n" << time;
	//bool saved = al_save_bitmap("imagemSequencial.bmp",this->bitmap);
	/*if(!saved){
        al_destroy_bitmap(this->bitmap);
        return -1;
	}*/
	return 0;
}

int
RayCasting::parallelRender(scene *s, camera *cam, obj *list_objects, int qtde_objects){

    cl_uint pixelSize = sizeof(streamsdk::uchar4);

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
        //cout << "plataformas " << (*iter).getInfo<CL_PLATFORM_VENDOR>().c_str();
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

    /****************************************************************************************/
    /*********                  Verificando suporte a imagem                            *****/
    /****************************************************************************************/
    // Check for image support
    cl_int imageSupport = devices[0].getInfo<CL_DEVICE_IMAGE_SUPPORT>(&err);
    CHECK_OPENCL_ERROR(err, "Device::getInfo() failed.");

    // If images are not supported then return
    if(!imageSupport)
    {
        OPENCL_EXPECTED_ERROR("Images are not supported on this device!");
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

    cl::Image2D outputImage2D = cl::Image2D(context,CL_MEM_WRITE_ONLY,cl::ImageFormat(CL_RGBA,CL_UNSIGNED_INT8),this->width,this->height,0, NULL, &err);
    CHECK_OPENCL_ERROR(err, "cl::Image2D(...) failed.");

    cl_int w = this->width;
    cl_int h = this->height;

    cl::Buffer a = cl::Buffer(context,CL_MEM_READ_ONLY, sizeof(scene));
    cl::Buffer b = cl::Buffer(context,CL_MEM_READ_ONLY, sizeof(camera));
    cl::Buffer c = cl::Buffer(context,CL_MEM_READ_ONLY, qtde_objects * sizeof(obj));

    err = queue.enqueueWriteBuffer(a,CL_TRUE,0 , sizeof(scene),s);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(scene) failed.");

    err = queue.enqueueWriteBuffer(b,CL_TRUE,0 , sizeof(camera),cam);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(camera) failed.");

    err = queue.enqueueWriteBuffer(c,CL_TRUE,0 , qtde_objects * sizeof(obj),list_objects);
    CHECK_OPENCL_ERROR(err, "enqueueWriteBuffer(obj) failed.");


    cl::size_t<3> origin;
    origin[0] = 0;
    origin[1] = 0;
    origin[2] = 0;

    cl::size_t<3> region;
    region[0] = this->width;
    region[1] = this->height;
    region[2] = 1;

    cl::Event writeEvt;

    cl_int status;

    status = kernel.setArg(0,a);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(0) failed.");

    status = kernel.setArg(1,b);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(1) failed.");

    status = kernel.setArg(2,c);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(2) failed.");

    status = kernel.setArg(3,w);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(3) failed.");

    status = kernel.setArg(4,h);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(4) failed.");


    status = kernel.setArg(5, outputImage2D);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg(5) failed.");


    size_t kernelWorkGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);

    //cout << "\n workgroups " << kernelWorkGroupSize << "\n\n";

    cl::NDRange global(this->width,this->height);
//    int local_w = this->width/kernelWorkGroupSize;
//    int local_h = this->heith/kernelWorkGroupSize;
    cl::NDRange local(32,24);

    //streamsdk::SDKCommon *sampleCommon = new streamsdk::SDKCommon();


    int timer = this->sampleCommon->createTimer();
    int i;
    cl::Event readEvt;
    for(i = 0; i < 50; i++){
        this->sampleCommon->resetTimer(timer);
        this->sampleCommon->startTimer(timer);

        cl::Event ndrEvt;
        status = queue.enqueueNDRangeKernel(kernel,cl::NullRange,global,local,0,&ndrEvt);
        CHECK_OPENCL_ERROR(status, "\n CommandQueue::senqueueNDRangeKernel(...) failed.");

        origin[0] = 0;
        origin[1] = 0;
        origin[2] = 0;

        region[0] = this->width;
        region[1] = this->height;
        region[2] = 1;

        status = queue.enqueueReadImage(outputImage2D, CL_TRUE, origin, region, 0, 0, outputImageData, NULL, &readEvt);
        CHECK_OPENCL_ERROR(status, "\n CommandQueue::senqueueNDRangeKernel(...) failed.");

        status = queue.flush();
        CHECK_OPENCL_ERROR(status, "\n CommandQueue::flush() failed.");

        status = queue.finish();
        CHECK_OPENCL_ERROR(status, "\n CommandQueue::flush() failed.");

        this->sampleCommon->stopTimer(timer);
        cout << "\n" << (double)(this->sampleCommon->readTimer(timer));
    }

    cl_int eventStatus = CL_QUEUED;
    while(eventStatus != CL_COMPLETE)
    {
        status = readEvt.getInfo<cl_int>(
                    CL_EVENT_COMMAND_EXECUTION_STATUS,
                    &eventStatus);
        CHECK_OPENCL_ERROR(status, "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
    }
    //}

    /*streamsdk::SDKBitMap bitmap;

    bitmap.load(OUTPUT_IMAGE);
    if(!bitmap.isLoaded()){
        cout << "\nerro ao carregar imagem";
    }

    streamsdk::uchar4* pixelData = bitmap.getPixels();

    memcpy(pixelData, outputImageData, w * h * pixelSize);

    if(!bitmap.write(OUTPUT_IMAGE)){
        cout << "\nerro ao escrever imagem";
    }*/

   free(outputImageData);

	return 0;
}


void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info, size_t cb, void *user_data)
{
    printf("Error while creating context or working in this context : %s", errinfo);
}


RayCasting::~RayCasting(void)
{
}
