#pragma once
#include<SDL/SDL.h>
#include<GL/glew.h>
#include<DARE_Engine/sprite.h>
#include<DARE_Engine/GLSLProgram.h>
#include<DARE_Engine/OpenGLTexture.h>
#include<DARE_Engine/Window.h>
#include<DARE_Engine/errors.h>
#include<DARE_Engine/Camera2D.h>
#include<DARE_Engine/InputManager.h>
#include<DARE_Engine/SpriteBatch.h>
#include<glm/gtx/string_cast.hpp>
#include<vector>
#include<DARE_Engine/DARE_Engine.h>
#include<iostream>
#include<string>

using namespace DARE_Engine;

enum class gamestate {PLAY,STOP};

class game
{
public:
	
	gamestate games;

	int start;

	void run(); 

	void process_input();

	void drawGame();

	void initsystems();

	void initShaders();

	game();

	~game();

	

private:

	Window _window;

	InputManager _inputManager;

	sprite _sprite;

	SpriteBatch _spriteBatch;

	GLSLProgram _colorProgram;
	
	OpenGLTexture _ChangeTexture;

	Camera2D _camera;

	float _fps, _frameTime, _maxFPS;

	void fpsCounter();

	float time;
};

