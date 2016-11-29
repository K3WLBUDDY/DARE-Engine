#pragma once
#include"TextureCache.h"

namespace DARE_Engine
{
	class ResourceManager
	{
	public:
		static OpenGLTexture getTexture(std::string texPath);

		//static GLuint _boundTex;

	private:
		static TextureCache _texCache;
	};

}