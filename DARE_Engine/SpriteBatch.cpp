#include "SpriteBatch.h"
#include<algorithm>

using namespace DARE_Engine;

enum class GlyphSortType{NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE};

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
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
	//sortGlyph();
}

void SpriteBatch::sortGlyph()
{
	
	std::stable_sort();
}

SpriteBatch::SpriteBatch() :_vbo(0), _vao(0)
{
}


SpriteBatch::~SpriteBatch()
{
}
