#include "game.h"
#include<DARE_Engine\DARE_Engine.h>
#include<iostream>
#include<string>





using namespace std;
//using namespace DARE_Engine;

game::game() : 
				games(gamestate::PLAY),
				time(0.0f),
				_maxFPS(60.0f)
{

}

void game::run()
{
	initsystems();
	_sprites.push_back(new sprite());//Adds a new Sprite at the end of the vector.Pop back deletes the last element and insert can insert an element at any position
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");//back()->Init is the same as (back()*).init. Initializes the new sprite.back() returns the address of the last element.
	_sprites.push_back(new sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");

	while (games != gamestate::STOP)
	{
		float startTick = SDL_GetTicks();
		process_input();
		time += 0.01f; 
		drawGame();
		fpsCounter();

		static int framecount = 0;
		framecount++;

		if (framecount == 10)
		{
			cout << "\n FPS: " << _fps << endl;
			framecount = 0;
		}

		float frameTick = SDL_GetTicks() - startTick;

		if (1000.0f / _maxFPS > frameTick)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTick);
		}
	}
}

void game::process_input() 
{
	SDL_Event evnt; 

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) 
		{
		case SDL_QUIT:
			games = gamestate::STOP;
			break;
		case SDL_MOUSEMOTION:
			//cout << "\nX: " << evnt.motion.x << " Y: " << evnt.motion.y;
			break;
		}
	}
}

void game::initsystems()
{

	init();

	_window.createWindow("DARE v0.1", 0);

	initShaders();

	
}

void game::drawGame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	
	glActiveTexture(GL_TEXTURE0); //Selects the Texture unit that will be affected

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler"); //Gets the location of the Texture Variable present in the Shader
	glUniform1i(textureLocation,0);
	GLuint timeLocation = _colorProgram.getUniformLocation("time"); //Gets the Location of the Time Variable and stores it in timeLocation
	glUniform1f(timeLocation, time); //Sends the Variable to the GPU so that it can be used by the GPU whereever the variable time appears in the shaders


	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	//	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");
	}
	
	glBindTexture(GL_TEXTURE_2D, 0); //Unbinds the Texture
	_colorProgram.unuse();
	

	

	
	_window.swapBuffer();//Swaps between the two buffers in the DoubleBuffer window
	
	
}

void game::initShaders()
{
	
	_colorProgram.compileShaders("Shaders/colorShading.vert.txt", "Shaders/colorShading.frag.txt");//Calls the CompileShaders function in GLSLProgram Class
	_colorProgram.addAttribute("vertexPosition"); //Binds the vertexPosition Attribute from the Vertex Shader
	_colorProgram.addAttribute("vertexColor"); //Binds the vertexColor attribute from the Vertex Shader
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();


	
}

void game::fpsCounter()
{
	static const int num_Samples = 10;//To Average the Frame times over 10 frames.Using static since values must be retained whenever the frame is drawm.
	static float frameTimes[num_Samples];
	static int currentFrame = 0;
	
	static float previousTicks = SDL_GetTicks();
	float currentTicks;
	
	currentTicks = SDL_GetTicks(); //Gets the current ms since SDL was initialized

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame%num_Samples] = _frameTime;//Implementing Circular Buffer.

	previousTicks = currentTicks;

	int count;
	currentFrame++;

	if (currentFrame < num_Samples)
		count = currentFrame;
	else
		count = num_Samples;
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage>0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;
	

}


game::~game()
{
}
