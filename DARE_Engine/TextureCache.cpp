#include "TextureCache.h"
#include"ImageLoader.h"
#include<iostream>

using namespace DARE_Engine;

OpenGLTexture TextureCache::getTexture(std::string texPath)
{
	//std::map<std::string, OpenGLTexture>::iterator mit=_textureMap.find(texPath);
	auto mit = _textureMap.find(texPath); //Auto automatically gets the Datatype based on the Argument. Here it deduces that the texture map is a string.

	if (mit == _textureMap.end())//If the texture cannot be found in the Map
	{
		OpenGLTexture newTexture = ImageLoader::loadPNG(texPath);
		/*
		std::pair<std::string, OpenGLTexture> newPair(texPath, newTexture);

		_textureMap.insert(newPair);
		*/

		_textureMap.insert(make_pair(texPath, newTexture));//Inserts a new Texture along with its File Path into the cache

		std::cout << "\n Used Cached Texture";

		return newTexture;
	}
	std::cout << "\n Loaded Texture";

	return mit->second;


}
TextureCache::TextureCache()
{
}
TextureCache::~TextureCache()
{
}
