#include "TextureCache.h"
#include "ImageToTexture.h"
#include <iostream>

namespace Bengine
{
	TextureCache::TextureCache()
	{

	}

	TextureCache::~TextureCache()
	{

	}

	GLTexture TextureCache::getTexture(const std::string texturePath)
	{
		//lookup the texture and see if it's in the map
		auto mIter = _textureMap.find(texturePath);
		if (mIter == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageToTexture::loadPNG(texturePath);
			/*std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
			_textureMap.insert(newPair);*/
			//Insert it into the map
			_textureMap.insert(std::make_pair(texturePath, newTexture));
			std::cout << "Loaded Texture!" << std::endl;
			return newTexture;
		}
		std::cout << "Used Cached Texture!" << std::endl;
		return mIter->second;
	}
}