#include "game.h"

#include<iostream>
#include<string>
#include<DARE_Engine/errors.h">



using namespace std;


game::game() : _window(nullptr),
				games(gamestate::PLAY),
				time(0.0f),
				_maxFPS(60.0f)
{

}

void game::run()
{
	getResolution();
	initsystems();
	_sprites.push_back(new sprite());//Adds a new Sprite at the end of the vector.Pop back deletes the last element and insert can insert an element at any position
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");//back()->Init is the same as (back()*).init. Initializes the new sprite.back() returns the address of the last element.
	_sprites.push_back(new sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");


	//_playerTexture = ImageLoader::loadPNG("Textures/JimmyJump/PNG/CharacterRight_Standing.png"); // Loads the PNG file into picopng for decoding into raw pixel data
	//_ChangeTexture = ImageLoader::loadPNG("changeTexture.png");

	while (games != gamestate::STOP)
	{
		float startTick = SDL_GetTicks();
		process_input();
		time += 0.01f; //Adds to the time variable every frame
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

	while (SDL_PollEvent(&evnt)) //Checks for any pending events that must be processed. Returns 1 if there is an event pending or 0 for none
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
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_OPENGL);//Creates an SDL window
	if (_window == nullptr)
	{
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window); //Creates an OpenGL context in the created SDL window
	if (glContext == nullptr)
	{
		fatalError("SDL_GL Context could not be created");
	}

	GLenum error = glewInit(); //Initialises GLEW and checks for error at the same time. 
	if (error != GLEW_OK)
	{
		fatalError("Could not Initialize GLEW");
	}
	
	cout << "OPENGL VERSION : " << glGetString(GL_VERSION);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//Sets the Attribute and its value. Here Double Buffer is set to 1.

	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//Sets the Color of the OpenGL context to the specified values. In this case the color is black.

	SDL_GL_SetSwapInterval(1);


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
	

	

	
	SDL_GL_SwapWindow(_window);//Swaps between the two buffers in the DoubleBuffer window
	
	
}

void game::initShaders()
{
	//TODO: ADD COMMENTS FOR THIS FUNCTION
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

void game::getResolution()
{
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
}



game::~game()
{
}
