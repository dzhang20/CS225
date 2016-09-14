#include "scene.h"

#include "image.h"

#include <iostream>

using namespace std;


Scene::Scene(int Max){

        max=Max;

        image = new Image*[max];

        x_cood = new int[max];

        y_cood = new int[max];

        for(int i=0;i<max;i++)

                image[i]=NULL;


}


Scene::~Scene(){

        clear();

}


Scene:: Scene(const Scene& source){

        copy(source);

}


const Scene & Scene::operator= (const Scene & source){

        if(this != &source){

                clear();

                copy(source);

        }

        return *this;

}


void Scene::changemaxlayers(int newmax){

        if(max>newmax){

                for(int i=0;i< max;i++)

                        if(image[i]!=NULL)

                                cout << "invalid newmax" << endl;

        }

        int newx_cood= new int[newmax];

        int newy_cood= new int[newmax];

        Image newimage= new Image*[newmax];

        for(int i=0;i<newmax;i++){

                newimage[i]=image[i];

                newx_cood[i]= x_cood[i];

                newy_cood[i]= y_cood[i];

        }

        clear();

        x_cood=newx_cood;

		y_cood=newy_cood;

        image=newimage;

}


void Scene::addpicture(const char* FileName, int index, int x, int y){

        if(index>0&&index<max){

                Image* newimage=new Image();

                newimage->readFromFile(FileName);

                if(image[index]!=NULL)

                        delete image[index];

                image[index]=newimage;

                x_cood=x;

                y_cood=y;

        }else

                cout << "invalid index" << endl;

}


void Scene::changelayer(int index, int newindex){

        if(index>0&&index<max&&newindex>0&&newindex<max){

                if(index==newindex)

                        return;

                if(image[newindex]!=NULL)

                        delete image[newindex];

                image[newidex]=image[index];

                x_cood[newindex]=x_cood[index];

                y_cood[newindex]=y_cood[index];

                x_cood[index]=0;

                y_cood[index]=0;

                image[index]=NULL;

        }else

                cout << "invalid index" << endl;

}


void Scene::translate(int index, int xcood, int ycood){

        if(index>0&&index<max&&image[index]!=NULL){

                x_cood[index]=xcood;

                y_cood[index]=ycood;

        }else

                cout << "invalid index" << endl;

}


void Scene::deletepicture(int index){

        if(index>0&&index<max&&image[index]!=NULL){

                delete image[index];

                x_cood[index]=0;

                y_cood[index]=0;

				image[index]=NULL;

        }else

        cout << "invalid index" << endl;

}


Image* Scene::getpicture(int index)const{

        if(index>0&&index<max){

                return image[index];

        }else{

                cout << "invalid index" << endl;

                return NULL;

        }

}


Image Scene::drawscene() const{

        return image;

}

void Scene::clear(){

        delete[] x_cood;

        delete[] y_cood;


        for(int i=0;i<max;i++){

                if(image[i]!=NULL)

                        delete image[i];

        }

        delete[] image;

}


void Scene::copy(const Scene & source){

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
