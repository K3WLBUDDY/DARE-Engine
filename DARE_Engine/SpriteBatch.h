#include<vector>
#include<glm\glm.hpp>
#include <GL\glew.h>
#include"vertex.h"
#pragma once



namespace DARE_Engine
{

	enum class GlyphSortType{ NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

	struct Glyph // Structure for Single sprite. Holds the type of texture and depth. Depth is for layering sprites on top of each other
	{
		GLuint texture;
		float depth;

		vertex topLeft;
		vertex topRight;
		vertex bottomLeft;
		vertex bottomRight;
	};

	class renderBatch
	{
	public:

		renderBatch(GLuint Offset, GLuint NumVertices, GLuint Textures) : offset(Offset), numVertices(NumVertices), texture(Textures)
		{

		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
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

		void createRenderBatches();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBacktoFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GlyphSortType _sortType;

		GLuint _vbo; //Provides Buffer Data to be used in the Array Object
		GLuint _vao; // Holds the state information for draw calls

		std::vector<Glyph*> _glyphs;
		std::vector<DARE_Engine::renderBatch> _renderBatches;

	};
}