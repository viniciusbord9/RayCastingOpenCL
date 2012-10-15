#include <iostream>
#include "../include/RayCasting.h"
#include "../include/Scene.h"

using namespace std;

int main(){
	RayCasting raycasting(800,600);
	Scene *scene = raycasting.sceneDefault;


	if(raycasting.parallelRender(scene->cast_struct(),scene->camera->cast_struct(), scene->cast_objects(), scene->getObjects()->size()) == 0){
        cout << "\nRenderizado";
	}else{
        cout << "\nERRO ao renderizar";
	}
	if(raycasting.render(scene)==0){
        cout << "\nRenderizado";
	}
	else{
        cout << "\nERRO ao renderizar";
	}
    return 0;
}
