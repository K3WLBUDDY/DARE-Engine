#include "GLSLProgram.h"
#include"errors.h"
#include<vector>

#include<fstream>
#include<string>
#include<iostream>
#include<SDL\SDL.h>

using namespace std;
using namespace DARE_Engine;

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)  //Initialization List. Slightly Faster
{
	
}


//Getter for getting both the Shaders and creating a Program ID
void GLSLProgram::compileShaders(const string& VertexShaderFilePath, const string& FragmentShaderFilePath)
{
	  _programID = glCreateProgram(); //Creates a program ID to be later used when linking the shaders

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) //0 signifies an error in creating the Shader.
	{
		fatalError("Vertex Shader failed to be created");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		fatalError("Fragment Shader failed to be created");
	}

	compileShader(VertexShaderFilePath, _vertexShaderID);
	compileShader(FragmentShaderFilePath, _fragmentShaderID);

	
}


//To Compile Individual Shaders. 
void GLSLProgram::compileShader(const string& filePath, GLuint id)
{

	//File Pointer to parse through the Shaders.

	ifstream vertexFile(filePath); //Creates a stream connection between the C++ compiler and the Shader File
	if (vertexFile.fail())
	{
		perror(filePath.c_str()); //perror is a C function for printing errors related to file operations.
		fatalError("Failed to Open" + filePath);
	}
	string fileContents = ""; //One String Variable to hold the entire shader code
	string line;

	while (getline(vertexFile, line))  //Gets Contents of the Shader line by line
	{
		fileContents += line + "\n"; //Getline does not get the \n along with its contents. \n must be truncated to the output of Getline
	}

	vertexFile.close(); //Can be avoided as the file gets deleted when it goes out of scope

	const char* contentPtr = fileContents.c_str(); //c.str() converts the contents of a std::string to a const char* for compatibility with C functions.

	glShaderSource(id, 1, &contentPtr, nullptr); //Inputs the strings read by the file pointer.

	glCompileShader(id);  //Compiles the Shader

	GLint success = 0;

	glGetShaderiv(id, GL_COMPILE_STATUS, &success); //Returns the  details of the compilation. 


	//Error Checking for any compilation Errors

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength); //Returns the Max Length of the Error Log generated

		vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]); //Stores the Error Log in a vector char variable.

		glDeleteShader(id); //Deletes the wrongly compiled Shader

		printf("%s\n", &(errorLog[0]));
		fatalError("Shader failed to Compile");

		SDL_Quit();
	}
}


void GLSLProgram::linkShaders()
{
	/*
	Any input parameters must be set before linking or else they won't be set at all*/
	

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		

		//Use the infoLog as you see fit.
		printf("%s\n", &(infoLog[0]));
		fatalError("Shader failed to Link");
		
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string& attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str()); //Binds the Attribute Name if it is present in the Shader Program to the OpenGl Code.
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		//cout << "\n Attrib No.: " << i;
		glEnableVertexAttribArray(i); //Enables the Vertex Attributes. Must be done to use the Attribute.
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i); //Disable the Vertex Attributes
	}
}

GLint GLSLProgram::getUniformLocation(const string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str()); //Returns the Location of the Uniform Variable
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform" + uniformName + "not found in Shader");
	}
	return location;


}


GLSLProgram::~GLSLProgram()
{
}
