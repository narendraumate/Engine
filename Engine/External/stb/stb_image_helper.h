#ifndef STBIMAGE
#define STBIMAGE

#include <iostream>
#include <vector>
using namespace std;

#include "stb_image.h"

class Image
{
public:
	Image(const string& name);
	virtual ~Image();
	
	inline unsigned char* getPixels() { return m_pixels; } const
	inline int getSizeX() const { return m_sizeX; }
	inline int getSizeY() const { return m_sizeY; }	

	void flipY();
	
private:
	//vector<unsigned char> m_pixels;
	unsigned char* m_pixels;
	int m_sizeX;
	int m_sizeY;
	int m_channels;
	int m_count;
};

#endif // STBIMAGE
