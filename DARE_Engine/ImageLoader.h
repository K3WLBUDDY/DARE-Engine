#pragma once

#include"OpenGLTexture.h"
#include<string>

using namespace std;

namespace DARE_Engine
{
	class ImageLoader
	{
		public:
		static OpenGLTexture loadPNG(string filePath);
	};

}

