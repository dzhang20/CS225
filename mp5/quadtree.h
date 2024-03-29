/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
	Quadtree();
	Quadtree(const PNG& source, int resolution);
	Quadtree(Quadtree const& other);
	~Quadtree();
	Quadtree const& operator=(Quadtree const & other);
	void buildTree(PNG const& source, int resolution);
	RGBAPixel getPixel(int x,int y) const;
	PNG decompress() const;
	void clockwiseRotate();
	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     
    */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
	int x_coord;
	int y_coord;
	int resol;
    };
	//helper functions
	//
	QuadtreeNode* copy(QuadtreeNode* subRoot);
	void clear(QuadtreeNode* subRoot)const;
	QuadtreeNode* buildTree(PNG const& source,int x,int y,int resolution)const;
	RGBAPixel getPixel(int x,int y,int a,int b,int resolution,QuadtreeNode* subRoot)const;
	void clockwiseRotate(QuadtreeNode* subRoot);
	void prune(int tolerance, QuadtreeNode* subRoot);
	int diff(QuadtreeNode* subRoot,QuadtreeNode* leaf)const;
	bool prunable(int tolerance,QuadtreeNode* subRoot,QuadtreeNode* leaf)const;
	int pruneSize(int tolerance,QuadtreeNode* subRoot)const;
    QuadtreeNode* root; /**< pointer to root of quadtree */
/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
