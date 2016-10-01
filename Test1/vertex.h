#pragma once

#include<GL\glew.h>

struct Position
{
	float x, y;
};

struct Color
{
	GLubyte r, g, b, a;
};

struct UV
{
	float u, v;
};

struct vertex
{
	Position position;
	Color color;
	UV uv;

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};