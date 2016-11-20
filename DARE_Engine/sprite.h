#pragma once
#include<GL\glew.h>
#include<string>
#include"ResourceManager.h"
class sprite
{
public:
	sprite();
	~sprite();

	void init(float x, float y, float width, float height,std::string texPath);//Gets the data to be sent to the VBO.

	void draw();
private:

	float _x, _y, _width, _height;
	GLuint _vboID;
	OpenGLTexture _texture;
};

