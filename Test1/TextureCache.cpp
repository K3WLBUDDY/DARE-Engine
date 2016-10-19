#include "TextureCache.h"
#include"ImageLoader.h"
#include<iostream>



OpenGLTexture TextureCache::getTexture(std::string texPath)
{
	//std::map<std::string, OpenGLTexture>::iterator mit=_textureMap.find(texPath);
	auto mit = _textureMap.find(texPath);

	if (mit == _textureMap.end())
	{
		OpenGLTexture newTexture = ImageLoader::loadPNG(texPath);
		/*
		std::pair<std::string, OpenGLTexture> newPair(texPath, newTexture);

		_textureMap.insert(newPair);
		*/

		_textureMap.insert(make_pair(texPath, newTexture));

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
