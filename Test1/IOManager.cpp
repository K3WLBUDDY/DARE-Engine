#include "IOManager.h"
#include<fstream>


bool IOManager::readFileToBuffer(std::vector<unsigned char>& buffer, std::string filepath)
{
	std::ifstream file(filepath, std::ios::binary);
	if (file.fail())
	{
		perror(filepath.c_str());
		return false;
	}

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Negating any header size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;

}