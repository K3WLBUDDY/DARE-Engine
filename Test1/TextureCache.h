#pragma once
#include<map>
#include"OpenGLTexture.h">
class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	OpenGLTexture getTexture(std::string);

private:
	std::map<std::string, OpenGLTexture> _textureMap;
};

