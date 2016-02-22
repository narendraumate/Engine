#include "stb_image_helper.h"

Image::Image(const string& name)
:	m_sizeX(0)
,	m_sizeY(0)
,	m_channels(0)
,	m_count(0) {
	int forceChannels = 4;
	m_pixels = stbi_load(name.c_str(), &m_sizeX, &m_sizeY, &m_channels, forceChannels);
	if (m_channels != forceChannels) {
		m_channels = forceChannels;
	}
	m_count = m_sizeY * m_sizeX * m_channels;
}

Image::~Image() {
	stbi_image_free(m_pixels);
}

void Image::flipY() {
	unsigned char* newPixels = new unsigned char[m_count];
	for (int y = 0; y < m_sizeY; ++y)
	{
		for(int x = 0; x < m_sizeX * m_channels; ++x)
		{
			newPixels[m_sizeX * (m_sizeY - 1 - y) * m_channels + x] = m_pixels[m_sizeX * y * m_channels + x];
		}
	}
	delete m_pixels;
	m_pixels = newPixels;
}
