#include "myColor.h"

myColor::myColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{

	red = r;
	green = g;
	blue = b;
	alpha = a;
}

myColor::~myColor()
{
}

unsigned int myColor::getAlpha()
{
	return alpha;
}
