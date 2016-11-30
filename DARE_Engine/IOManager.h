#pragma once
#include<string>
#include<vector>
//This is a static class. No constructor or destructor needed.

using namespace std;

namespace DARE_Engine
{
	class IOManager
	{
	public:

		static bool readFileToBuffer(vector<unsigned char>& buffer, string filepath);
	};
}

