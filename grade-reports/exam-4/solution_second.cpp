#include "common.h"
#include "quadtree.h"

#include <iostream>
#include <algorithm>
#include <cmath>
/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int Quadtree::tallyDeviants(RGBAPixel const & target, 
    QuadtreeNode const * curNode, int tolerance) const {
    //YOUR CODE HERE
    if(curNode==NULL)
    	return 0;
    if(curNode->nwChild==NULL&&(tolerance<(pow(target.red-curNode->element.red,2)+pow(target.green-curNode->element.green,2)+pow(target.blue-curNode->element.blue,2))))
	return 1;
    else if(curNode->nwChild!=NULL){
	return tallyDeviants(target,curNode->nwChild,tolerance)+tallyDeviants(target,curNode->neChild,tolerance)+tallyDeviants(target,curNode->swChild,tolerance)+tallyDeviants(target,curNode->seChild,tolerance);
    }else 
	return 0;
}

void Quadtree::prunish(int tolerance, double percent) {
    //YOUR CODE HERE
	prunish(root,tolerance,resolution,percent);
} 

void Quadtree::prunish(QuadtreeNode * curNode, int tolerance, int res, double percent) {
    //YOUR CODE HERE
	if(curNode==NULL)
		return;
	else if(curNode->nwChild==NULL)
		return;
	else if(prunable(curNode,curNode,tolerance)/(total(curNode)<=percent)){
		clear(curNode->nwChild);
		clear(curNode->neChild);
		clear(curNode->swChild);
		clear(curNode->seChild);
		curNode->nwChild=NULL;
		curNode->neChild=NULL;
		curNode->swChild=NULL;
		curNode->seChild=NULL;
	}else{
		prunish(curNode->nwChild,tolerance,res/2,percent);
		prunish(curNode->neChild,tolerance,res/2,percent);
		prunish(curNode->swChild,tolerance,res/2,percent);
		prunish(curNode->seChild,tolerance,res/2,percent);
	}
}

int Quadtree::prunable(QuadtreeNode* curNode, QuadtreeNode* leaf, int tolerance){
	if(leaf->nwChild==NULL&& tolerance>=(pow(curNode->element.red-leaf->element.red,2)+pow(curNode->element.green-leaf->element.green,2)+pow(curNode->element.blue-leaf->element.blue,2)))
		return 1;
	else if(leaf->nwChild==NULL)
		return 0;
	else
		return prunable(curNode,leaf->nwChild,tolerance)+prunable(curNode,leaf->neChild,tolerance)+prunable(curNode,leaf->swChild,tolerance)+prunable(curNode,leaf->seChild,tolerance);
}

int Quadtree::total(QuadtreeNode* curNode){
	if(curNode==NULL)
		return 0;
	if(curNode->nwChild==NULL)
		return 1;
	else
		return total(curNode->nwChild)+total(curNode->neChild)+total(curNode->swChild)+total(curNode->seChild);
}	
