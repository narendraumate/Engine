//
//  TextureManager.cpp
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#include "TextureManager.h"

TextureManager::TextureManager(const std::string& basePath)
:	m_basePath(basePath)
{ }

TextureManager::~TextureManager()
{
	for (std::map<std::string, StbImage*>::iterator it = m_stbImageMap.begin(); it != m_stbImageMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
}

void TextureManager::loadTexture(const std::string& textureName)
{
	if (m_stbImageMap[textureName] == NULL)
	{
		m_stbImageMap[textureName] = new StbImage(m_basePath + textureName);
		m_stbImageMap[textureName]->flipY();
	}
}

int TextureManager::getSizeX(const std::string& textureName)
{
	return m_stbImageMap[textureName]->getSizeX();
}

int TextureManager::getSizeY(const std::string& textureName)
{
	return m_stbImageMap[textureName]->getSizeY();
}

void* TextureManager::getPixels(const std::string& textureName)
{
	return &(m_stbImageMap[textureName]->getPixels()[0]);
}
