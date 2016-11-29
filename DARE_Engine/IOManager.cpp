#include "IOManager.h"
#include<fstream>


using namespace DARE_Engine;

bool IOManager::readFileToBuffer(std::vector<unsigned char>& buffer, std::string filepath) //Calling Buffer by Value ie it takes the reference of the in vector
{
	std::ifstream file(filepath, std::ios::binary);//File read in binary format. Just the Raw data. 
	if (file.fail())
	{
		perror(filepath.c_str());//Perror prints the error message. It takes a C String as an argument.
		return false;
	}
	file.seekg(0, std::ios::end);//Seeks to the end. First parameter is the byte offset. Here it is 0 bytes offset from the end
	int fileSize = file.tellg();//Tells the bytes passed by the get pointer. 
	file.seekg(0, std::ios::beg);//Places the get pointer at the beginning of the file.

	//Negating any header size such as date of modification or some other metadata about the file.
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);//Reads bytes into the buffer.  char* is an array of chars. To parse it into the vector pass it into the address of the first elemeet of the buffer.
	file.close();

	return true;

}