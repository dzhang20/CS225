/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <map>
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Edge> ret=graph.getEdges();
    int min=INT_MAX;
    int id=0;
    for(int i=0;i<ret.size();i++){
	if(ret[i].weight<min){
		min=ret[i].weight;
		id=i;
	}
    }
    graph.setEdgeLabel(ret[id].source,ret[id].dest,"MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    reset(graph);
    graph.setVertexLabel(start,"VISITED");
    map<Vertex,Vertex> route;
    queue<Vertex> temp;
    temp.push(start);
    while(!temp.empty()){
 	Vertex curr=temp.front();
	temp.pop();
	vector<Vertex> next=graph.getAdjacent(curr);
	for(size_t i=0;i<next.size();i++){
		if(graph.getVertexLabel(next[i])=="UNEXPLORED"){
			temp.push(next[i]);
			graph.setEdgeLabel(curr,next[i],"DISCOVERY");
			graph.setVertexLabel(next[i],"VISITED");
			route[next[i]]=curr;	
		}else if(graph.getEdgeLabel(curr,next[i])=="UNEXPLORED")
			graph.setEdgeLabel(curr,next[i],"CROSS");
	}

    }
    int min=0;
    while(end!=start){
	graph.setEdgeLabel(end,route[end],"MINPATH");
	end=route[end];
	min++;	
    }
    return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
	vector<Edge> temp1=graph.getEdges();
	vector<Vertex> temp2=graph.getVertices();
	sort(temp1.begin(),temp1.end());
	DisjointSets ret;
	for(size_t i=0;i<temp2.size();i++)
		ret.addelements(temp2[i]);
	for(size_t i=0;i<temp1.size();i++){
		Vertex a=temp1[i].source;
		Vertex b=temp1[i].dest;
		if(ret.find(a)!=ret.find(b)){
			ret.setunion(a,b);
			graph.setEdgeLabel(a,b,"MST");
		}
	}



}

/**
 * Helper function to set all things UNEXPLORED
 */
void GraphTools::reset(Graph& graph){
    queue<Vertex> temp;
    Vertex curr= graph.getStartingVertex();
    graph.setVertexLabel(curr,"UNEXPLORED");
    temp.push(curr);
    while(!temp.empty()){
	curr=temp.front();
	vector<Vertex> next=graph.getAdjacent(curr);
	temp.pop();
	for(int i=0;i<next.size();i++){
		if(graph.getVertexLabel(next[i])!="UNEXPLORED"){
			graph.setEdgeLabel(curr,next[i],"UNEXPLORED");
			graph.setVertexLabel(next[i],"UNEXPLORED");
			temp.push(next[i]);
		}else if(graph.getEdgeLabel(curr,next[i])!="UNEXPLORED")
			graph.setEdgeLabel(curr,next[i],"UNEXPLORED");
	}
    }

}
