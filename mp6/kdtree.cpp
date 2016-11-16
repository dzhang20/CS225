/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	
	if(first[curDim]==second[curDim])//if there is a tie
		return first<second;    
	return first[curDim]<second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	int distanceCurr=0;
	int distanceP=0;
	for(int i=0;i<Dim;i++){
		distanceCurr+=pow(currentBest[i]-target[i],2);
		distanceP+=pow(potential[i]-target[i],2);
	}
	if(distanceCurr==distanceP)//if there is a tie
		return potential<currentBest;
	return distanceP<distanceCurr;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	points=newPoints;		
	quicksort(0,points.size()-1,0);
}

template <int Dim>
void KDTree<Dim>::quicksort(int left,int right,int Dimension){
	if(left>right)
		return;	
	sort(left,right,(left+right)/2,Dimension);
	quicksort(left,(left+right)/2-1,(Dimension+1)%Dim);
	quicksort((left+right)/2+1,right,(Dimension+1)%Dim);
	
}

template <int Dim>
void KDTree<Dim>::sort(int left,int right,int mid,int Dimension){
	while(left<right){
		int pivot=partition(left,right,Dimension);
		if(pivot==mid)
			return ;
		else if(pivot>mid)
			right=pivot-1;
		else
			left=pivot+1;
	}

}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int Dimension){
	Point<Dim> pivot=points[right];
	int index=left;
	for(int i=left;i<right;i++){
		if(smallerDimVal(points[i],pivot,Dimension)||points[i]==pivot){
			Point<Dim> temp=points[index];
			points[index]=points[i];
			points[i]=temp;
			index++;
		}
	}
	Point<Dim> temp2=points[right];
	points[right]=points[index];
	points[index]=temp2;
	return index;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNeighbor(query,points[(points.size()-1)/2],0,points.size()-1,0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNeighbor(const Point<Dim>& query,const Point<Dim>& curBest, int left, int right, int Dimension)const{
	Point<Dim> temp=curBest;
	if(left==right){
		if(shouldReplace(query,curBest,points[left]))
			temp=points[left];
		return temp;
	}
	bool toLeft=true;
	if(smallerDimVal(query,points[(left+right)/2],Dimension)&&left<(right+left)/2){
		temp=findNeighbor(query,curBest,left,(right+left)/2-1,(Dimension+1)%Dim);
		toLeft=true;
	}
	if(smallerDimVal(points[(left+right)/2],query,Dimension)&&right>(left+right)/2){
		temp=findNeighbor(query,curBest,(left+right)/2+1,right,(Dimension+1)%Dim);
		toLeft=false;
	}
	if(shouldReplace(query,temp,points[(left+right)/2]))
		temp=points[(left+right)/2];
	int radi =0;
	for(int i=0;i<Dim;i++)
		radi+=pow(temp[i]-query[i],2);
	if(pow(points[(left+right)/2][Dimension]-query[Dimension],2)<=radi){
		if(toLeft==true&&right>(right+left)/2){
			temp=findNeighbor(query,temp,(left+right)/2+1,right,(Dimension+1)%Dim);	
		}
		if(toLeft==false&&left<(left+right)/2){
			temp=findNeighbor(query,temp,left,(left+right)/2-1,(Dimension+1)%Dim);
		}
	}
	return temp;
}
