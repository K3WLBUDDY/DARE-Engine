#pragma once
#include<iostream>
#include<SDL\SDL.h>
#include<GL\glew.h>
#include<string>
#include<Windows.h>

namespace DARE_Engine
{
	enum  WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };
	class Window
	{
	public:
		Window();
		~Window();

		int createWindow(std::string windowName, unsigned int currentFlags);
		int createWindow(std::string windowName, int _width, int _height, unsigned int currentFlags);
		void swapBuffer();

		void setWidth();


		void setHeight();

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
}

				