/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
#include <cmath>
using namespace std;

Quadtree::Quadtree(){
	root=NULL;
}
Quadtree::Quadtree(const PNG& source, int resolution){
	buildTree(source,resolution);
}

Quadtree::Quadtree(Quadtree const& other){
	root=copy(other.root);
}

//helper function-- copy
Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* subRoot){
	if(subRoot==NULL)
		return NULL;
	QuadtreeNode* temp=new QuadtreeNode;
	temp->element=subRoot->element;
	temp->nwChild=copy(subRoot->nwChild);
	temp->neChild=copy(subRoot->neChild);
	temp->swChild=copy(subRoot->swChild);
	temp->seChild=copy(subRoot->seChild);
	temp->resol=subRoot->resol;
	return temp;
}

Quadtree::~Quadtree(){
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
	if(root==other.root)
		return *this;
	clear(root);
	root=copy(other.root);
	return *this;
}

void Quadtree::buildTree(PNG const& source, int resolution){
	root=buildTree(source,0,0,resolution);
}

//helper functoin
Quadtree::QuadtreeNode* Quadtree::buildTree(PNG const& source,int x,int y,int resolution)const{
	if(resolution==1){
		QuadtreeNode* subRoot=new QuadtreeNode;
		subRoot->element=*source(x,y);
		subRoot->nwChild=NULL;
		subRoot->neChild=NULL;
		subRoot->swChild=NULL;
		subRoot->seChild=NULL;
		subRoot->resol=resolution;
		return subRoot;
	}
	QuadtreeNode* subRoot=new QuadtreeNode;
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
	if(x>=root->resol||y>=root->resol||root==NULL)
		return RGBAPixel();
	return getPixel(x,y,0,0,root->resol,root);
}

//helper function
RGBAPixel Quadtree::getPixel(int x,int y,int a,int b,int resolution,QuadtreeNode* subRoot)const{
	if(subRoot->nwChild==NULL)
		return subRoot->element;
	if((x<a+resolution/2)&&(y<b+resolution/2))
		return getPixel(x,y,a,b,resolution/2,subRoot->nwChild);
	else if((x>=a+resolution/2)&&(y<b+resolution/2))
		return getPixel(x,y,a+resolution/2,b,resolution/2,subRoot->neChild);
	else if((x<a+resolution/2)&&(y>=b+resolution/2))
		return getPixel(x,y,a,b+resolution/2,resolution/2,subRoot->swChild);
	else
		return getPixel(x,y,a+resolution/2,b+resolution/2,resolution/2,subRoot->seChild);
}

PNG Quadtree::decompress() const{
	if(root==NULL)
		return PNG();
	PNG ret(root->resol,root->resol);
        for(int i=0;i<root->resol;i++)
		for(int j=0;j<root->resol;j++)
			*(ret(i,j))=getPixel(i,j);


	return ret;
}


void Quadtree::clockwiseRotate(){
	clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode* subRoot){
	if(subRoot->nwChild==NULL)
		return;
	QuadtreeNode* temp=subRoot->nwChild;
	subRoot->nwChild=subRoot->swChild;
	subRoot->swChild=subRoot->seChild;
	subRoot->seChild=subRoot->neChild;
	subRoot->neChild=temp;
	
	subRoot->nwChild->x_coord=subRoot->x_coord;
	subRoot->nwChild->y_coord=subRoot->y_coord;
	subRoot->neChild->x_coord=subRoot->x_coord+subRoot->resol/2;
	subRoot->neChild->y_coord=subRoot->y_coord;
	subRoot->swChild->x_coord=subRoot->x_coord;
	subRoot->swChild->y_coord=subRoot->y_coord+subRoot->resol/2;
	subRoot->seChild->x_coord=subRoot->x_coord+subRoot->resol/2;
	subRoot->seChild->y_coord=subRoot->y_coord+subRoot->resol/2;
	clockwiseRotate(subRoot->nwChild);
	clockwiseRotate(subRoot->neChild);
	clockwiseRotate(subRoot->swChild);
	clockwiseRotate(subRoot->seChild);
}

void Quadtree::prune(int tolerance){

	prune(tolerance, root);
}

void Quadtree::prune(int tolerance, QuadtreeNode* subRoot){
	if(subRoot->nwChild==NULL)
		return;
	else if(prunable(tolerance,subRoot,subRoot)){
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);
		subRoot->nwChild=NULL;
		subRoot->neChild=NULL;
		subRoot->swChild=NULL;
	 	subRoot->seChild=NULL;

		return;
	}else{
		prune(tolerance,subRoot->nwChild);
		prune(tolerance,subRoot->neChild);
		prune(tolerance,subRoot->swChild);
		prune(tolerance,subRoot->seChild);
	}
}

int Quadtree::diff(QuadtreeNode* subRoot,QuadtreeNode* leaf)const{
	int diff=pow(subRoot->element.red-leaf->element.red,2)+pow(subRoot->element.green-leaf->element.green,2)+pow(subRoot->element.blue-leaf->element.blue,2);
	return diff;
	
}

bool Quadtree::prunable(int tolerance, QuadtreeNode* subRoot,QuadtreeNode* leaf)const{
	if(subRoot==NULL)
		return true;
	if(leaf->nwChild==NULL)
		return diff(subRoot,leaf)<=tolerance;
	return prunable(tolerance,subRoot,leaf->nwChild)&&prunable(tolerance,subRoot,leaf->neChild)&&prunable(tolerance,subRoot,leaf->seChild)&&prunable(tolerance,subRoot,leaf->swChild);

}

int Quadtree::pruneSize(int tolerance) const{
	return pruneSize(tolerance,root);
}

int Quadtree::pruneSize(int tolerance,QuadtreeNode* subRoot)const{
	if(subRoot==NULL)
		return 0;
	if(subRoot->nwChild==NULL||prunable(tolerance,subRoot,subRoot))
		return 1;
	return pruneSize(tolerance,subRoot->nwChild)+pruneSize(tolerance,subRoot->neChild)+pruneSize(tolerance,subRoot->seChild)+pruneSize(tolerance,subRoot->swChild);

}

int Quadtree::idealPrune(int numLeaves) const{
	int max=pow(255,2)+pow(255,2)+pow(255,2);
	int min=0;
	int toler=(min+max)/2;
	int ret=0;
	while(toler>min&&toler<max){
		if(pruneSize(toler)<=numLeaves){
			max=toler;
			ret=toler;
			toler=(min+max)/2;
		}else{
			min=toler;
			toler=(min+max)/2;
		}
	}
	if(ret==1)
		return 0;
	return ret;
}






