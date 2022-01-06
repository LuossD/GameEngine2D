#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

namespace Bengine
{
	
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	
	//It's just a single sprite essentially, it's going to have the six vertices
	//that we normally have for a sprite.
	//It's also going to hold what type of texture it's going to use,
	//it's also going to hold the depth.
	struct Glyph
	{
		//根据texture决定一批我们要画的SpriteBatch，这样减少纹理切换以及绘制的调用次数
		GLuint texture;
		float depth;
		
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};
	
	class RenderBatch
	{
	public:
		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) :
			_offset(offset),
			_numVertices(numVertices),
			_texture(texture)
		{
		}
		GLuint _offset;
		GLuint _numVertices;
		GLuint _texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void setDraw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, const float& depth, const Color& color);

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
	};

}

