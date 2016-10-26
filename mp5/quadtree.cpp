/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
#include <cmath>
using namespace std;

Quadtree::Quadtree(){root=NULL;}
Quadtree::Quadtree(const PNG& source, int resolution){
	root=NULL;
	buildTree(source,resolution);
}

Quadtree::Quadtree(Quadtree const& other){
	root=copy(other.root);
}

//helper function-- copy
Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* subRoot){
	if(subRoot==NULL)
		return NULL;
	QuadtreeNode* temp=new QuadtreeNode();
	temp->element=subRoot->element;
	temp->nwChild=copy(subRoot->nwChild);
	temp->neChild=copy(subRoot->neChild);
	temp->swChild=copy(subRoot->swChild);
	temp->seChild=copy(subRoot->seChild);
	return temp;
}

Quadtree::~Quadtree(){
	if(root!=NULL)
		clear(root);
}

//helper function-- clear
void Quadtree::clear(QuadtreeNode* subRoot)const{
	if(subRoot==NULL)
		return;
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);
	delete subRoot;
	subRoot=NULL;
}

Quadtree const& Quadtree::operator=(Quadtree const& other){
	if((*this)==other)
		return *this;
	clear(this->root);
	root=copy(other.root);
	return *this;
}

void Quadtree::buildTree(PNG const& source, int resolution){
	clear(root);
	root=buildTree(source,0,0,resolution);
}

//helper functoin
Quadtree::QuadtreeNode* Quadtree::buildTree(PNG const& source,int x,int y,int resolution)const{
	if(resolution==1){
		QuadtreeNode* subRoot=new QuadtreeNode();
		subRoot->element=*source(x,y);
		subRoot->nwChild=NULL;
		subRoot->neChild=NULL;
		subRoot->swChild=NULL;
		subRoot->seChild=NULL;
		subRoot->resol=resolution;
		return subRoot;
	}
	QuadtreeNode* subRoot=new QuadtreeNode();
	subRoot->nwChild=buildTree(source,x,y,resolution/2);
	subRoot->neChild=buildTree(source,x+resolution/2,y,resolution/2);
	subRoot->swChild=buildTree(source,x,y+resolution/2,resolution/2);
	subRoot->seChild=buildTree(source,x+resolution/2,y+resolution/2,resolution/2);

	subRoot->element.red=(subRoot->nwChild->element.red+subRoot->neChild->element.red+subRoot->swChild->element.red+subRoot->seChild->element.red)/4;
	subRoot->element.green=(subRoot->nwChild->element.green+subRoot->neChild->element.green+subRoot->swChild->element.green+subRoot->seChild->element.green)/4;
	subRoot->element.blue=(subRoot->nwChild->element.blue+subRoot->neChild->element.blue+subRoot->swChild->element.blue+subRoot->seChild->element.blue)/4;
	subRoot->resol=resolution;
	return subRoot;
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
	if(x>=root->x_coord||y>=root->y_coord||root==NULL||x<0||y<0)
		return RGBAPixel();
	return getPixel(x,y,0,0,root->resol,root);
}

//helper function
RGBAPixel Quadtree::getPixel(int x,int y,int nx,int ny,int resolution,QuadtreeNode* subRoot)const{
	if(subRoot->nwChild||subRoot->neChild||subRoot->swChild||subRoot->seChild){
		return subRoot->element;
	}
	if(x<nx+resolution/2&&y<ny+resolution/2)
		return getPixel(x,y,nx,ny,resolution/2,subRoot->nwChild);
	else if((x>=nx+resolution/2)&&(y<ny+resolution/2))
		return getPixel(x,y,nx+resolution/2,ny,resolution/2,subRoot->neChild);
	else if((x<nx+resolution/2)&&(y>=ny+resolution/2))
		return getPixel(x,y,nx,ny+resolution/2,resolution/2,subRoot->swChild);
	else
		return getPixel(x,y,nx+resolution/2,ny+resolution/2,resolution/2,subRoot->seChild);
}

PNG Quadtree::decompress() const{
	if(root==NULL)
		return *(new PNG());
	PNG ret(root->resol,root->resol);
        for(int i=0;i<root->resol;i++){
                for(int j=0;j<root->resol;j++){
                       *ret(i,j)=getPixel(i,j);
                }
        }
        return ret;
}


void Quadtree::clockwiseRotate(){


}

void Quadtree::prune(int tolerance){

}

int Quadtree::pruneSize(int tolerance) const{

	return 0;
}

int Quadtree::idealPrune(int numLeaves) const{
	return 0;
}






