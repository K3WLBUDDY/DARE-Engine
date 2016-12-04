#include "Window.h"
#include "errors.h"
#include<iostream>

using namespace DARE_Engine;
using namespace std;

int Window::createWindow(std::string windowName, unsigned int currentFlags)
{
	setWidth();
	setHeight();

	cout << "\n\n RESOLUTION : " << width << "x" << height << endl;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}

	if (currentFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (currentFlags&BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);//Creates an SDL window
	if (_sdlWindow == nullptr)
	{
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow); //Creates an OpenGL context in the created SDL window
	if (glContext == nullptr)
	{
		fatalError("SDL_GL Context could not be created");
	}

	GLenum error = glewInit(); //Initialises GLEW and checks for error at the same time. 
	if (error != GLEW_OK)
	{
		fatalError("Could not Initialize GLEW");
	}

	std::cout << " OPENGL VERSION : " << glGetString(GL_VERSION);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//Sets the Attribute and its value. Here Double Buffer is set to 1.


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//Sets the Color of the OpenGL context to the specified values. In this case the color is black.

	SDL_GL_SetSwapInterval(1);

	return 0;

}


int Window::createWindow(std::string windowName, int windowWidth, int widnowHeight, unsigned int currentFlags)
{

	width = windowWidth;
	height = widnowHeight;

	cout << "\n\n RESOLUTION : " << width << "x" << height << endl;

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE)
	{
		flags |= SDL_WINDOW_HIDDEN;
	}

	if (currentFlags & FULLSCREEN)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (currentFlags&BORDERLESS)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (_sdlWindow == nullptr)
	{
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow); 
	if (glContext == nullptr)
	{
		fatalError("SDL_GL Context could not be created");
	}

	GLenum error = glewInit(); 
	if (error != GLEW_OK)
	{
		fatalError("Could not Initialize GLEW");
	}

	std::cout << "OPENGL VERSION : " << glGetString(GL_VERSION);
	


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//Sets the Color of the OpenGL context to the specified values. In this case the color is black.

	SDL_GL_SetSwapInterval(1);

	return 0;
}


void Window::setWidth()
{
	width = GetSystemMetrics(SM_CXSCREEN);	
}

void Window::setHeight()
{
	height = GetSystemMetrics(SM_CYSCREEN);
}


void Window::swapBuffer()
{
	SDL_GL_SwapWindow(_sdlWindow);
}

Window::Window() 
{
}


Window::~Window()
{
}
