#include "ResourceManager.h"

using namespace DARE_Engine;

TextureCache ResourceManager::_texCache;

OpenGLTexture ResourceManager::getTexture(std::string texPath)
{
	return _texCache.getTexture(texPath);
}