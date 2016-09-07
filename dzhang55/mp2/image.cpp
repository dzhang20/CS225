#include "image.h"

void Image::flipleft(){
	int height = (*this).height();
	int width = (*this).width();
	RGBAPixel temp = *(*this).operator()(0,0);
	for (int x=0; x< width/2; x++){
		for (int y=0; y<height; y++){
			RGBAPixel* left = this->operator()(x,y);
			RGBAPixel* right = this->operator()(width-x-1,y);
			temp = *left;
			*left = *right; 
			*right= temp;
		}
	}

}


void Image::adjustbrightness(int r, int g, int b){
	int height = (*this).height();
	int width = (*this).width();
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			if((*this).operator()(x,y)->red+r>255)
				(*this).operator()(x,y)->red=255;
			else if((*this).operator()(x,y)->red+r<0)
				(*this).operator()(x,y)->red=0;
			else
				(*this).operator()(x,y)->red= (*this).operator()(x,y)->red+r;			
			if((*this).operator()(x,y)->green+g>255)
				(*this).operator()(x,y)->green=255;
			else if((*this).operator()(x,y)->green+g<0)
				(*this).operator()(x,y)->green=0;
			else
				(*this).operator()(x,y)->green= (*this).operator()(x,y)->green+g;
			if((*this).operator()(x,y)->blue+b>255)
				(*this).operator()(x,y)->blue=255;
			else if((*this).operator()(x,y)->blue+b<0)
				(*this).operator()(x,y)->blue=0;
			else
				(*this).operator()(x,y)->blue= (*this).operator()(x,y)->blue+b;

		}
	}

}


void Image::invertcolors(){
	int height = this->height();
	int width = this->width();
	
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			(*this).operator()(x,y)->red= 255-(*this).operator()(x,y)->red;			
			(*this).operator()(x,y)->green= 255-(*this).operator()(x,y)->green;
			(*this).operator()(x,y)->blue= 255-(*this).operator()(x,y)->blue;
		}
	}
}


