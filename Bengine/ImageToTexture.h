#pragma once
#include <string>
#include "GLTexture.h"

namespace Bengine
{
	//static class
	class ImageToTexture
	{
	public:
		typedef GLTexture* texturePtr;
		//static void genTextureFromPNG(const std::string& filePath, texturePtr& texture);
		static GLTexture loadPNG(const std::string& filePath);
	};
}

   
