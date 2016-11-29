#pragma once
#include<iostream>
#include<SDL\SDL.h>
#include<GL\glew.h>
#include<string>
#include<Windows.h>


enum  WindowFlags {INVISIBLE=0x1, FULLSCREEN=0x2, BORDERLESS=0x4};
class Window
{
public:
	Window();
	~Window();
	
	int createWindow(std::string windowName, unsigned int currentFlags);
	int createWindow(std::string windowName, int _width, int _height, unsigned int currentFlags);
	void swapBuffer();

	void setWidth()
	{
		_width = GetSystemMetrics(SM_CXSCREEN);
	}

	void setHeight()
	{
		_height = GetSystemMetrics(SM_CYSCREEN);
	}

	int getWidth()
	{
		_width;
	}

	int getHeight()
	{
		_height;
	}
private:
	int _width;
	int _height;
	SDL_Window* _sdlWindow;
};

				