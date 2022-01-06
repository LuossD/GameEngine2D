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
		//���ﲻ����ָ����Ƿ������������ΪGLTexture���id����һ��ָ��ָ�������texture
		//���㿽��������ʱ���ǰ�ȫ�ģ���������౾���С;
		//���������õ���map�������Ȳ������texture�Ƿ��Ѿ�����
		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
