#pragma once
#include"TextureCache.h"
class ResourceManager
{
public:
	static OpenGLTexture getTexture(std::string texPath);

	//static GLuint _boundTex;
	
private:
	static TextureCache _texCache;
};

