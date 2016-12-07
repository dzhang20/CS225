#include "maze.h"
#include <vector>
#include <map>
#include <queue>


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
	if(x>w||y>h||x<0||y<0)
		return false;
	if(((x==w-1)&&dir==0)||(x==0&&dir==2)||(y==0&&dir==3)||(y==h-1&&dir==1))
		return false;
	if(dir==0)
		return !cells[x+w*y].right;
	if(dir==1)
		return !cells[x+w*y].down;
	if(dir==2)
		return !cells[y*w+x-1].right;
	if(dir==3)
		return !cells[(y-1)*w+x].down;
	return false;

}


void SquareMaze::setWall(int x, int y, int dir, bool exists){
	if(dir==0)
		cells[y*w+x].right=exists;
	else if(dir==1)
		cells[y*w+x].down=exists;

}


vector <int> SquareMaze::solveMaze(){
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			cells[j*w+i].visited=false;
		}
	}		
	map<int,int> sol;
	queue<int> q;
	q.push(0);
	cells[0].visited=true;
	while(!q.empty()){
		int cur=q.front();
		int curX=cur%w;
		int curY=cur/w;
		q.pop();
		for(int i=0;i<4;i++){
			int next;
			if(i==0)
				next=cur+1;
			else if(i==1)
				next=cur+w;
			else if(i==2)
				next=cur-1;
			else 
				next=cur-w;
			if(canTravel(curX,curY,i)&&cells[next].visited==false){
				q.push(next);
				cells[next].visited=true;
				sol[next]=cur;
			}
		}
	}
	int index=0;
	int max=0;
	for(int i=0;i<w;i++){
		int count=0;
		int temp=i+(h-1)*w;
		if(sol.count(temp)>0)
			while(temp!=0){
				temp=sol[temp];
				count++;
			}
		if(count>max){
			max=count;
			index=i;
		}
	}
	index=index+(h-1)*w;
	vector<int> solution;
	while(index!=0){
		if(index-sol[index]==1)
			solution.push_back(0);
		else if(index-sol[index]==-1)
			solution.push_back(2);
		else if(index-sol[index]==w)
			solution.push_back(1);
		else if(index-sol[index]==-1)
			solution.push_back(3);
		index=sol[index];
	}
	reverse(solution.begin(),solution.end());
	return solution;
}

PNG* SquareMaze::drawMaze() const{
	PNG* ret =new PNG(w*10+1,h*10+1);
	for(int i=10;i<10*w+1;i++){
		(*ret)(i,0)->red=0;
		(*ret)(i,0)->green=0;
		(*ret)(i,0)->blue=0;
	}
	for(int i=0;i<10*h+1;i++){
                (*ret)(0,i)->red=0;
                (*ret)(0,i)->green=0;
                (*ret)(0,i)->blue=0;
        }
	for(size_t i=0;i<cells.size();i++){
		if(cells[i].right==true){
			for(int j=0;j<=10;j++){
				(*ret)((i%w+1)*10,(i/w)*10+j)->red=0;
				(*ret)((i%w+1)*10,(i/w)*10+j)->green=0;
				(*ret)((i%w+1)*10,(i/w)*10+j)->blue=0;
			}
		}
		 if(cells[i].down==true){
                        for(int j=0;j<=10;j++){
                                (*ret)((i%w)*10+j,(i/w+1)*10)->red=0;
                                (*ret)((i%w)*10+j,(i/w+1)*10)->green=0;
                                (*ret)((i%w)*10+j,(i/w+1)*10)->blue=0;
                        }
                }
	}
	return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
	PNG* ret=drawMaze();
	int cx=5;
	int cy=5;
	vector<int> solution=solveMaze();
	for(auto it=solution.begin();it!=solution.end();it++){
		if(*it==0){
			for(int i=0;i<=10;i++){
				(*ret)(cx,cy)->red=255;
				(*ret)(cx,cy)->green=0;
				(*ret)(cx,cy)->blue=0;
			}
			cx+=10;
		}else if(*it==1){
                        for(int i=0;i<=10;i++){
                                (*ret)(cx,cy)->red=255;
                                (*ret)(cx,cy)->green=0;
                                (*ret)(cx,cy)->blue=0;
                        }
                        cy+=10;
                }else if(*it==2){
                        for(int i=0;i<=10;i++){
                                (*ret)(cx,cy)->red=255;
                                (*ret)(cx,cy)->green=0;
                                (*ret)(cx,cy)->blue=0;
                        }
                        cx-=10;
                }else if(*it==3){
                        for(int i=0;i<=10;i++){
                                (*ret)(cx,cy)->red=255;
                                (*ret)(cx,cy)->green=0;
                                (*ret)(cx,cy)->blue=0;
                        }
                        cy-=10;
                }
	}
	cx-=5;
	cy-=5;
	for(int i=1;i<=9;i++){
		(*ret)(cx+i,cy)->red=255;
		(*ret)(cx+i,cy)->green=255;
		(*ret)(cx+i,cy)->blue=255;

	}
	return ret;
}

