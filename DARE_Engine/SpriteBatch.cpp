#include "SpriteBatch.h"
#include<algorithm>

using namespace DARE_Engine;

enum class GlyphSortType{NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE}; //For sorting the Glyphs

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	//TODO : Figure out the UV Maps for the Tex


	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + uvRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + uvRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	_glyphs.push_back(newGlyph);


}

void SpriteBatch::createVertexArray()
{

	if (_vao==0)
		glGenVertexArrays(1, &_vao);

	glBindVertexArray(_vao);	

	if (_vbo==0)	
		glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);//Enables the Vertex Attributes
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));//Defines an array from which data is used to draw
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));

	glBindVertexArray(0);


}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
	_sortType = sortType;
}

void SpriteBatch::end()
{
	sortGlyph();
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return(a->depth < b->depth);
}

bool SpriteBatch::compareBacktoFront(Glyph* a, Glyph* b)
{
	return(a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return(a->texture < b->texture);
}
void SpriteBatch::sortGlyph()
{
	switch (_sortType)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBacktoFront); //Depth defines the sort order
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
		break;
	}
	
}

void SpriteBatch::renderBatch()
{

}
SpriteBatch::SpriteBatch() :_vbo(0), _vao(0)
{

}


SpriteBatch::~SpriteBatch()
{

}
