#include <iostream>
#include "../include/RayCasting.h"
#include "../include/Scene.h"

using namespace std;

int main(){
	RayCasting raycasting(800,600);
	Scene *scene = raycasting.sceneDefault;
	if(raycasting.parallelRender(scene) == 0){
        cout << "Renderizado";
	}else{
        cout << "ERRO ao renderizar";
	}
	/*if(raycasting.render(scene)==0){
        cout << "Imagem criada";
	}
	else{
        cout << "ERRO ao renderizar";
	}*/
    return 0;
}
