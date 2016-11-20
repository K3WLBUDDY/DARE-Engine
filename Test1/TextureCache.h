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
	std::map<std::string, OpenGLTexture> _textureMap;//Maps form a combination of Key and Mapped values. First parameter is the key value and the second parameter is the mapped value. Here it gets an address and checks if that address points to the correct TExture in the cache
};

