#pragma once
#include<string>
#include<vector>
//This is a static class. No constructor or destructor needed.

namespace DARE_Engine
{
	class IOManager
	{
	public:

		static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filepath);
	};
}

