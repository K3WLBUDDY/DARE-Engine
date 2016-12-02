#include<SDL\SDL.h>
#include<GL\glew.h>
#include"DARE_Engine.h"

//using namespace DARE_Engine;

int DARE_Engine::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//Sets the Attribute and its value. Here Double Buffer is set to 1.
	//start = 1;
	return 0;
}