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
	unsigned int getBlack();
	unsigned int getGreen();
	unsigned int getBlue();
	unsigned int getRed();


private:
	unsigned int max(unsigned int r, unsigned int g, unsigned int b);
	unsigned int min(unsigned int r, unsigned int g, unsigned int b);
private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

#endif // !