#include "ResourceManager.h"


TextureCache ResourceManager::_texCache;

OpenGLTexture ResourceManager::getTexture(std::string texPath)
{
	return _texCache.getTexture(texPath);
}