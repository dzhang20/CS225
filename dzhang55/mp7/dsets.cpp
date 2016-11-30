/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num){
	elems.resize(elems.size()+num);
	for(size_t i=elems.size()-num;i<elems.size();i++)
		elems[i]=-1;

}

int DisjointSets::find(int elem){
	if(elems[elem]<0)
		return elem;
	else{
		elems[elem]=find(elems[elem]);
		return find(elems[elem]);
	}

}

void DisjointSets::setunion(int a, int b){
	a=find(a);
	b=find(b);
	int newSize=elems[a]+elems[b];
	if(elems[a]<=elems[b]){
		elems[b]=a;
		elems[a]=newSize;
	}else{
		elems[a]=b;
		elems[b]=newSize;
	}
}
