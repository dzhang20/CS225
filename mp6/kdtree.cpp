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
	quicksort(points,0,newPoints.size()-1,0);
}

template <int Dim>
void KDTree<Dim>::quicksort(vector<Point<Dim>>& point, int left,int right,int Dimension){
	if(left>right)
		return;
	points[(left+right)/2]=findmedian(point,left,right,(left+right)/2,Dimension);
	quicksort(point,left,(left+right)/2-1,(Dimension+1)%Dim);
	quicksort(point,(left+right)/2+1,right,(Dimension+1)%Dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findmedian(vector<Point<Dim>>& point,int left,int right,int mid,int Dimension){
	while(left<right){
		int pivo=partition(point,left,right,(right+left)/2,Dimension);
		if(pivo==mid)
			return point[pivo];
		else if(mid>pivo)
			left=pivo+1;
		else
			right=pivo-1;
	
	}
	return point[left];
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& point,int left, int right,int mid, int Dimension){
	Point<Dim> Val=point[mid];
	int index=left;
	for(int i=left;i<right;i++){
		if(smallerDimVal(point[i],Val,Dimension)){
			Point<Dim> temp=point[index];
			point[index]=point[i];
			point[i]=temp;
			index++;
		}
	}
	Point<Dim> temp2=point[index];
	point[index]=point[right];
	point[right]=temp2;
	return index;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNeighbor(query,points,0,points.size()-1,0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNeighbor(const Point<Dim>& query,const vector<Point<Dim>>& point, int left, int right, int Dimension)const{
	if(left>=right)
		return point[left];
	Point<Dim> temp=point[(left+right)/2];
	Point<Dim> curBest;
	if(smallerDimVal(query,temp,Dimension))
		 curBest=findNeighbor(query,point,left,(left+right)/2-1,(Dimension+1)%Dim);
	else
		curBest=findNeighbor(query,point,(left+right)/2+1,right,(Dimension+1)%Dim);
	if(shouldReplace(query,curBest,temp)){
		curBest=temp;
		Point<Dim> temp2;
		if(smallerDimVal(query,temp,Dimension))
			temp2=findNeighbor(query,point,(left+right)/2+1,right,(Dimension+1)%Dim);
		else
			temp2=findNeighbor(query,point,left,(left+right)/2-1,(Dimension+1)%Dim);
		if(shouldReplace(query,curBest,temp2))
			curBest=temp2;
	}
	
	return curBest;
}





