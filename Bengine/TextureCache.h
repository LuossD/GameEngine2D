#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace Bengine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		//这里不返回指针而是返回类对象，是因为GLTexture里的id就像一个指针指向了这个texture
		//当你拷贝这个类的时候是安全的，而且这个类本身很小;
		//另外这里用的是map，它会先查找这个texture是否已经存在
		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
