#include<vector>
#include<glm\glm.hpp>
#include <GL\glew.h>
#include"vertex.h"
#pragma once

namespace DARE_Engine
{

	struct Glyph // Single sprite. Holds the type of texture and depth. Depth is for layering sprites on top of each other
	{
		GLuint texture;
		float depth;

		vertex topLeft;
		vertex topRight;
		vertex bottomLeft;
		vertex bottomRight;
	};

	class SpriteBatch // Each Texture has its own batch. 
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(); // Ready for Drawing
		void end(); //Post stuff like sorting images
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color); //Adds to the Batch
		void renderBatch(); // Renders to the Screen
		void init();


	private:

		GLuint _vbo;
		GLuint _vao;

		std::vector<Glyph> _glyphs;

	};
}