#include "ResManager.h"

namespace Bengine
{
	TextureCache ResManager::_textureCache;

	GLTexture ResManager::getTexture(const std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}