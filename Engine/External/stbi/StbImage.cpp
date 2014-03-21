#include "StbImage.h"

StbImage::StbImage(const string& name)
:	m_sizeX(0)
,	m_sizeY(0)
,	m_channels(0)
{
	int forceChannels = 4;
	
	unsigned char *pixels = stbi_load(name.c_str(), &m_sizeX, &m_sizeY, &m_channels, forceChannels);
	
	if (m_channels != forceChannels)
	{
		m_channels = forceChannels;
	}

	for (int i = 0; i < m_sizeY * m_sizeX * m_channels; ++i)
	{
		m_pixels.push_back(pixels[i]);
	}
	
	stbi_image_free(pixels);	
}

void StbImage::flipY()
{
	vector<unsigned char> res = m_pixels;
	for (int y = 0; y < m_sizeY; ++y)
	{
		for(int x = 0; x < m_sizeX * m_channels; ++x)
		{
			m_pixels[m_sizeX*(m_sizeY-1-y)*m_channels+x] = res[m_sizeX*y*m_channels+x];
		}
	}
}
