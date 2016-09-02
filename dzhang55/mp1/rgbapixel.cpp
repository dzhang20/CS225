#include "rgbapixel.h"

RGBAPixel::RGBAPixel()
{
    alpha = 255;
    red = 255;
    green = 255;
    blue = 255;
}

RGBAPixel::RGBAPixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
    alpha =255;
}





