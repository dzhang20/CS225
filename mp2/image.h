#ifndef Image_H
#define Image_H

#include "png.h"

class Image : public PNG
{
	public:
		void flipleft();
		void adjustbrightness(int r, int g, int b);
		void invertcolors();
};
#endif
