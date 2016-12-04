#include "SpriteBatch.h"

using namespace DARE_Engine;

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	Glyph newGlyph;
	newGlyph.texture = texture;
	newGlyph.depth = depth;

	newGlyph.topLeft.color = color;
	newGlyph.topLeft.setPosition(destRect.x, destRect.y + uvRect.w);
	newGlyph.topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph.bottomLeft.color = color;
	newGlyph.bottomLeft.setPosition(destRect.x, destRect.y + uvRect.w);
	newGlyph.bottomLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph.topLeft.color = color;
	newGlyph.topLeft.setPosition(destRect.x, destRect.y + uvRect.w);
	newGlyph.topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph.topLeft.color = color;
	newGlyph.topLeft.setPosition(destRect.x, destRect.y + uvRect.w);
	newGlyph.topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);


}


SpriteBatch::SpriteBatch()
{
}


SpriteBatch::~SpriteBatch()
{
}
