#include <algorithm>
#include "SpriteBatch.h"

namespace Bengine
{
	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{

	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
	{
		_sortType = sortType;
		//clear doesn't free all of the memory exactly,
		//what it does is just changes the size of the vector back to zero.
		/*
		If you want to actually free the memory completely,there's other tricks,
		but we don't really need to do that here, it's actually beneficial to keep
		the memory allocated because it'll be a little bit faster.
		*/
		for (int i = 0; i < _glyphs.size(); ++i)
		{
			delete _glyphs[i];
		}
		_renderBatches.clear();
		_glyphs.clear();

	}

	void SpriteBatch::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::setDraw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, const float& depth, const Color& color)
	{
		Glyph* newGlyph = new Glyph();
		
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.position.setPosition(destRect.x,destRect.y + destRect.w);
		newGlyph->topLeft.uv.setUV(uvRect.x,uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.position.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.uv.setUV(uvRect.x, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.position.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.uv.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.position.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.uv.setUV(uvRect.x + uvRect.z, uvRect.y);
		
		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size(); ++i)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i]._texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i]._offset, _renderBatches[i]._numVertices) ;
		}
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);
		if (_glyphs.empty())
		{
			return;
		}

		int offset = 0;
		int cv = 0; //current vertex
		/*RenderBatch myBatch(0, 6, _glyphs[0]->texture);
		_renderBatches.push_back(myBatch);*/
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		vertices[cv++] = _glyphs[0]->topLeft;
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topLeft;
		offset += 6;
		
		int cg = 1; //current Glyph
		for (cg; cg < _glyphs.size(); ++cg)
		{
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			{
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			}
			else
			{
				_renderBatches.back()._numVertices += 6;
			}
			vertices[cv++] = _glyphs[cg]->topLeft;
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		/*
		Since we're using the same vertex buffer object,there's going to already be some
		data in here, and when we call glBufferData, it's going to have to overwrite that data 
		and that takes a little bit of time.
		There's a little trick we can do where we tell OpenGL that
		I don't want the old buffer anymore at all, you can just throw it away
		and give me a band new buffer and it'll be a little bit faster.
		This two lines is the faster way to do it.It avoids overwrite the data. 
		*/
		//Orphan the buffer.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray()
	{
		if (_vao == 0)
		{
			glCreateVertexArrays(1, &_vao);
		}
		//Bind it means that anything else that you do to change
		//the OpenGL state in here is going to be stored in the vao.
		glBindVertexArray(_vao);

		if (_vbo == 0)
		{
			glCreateBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//you can think of this as an array and we're only using the very first element of the array(position)
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//This is the color attribute pointer.Transform [0, 255] to [0, 1].
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//This is the UV attribute pointer
		//The second attribute,it has 2 elements
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//It's going to disable all of these VertexAttribArray and unbind our VBO and everything.
		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (_sortType)
		{
		
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
		default:
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
}

