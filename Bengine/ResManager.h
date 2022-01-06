#pragma once
#include <string>
#include "TextureCache.h"

namespace Bengine
{
	class ResManager
	{
	public:
		static GLTexture getTexture(const std::string texturePath);

		static GLuint _boundTexture;

	private:
		static TextureCache _textureCache;
	};
}
