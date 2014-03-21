#ifndef STBIMAGE
#define STBIMAGE

#include <iostream>
#include <vector>
using namespace std;

#include "stb_image.h"

class StbImage
{
public:
	StbImage(const string& name);
	
	inline vector<unsigned char> getPixels() { return m_pixels; } const
	inline int getSizeX() const { return m_sizeX; }
	inline int getSizeY() const { return m_sizeY; }	
	void flipY();
	
private:
	vector<unsigned char> m_pixels;
	int m_sizeX;
	int m_sizeY;
	int m_channels;
};

#endif // STBIMAGE
