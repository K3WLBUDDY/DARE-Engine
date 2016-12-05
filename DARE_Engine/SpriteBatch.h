#include<vector>
#include<glm\glm.hpp>
#include <GL\glew.h>
#include"vertex.h"
#pragma once

namespace DARE_Engine
{

	struct Glyph // Structure for Single sprite. Holds the type of texture and depth. Depth is for layering sprites on top of each other
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

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE); // Ready for Drawing
		void end(); //Post stuff like sorting images
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color); //Adds to the Batch
		void renderBatch(); // Renders to the Screen
		void init();


	private:
		void createVertexArray(); //Creates a Vertex Array Object fo storing states of the Sprites and takes care of the various buffers
		void sortGlyph(); //Sorts the Order of the Glyphs based on the 

		GlyphSortType _sortType;

		GLuint _vbo;
		GLuint _vao; // Holds the state information for draw calls

		std::vector<Glyph*> _glyphs;

	};
}