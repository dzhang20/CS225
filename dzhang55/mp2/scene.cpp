#include "scene.h"
#include "image.h"

Scene::Scene(int Max){
	max=Max;
	image = new Image*[max];
	x_cood = new int[max];
	y_cood = new int[max];
	for(int i=0;i<max;i++)
		image[i]=NULL;

}

Scene::~Scene(){
	for(int i=0;i<max;i++){
		delete image[i];
		image[i]=NULL;
	}
	delete [] x_cood;
	delete [] y_cood;
	delete [] image;
	x_cood =NULL;
	y_cood =NULL;
	image =NULL;
}

Scene:: Scene(const Scene& source){
	max = source.max;
	x_cood = new int[max];
	y_cood = new int[max];
	for(int i=0; i<max;i++){
		x_cood[i]= source.x_cood[i];
		y_cood[i]= source.y_cood[i];
		if(source.image[i]==NULL)
			image[i]=NULL;
		else
			image[i]= new Image(*(source.image[i]));


	}
}

const Scene & Scene::operator= (const Scene & source){
	
}

void Scene::changemaxlayers(int newmax){

}

void Scene::addpicture(const char* FileName, int index, int x, int y){

}

void Scene:;changelayer(int index, int newindex){

}

void Scene::translate(int index, int xcood, int ycood){

}

void Scene::deletepicture(int index){

}

Image* Scene::getpicture(int index)const{

}

Image Scene::drawscene() const{

}
