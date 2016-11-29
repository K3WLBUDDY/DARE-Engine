#pragma once
#include<string>
#include<GL\glew.h>

namespace DARE_Engine
{

	using namespace std;

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		GLint getUniformLocation(const string& uniformName); //Returns the location of the Uniform Variable.

		void compileShaders(const string& VertexShaderFilePath, const string& FragmentShaderFilePath);//To get details about the Shaders and generate an ID
		/*The FilePaths are referenced to avoid copying it every time*/

		void linkShaders();//Links the Shaders into a single program

		void addAttribute(const string& attributeName); //Binds the Attributes found in the Shader Program
		void use(); //To Use the Shader Program.
		void unuse(); //To unuse or unbind the SHader program
	private:
		int _numAttributes; //Keeps track of the Number of Attributes bound
		GLuint _programID; // An ID for the compiled program containing both the Shaders.
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		void compileShader(const string& filePath, GLuint id);//Compiles the Shaders individually.

	};
}
/* 
The Vertex Shader manipulates the data present alongside the vertices.
By default it passes through by doing interpolation thereby creating a gradiant fill for the triangle
*/

