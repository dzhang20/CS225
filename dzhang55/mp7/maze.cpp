#include "maze.h"

SquareMaze::SquareMaze(){
	
	d=DisjointSets();
}

void SquareMaze::makeMaze(int width,int height){
	d.addelements(width*height);
	w=width;
	h=height;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
		 	Cell t=Cell();
			t.x=i;
			t.y=j;
			t.visited=false;
			t.right=true;
			t.down=true;
			cells.push_back(t);
		}
	}
	srand(time(NULL));
	vector<int> walls;
	for(int i=0;i<2*height*width;i++)
		walls.push_back(i);
	random_shuffle(walls.begin(),walls.end());
	for(auto it=walls.begin();it!=walls.end();it++){
		if(*it<(int)cells.size()){
			if((*it+1)%width!=0)
				if(d.find(*it)!=d.find(*it+1)||(d.find(*it)==d.find(*it+1)&&d.find(*it)==-1)){
					d.setunion(*it,*it+1);
					cells[*it].right=false;
				}
		}else{
			int temp=*it-cells.size();
			if(temp<(height-1)*width){
				if(d.find(temp)!=d.find(temp+width)||(d.find(temp)==d.find(temp+width)&&d.find(temp)==-1)){
				d.setunion(temp,temp+width);
				cells[temp].down=false;
				}
			}
		}
	}	
}


bool SquareMaze::canTravel(int x,int y, int dir) const{
	if(x>=w||y>=h||x<0||y<0)
		return false;
	if(((x==w-1)&&dir==0)||(x==0&&dir==2)||(y==0&&dir==3)||(y==h-1&&dir==1))
		return false;
	if(dir==0&&cells[y*w+x].right==true)
		return false;
	if(dir==1&&cells[y*w+x].down==true)
		return false;
	if(dir==2&&cells[y*w+x-1].right==true)
		return false;
	if(dir==3&&cells[(y-1)*w+x].down==true)
		return false;
	return true;

}


void SquareMaze::setWall(int x, int y, int dir, bool exists){
	if(dir==0)
		cells[y*w+x].right=!exists;
	else
		cells[y*w+x].down=!exists;

}


vector <int> SquareMaze::solveMaze(){
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			cells[j*w+i].visited=false;
		}
	}	
	vector<int> solution;	
	
	return solution;
}

PNG* SquareMaze::drawMaze() const{
	PNG* ret =new PNG(w*10+1,h*10+1);
	return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
	PNG* ret=drawMaze();
	return ret;
}

