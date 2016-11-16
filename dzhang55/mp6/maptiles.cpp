/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	MosaicCanvas* target=new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	vector<Point<3>> RGB;
	map<Point<3>,TileImage> theMap;
	
	for(size_t i=0;i<theTiles.size();i++){
		RGBAPixel temp=theTiles[i].getAverageColor();
		Point<3> t(temp.red,temp.green,temp.blue);
		theMap[t]=theTiles[i];
		RGB.push_back(t);
	}
	
	KDTree<3> root(RGB);
	for(int i=0;i<(int)theSource.getRows();i++){
		for(int j=0;j<(int)theSource.getColumns();j++){
			RGBAPixel temp=theSource.getRegionColor(i,j);
			Point<3> t(temp.red,temp.green,temp.blue);
			t=root.findNearestNeighbor(t);
			target->setTile(i,j,theMap[t]);
		}
	}



	return target;
}

