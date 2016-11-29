#pragma once
#include<SDL/SDL.h>
#include<GL/glew.h>
#include<DARE_Engine/sprite.h>
#include<DARE_Engine/GLSLProgram.h>
#include<DARE_Engine/OpenGLTexture.h>
#include<DARE_Engine/Window.h>
#include<DARE_Engine/errors.h>
#include<vector>

using namespace DARE_Engine;

enum class gamestate {PLAY,STOP};

class game
{
public:

	void run(); 

	void process_input();

	void drawGame();

	void initsystems();

	void initShaders();

	game();

	~game();

	gamestate games;

private:

	Window _window;

	sprite _sprite;

	void fpsCounter();

	float time;

	GLSLProgram _colorProgram;
	
	OpenGLTexture _ChangeTexture;

	std::vector<sprite*> _sprites; 

	float _fps, _frameTime, _maxFPS;
};

