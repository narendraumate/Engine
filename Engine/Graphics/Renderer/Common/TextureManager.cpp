//
//  TextureManager.cpp
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#include "TextureManager.h"

TextureManager::TextureManager(const std::string& basePath)
:	m_basePath(basePath) {
}

TextureManager::~TextureManager() {
	for (std::map<std::string, Image*>::iterator it = m_nameImageMap.begin(); it != m_nameImageMap.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
}

void TextureManager::loadTexture(const std::string& textureName) {
	if (m_nameImageMap[textureName] == NULL)
	{
		m_nameImageMap[textureName] = new Image(m_basePath + textureName);
		m_nameImageMap[textureName]->flipY();
	}
}

int TextureManager::getSizeX(const std::string& textureName) {
	return m_nameImageMap[textureName]->getSizeX();
}

int TextureManager::getSizeY(const std::string& textureName) {
	return m_nameImageMap[textureName]->getSizeY();
}

void* TextureManager::getPixels(const std::string& textureName) {
	return (m_nameImageMap[textureName]->getPixels());
}
