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

void SpriteBatch::createRenderBatches()
{
	std::vector <vertex> vertices;
	//vertices.reserve(_glyphs.size() * 6);
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty())
		return;

	int offset = 0; 
	int cv = 0;
	//DARE_Engine::renderBatch myBatch(0, 6, _glyphs[0]->texture);
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;

	offset += 6;
	for (int cg = 1; cg < _glyphs.size(); cg++)
	{
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->bottomLeft;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), vertices.data(), GL_DYNAMIC_DRAW);//GL_STREAM_DRAW

	//Orphoning the Buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER,0);
	

		
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
	_renderBatches.clear();
	_glyphs.clear();

}

void SpriteBatch::end()
{
	sortGlyph();
	createRenderBatches();
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
	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
}
SpriteBatch::SpriteBatch() :_vbo(0), _vao(0)
{

}


SpriteBatch::~SpriteBatch()
{

}
