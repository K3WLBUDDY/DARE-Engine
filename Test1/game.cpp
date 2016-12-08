#include "game.h"

using namespace std;

game::game() :
games(gamestate::PLAY),
time(0.0f),
_maxFPS(60.0f)
{

}

void game::run()
{
	start = 1;
	initsystems();

	/*
	_sprites.push_back(new sprite());//Adds a new Sprite at the end of the vector.Pop back deletes the last element and insert can insert an element at any position
	_sprites.back()->init(0.0f, 0.0f, _window.width / 2, _window.width / 2, "Textures/DAREv0.1_logo.png");//back()->Init is the same as (back()*).init. Initializes the new sprite.back() returns the address of the last element.
	_sprites.push_back(new sprite());
	_sprites.back()->init(_window.width / 2, 0.0f, _window.width / 2, _window.width / 2, "Textures/DAREv0.1_logo.png");
	*/


	while (games != gamestate::STOP)
	{
		float startTick = SDL_GetTicks();
		process_input();
		time += 0.01f; 


		_camera.update();
		drawGame();
		fpsCounter();

		static int framecount = 0;
		framecount++;

		if (framecount == 10)
		{
			cout << "\n\t\t FPS: " << _fps << endl;
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

	float cameraSpeed = 20;
	float scaleSpeed = 0.1f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:

			games = gamestate::STOP;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			/*
			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -cameraSpeed));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, cameraSpeed));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() - glm::vec2(cameraSpeed, 0.0));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(cameraSpeed, 0.0));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + scaleSpeed);
				break;
			case SDLK_e:
				_camera.setScale(_camera.getScale() - scaleSpeed);
				break;
			}
			*/
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);

		}
		
		if (evnt.button.type == SDL_MOUSEBUTTONDOWN && evnt.button.button == SDL_BUTTON_LEFT) // Mouse Motion for translating the Sprite when the left mouse button is clicked.
		{
			while (SDL_WaitEvent(&evnt) && evnt.button.type != SDL_MOUSEBUTTONUP)
			{
				_camera.setPosition(glm::vec2((float)evnt.motion.x, (float)evnt.motion.y));
				_camera.update();
				drawGame();
			}
		}
		if (evnt.wheel.type == SDL_MOUSEWHEEL && evnt.wheel.y > 0)
		{
			_camera.setScale(_camera.getScale() + scaleSpeed);
			_camera.update();
			drawGame();
		}
		else if (evnt.wheel.type == SDL_MOUSEWHEEL && evnt.wheel.y < 0)
		{
			_camera.setScale(_camera.getScale() - scaleSpeed);
			_camera.update();
			drawGame();
		}

		
	}
	if (_inputManager.isKeyPressed(SDLK_w))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -cameraSpeed));

	if (_inputManager.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, cameraSpeed));

	if (_inputManager.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPosition() - glm::vec2(cameraSpeed, 0.0));

	if (_inputManager.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPosition() + glm::vec2(cameraSpeed, 0.0));

	if (_inputManager.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() + scaleSpeed);

	if (_inputManager.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() - scaleSpeed);
	
		
}

void game::initsystems()
{

	init();

	

	//_window.createWindow("DARE v0.1", 1366, 768, 0);

	_window.createWindow("DARE v0.1", 0);

	_camera.init(_window.width, _window.height);

	initShaders();

	_spriteBatch.init();

	
}

void game::drawGame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	
	glActiveTexture(GL_TEXTURE0); //Selects the Texture unit that will be affected

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler"); //Gets the location of the Texture Variable present in the Shader
	glUniform1i(textureLocation,0);
	GLuint timeLocation = _colorProgram.getUniformLocation("time"); //Gets the Location of the Time Variable 
	glUniform1f(timeLocation, time); //Sends the  Value of the Variable to the GPU so that it can be used by the GPU whereever the variable time appears in the shaders

	GLuint PLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(PLocation, 1, GL_FALSE, &(cameraMatrix[0][0])); // glUniformMatrix4fv(Location, count, Transpose Matrix (GL_TRUE, GL_FALSE), value);
	
	_spriteBatch.begin();
	
	glm::vec4 pos(0.0f, 0.0f, _window.width / 2, _window.width / 2);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	//OpenGLTexture texture = ResourceManager::getTexture("Textures/DAREv0.1_logo.png");

	OpenGLTexture texture = ResourceManager::getTexture("Textures/DAREv0.1_logo.png");

	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	
	_spriteBatch.draw(pos,uv, texture.ID, 0.0f, color);
	_spriteBatch.draw(pos+glm::vec4(_window.width/2,0,0,0), uv, texture.ID, 0.0f, color);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	/*
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	//	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/JimmyJump/PNG/CharacterRight_Standing.png");
	}
	*/


	
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
