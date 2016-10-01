#pragma once

#include"OpenGLTexture.h"
#include<string>
class ImageLoader
{
public:
	static OpenGLTexture loadPNG(std::string filePath);
};

