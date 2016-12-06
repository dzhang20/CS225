#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include "png.h"
#include <vector>
#include <map>
using namespace std;

class SquareMaze{
        public:
                SquareMaze();
                void makeMaze(int width,int height);
                bool canTravel(int x,int y,int dir)const;
                void setWall(int x, int y,int dir, bool exists);
                vector<int> solveMaze();
                PNG* drawMaze() const;
                PNG* drawMazeWithSolution();
	private:
		DisjointSets d;
		int w;
		int h;
		class Cell{
			public:
				int x;
				int y;
				bool visited;
				bool right;
				bool down;
		};
		vector<Cell> cells;	
};
#endif

