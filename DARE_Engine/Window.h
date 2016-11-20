#include<SDL\SDL.h>
#include<GL\glew.h>
#include<string>
#pragma once

enum WindowFlags (INVISIBLE=0x1, FULLSCREEN=0x2, BORDERLESS=0x4);
class Window
{
public:
	Window();
	~Window();
	
	int createWindow(std::string windowName, int width, int height, unsigned int currentFlags);

	int getWidth()
	{
		_width;
	}
	int getHeight()
	{
		_height;
	}
private:
	SDL_Window*  _sdlWindow;
	int _width, _height;
};

