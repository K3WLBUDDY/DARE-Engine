#pragma once

#include"OpenGLTexture.h"
#include<string>

namespace DARE_Engine
{
	class ImageLoader
	{
	public:
		static OpenGLTexture loadPNG(std::string filePath);
	};
}

