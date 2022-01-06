#include <cstddef>
#include "Sprite.h"
#include "Vertex.h"
#include "ResManager.h"

namespace Bengine
{
	Sprite::Sprite()
	{
		//相当于一般的初始化置为空
		_vboID = 0;
	}
	Sprite::~Sprite()
	{
		if (_vboID != 0)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::initSprite(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResManager::getTexture(texturePath);

		if (_vboID == 0)
		{
			//generate a vertex buffer and then change VBOID to equal the ID of that buffer
			glCreateBuffers(1, &_vboID);
		}

		Vertex vertextData[6]{};
		//First Triangle
		/*vertextData[0].position.x = x + width;
		vertextData[0].position.y = y + height;*/
		vertextData[0].position.setPosition(x + width, y + height);
		vertextData[0].uv.setUV(1.0f, 1.0f);

		/*vertextData[1].position.x = x;
		vertextData[1].position.y = y + height;*/
		vertextData[1].position.setPosition(x, y + height);
		vertextData[1].uv.setUV(0.0f, 1.0f);

		/*vertextData[2].position.x = x;
		vertextData[2].position.y = y;*/
		vertextData[2].position.setPosition(x, y);
		vertextData[2].uv.setUV(0.0f, 0.0f);

		//Second Triangle
		/*vertextData[3].position.x = x;
		vertextData[3].position.y = y;

		vertextData[4].position.x = x + width;
		vertextData[4].position.y = y;

		vertextData[5].position.x = x + width;
		vertextData[5].position.y = y + height;*/

		vertextData[3].position.setPosition(x, y);
		vertextData[3].uv.setUV(0.0f, 0.0f);

		vertextData[4].position.setPosition(x + width, y);
		vertextData[4].uv.setUV(1.0f, 0.0f);

		vertextData[5].position.setPosition(x + width, y + height);
		vertextData[5].uv.setUV(1.0f, 1.0f);


		for (int i = 0; i < 6; ++i)
		{
			/*vertextData[i].color.r = 255;
			vertextData[i].color.g = 0;
			vertextData[i].color.b = 255;
			vertextData[i].color.a = 255;*/
			vertextData[i].color.setColor(255, 0, 255, 255);
		}
		/*vertextData[1].color.r = 0;
		vertextData[1].color.g = 255;
		vertextData[1].color.b = 0;
		vertextData[1].color.a = 255;*/

		vertextData[1].color.setColor(0, 255, 0, 255);
		vertextData[4].color.setColor(0, 0, 255, 255);

		//make this buffer(type) to be active---bind the buffer.
		//告诉这个显存（缓冲）是个什么类型
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//upload the buffer data---cpu(vertexData) to gpu(GL_ARRAY_BUFFER),must be bound before this.
		//if it is't static array,the second argument could be like sizeof(vertex) * 6.
		//这个时候才开辟显存
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertextData), vertextData, GL_STATIC_DRAW);
		//unbind to nothing---if you've bound vertex it will never this glCreateBuffers will never set VBOID to zero
		//because 0 indicates no buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		//Instead of making all these calls every frame,
		//what we can do is take all of these calls and put them
		//inside what's called a vertex array object.
		//It will hold all this state for us.
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//you need't to unbind texture,maybe another sprite that's going to use the same texture
		glBindTexture(GL_TEXTURE_2D, _texture.id);
		
		

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}