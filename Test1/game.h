#pragma once
#include<SDL/SDL.h>
#include<GL/glew.h>
#include<DARE_Engine/sprite.h>
#include<DARE_Engine/GLSLProgram.h>
#include<DARE_Engine/OpenGLTexture.h>
#include<Windows.h>
#include<vector>




enum class gamestate {PLAY,STOP}; //Global enum to check if the player has pressed the exit button or not.

class game
{
public:
	void run(); //Function that Starts everything
	void process_input();//Polls for a mouse event and prints the coordinates of the pointer.
	void drawGame();//Draws the Sprite along with the Shader
	void initsystems();//Initialises the SDL window, OpenGL Context and GLEW.
	void initShaders();//Initialises the Shaders.
	game();
	~game();
	gamestate games;
private:
	SDL_Window* _window;
	sprite _sprite;
	int width, height;
	void getResolution();
	void fpsCounter();
	float time;
	GLSLProgram _colorProgram;
	//OpenGLTexture _playerTexture; //Initialises a texture with the attributes defined in OpenGLTexture.h
	OpenGLTexture _ChangeTexture;
	std::vector<sprite*> _sprites; //Declares a Vector for Sprites.
	float _fps, _frameTime, _maxFPS;
};

