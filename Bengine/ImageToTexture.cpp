#include "ImageToTexture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

namespace Bengine
{
	/*
	void ImageToTexture::genTextureFromPNG(const std::string& filePath, texturePtr& texture)
	{
		std::vector<unsigned char> out;
		std::vector<unsigned char> in;
		unsigned long& width = texture->width;
		unsigned long& height = texture->height;

		if (!IOManager::readFileToBuf(filePath, in))
		{
			fatalError("Failed to load PNG file to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode)
		{
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &texture->id);
		glBindTexture(GL_TEXTURE_2D, texture->id);
		//upload the image data to the texture.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind it when you've done.
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	*/
	GLTexture ImageToTexture::loadPNG(const std::string& filePath)
	{
		GLTexture texture{};
		std::vector<unsigned char> out;
		std::vector<unsigned char> in;
		unsigned long& width = texture.width;
		unsigned long& height = texture.height;

		if (!IOManager::readFileToBuf(filePath, in))
		{
			fatalError("Failed to load PNG file to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode)
		{
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		//Generates a texture object name.Write values in through Pointers and bring them out
		glGenTextures(1, &texture.id);
		//Bind texture type
		glBindTexture(GL_TEXTURE_2D, texture.id);
		//upload the image data to the texture.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind it when you've done.
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}
}