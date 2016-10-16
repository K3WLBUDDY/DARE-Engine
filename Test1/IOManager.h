#pragma once
#include<string>
#include<vector>
//This is a static class. No constructor or destructor needed.
class IOManager
{
public:
	
	static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filepath);
};

