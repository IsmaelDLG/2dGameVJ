#ifndef _MY_COLOR_INCLUDE
#define _MY_COLOR_INCLUDE

using namespace std;

class myColor
{
	//asumim colors entre 0 i 255
public:
	myColor(unsigned int r,unsigned int g, unsigned int b, unsigned int a);
	~myColor();
	unsigned int getAlpha();
private:
	
private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

#endif // !