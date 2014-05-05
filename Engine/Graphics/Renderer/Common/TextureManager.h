//
//  TextureManager.h
//  Application
//
//  Created by Narendra Umate on 5/4/14.
//
//

#ifndef __Application__TextureManager__
#define __Application__TextureManager__

#include <map>
#include <string>
#include "../../../External/stbi/StbImage.h"

class TextureManager
{
public:
	TextureManager(const std::string& basePath);
	~TextureManager();

	void loadTexture(const std::string& textureName);
	int getSizeX(const std::string& textureName);
	int getSizeY(const std::string& textureName);
	void* getPixels(const std::string& textureName);

private:
	std::string m_basePath;
	std::map<std::string, StbImage*> m_stbImageMap;
};

#endif /* defined(__Application__TextureManager__) */
