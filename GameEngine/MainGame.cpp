#include <iostream>
#include <Bengine/Bengine.h>
#include <Bengine/Errors.h>
#include <Bengine/GLTexture.h>
#include <Bengine/ResManager.h>
#include "MainGame.h"


//#include "ImageToTexture.h"
using namespace std;


MainGame::MainGame(int w, int h) : 
	_windowWidth(w),
	_windowHeight(h),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_colorProgram = new Bengine::GLSLProgram();
	_camera.init(_windowWidth, _windowHeight);
}
MainGame::~MainGame()
{
	delete _colorProgram;
	//delete _sprite;
	//delete _playerTexture;
}
void MainGame::run()
{
	initSystems();

	gameLoop();
}
void MainGame::initSystems()
{
	initSDLWindowOpenGL();
	//call this after you've initialized opengl which we do up here.
	_colorProgram->initShaderProgram();
	//_sprite->initSprite(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJump_pack/PNG/CharacterLeft_Jump.png");
	//ImageToTexture::genTextureFromPNG("Textures/JimmyJump_pack/PNG/CharacterLeft_Jump.png", _playerTexture);
	//initSprites(2);

	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initSDLWindowOpenGL()
{
	Bengine::init();
	
	_window.create("Game Engine", _windowWidth, _windowHeight, Bengine::FULLSCREEN);
} 


void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_fpsLimiter.begin();
		//float startTicks = SDL_GetTicks();
		processInput();
		//It says 100fps, and most monitors have a refresh rate of 60Hz,
		//if the number higher than that will waste GPU and CPU resources.
		_time += 0.01f;

		_camera.update();

		//Update all bullets.
		for (int i = 0; i < _bullets.size(); /* ++i */)
		{
			if (_bullets[i].update() == true)
			{
				//A good way to remove elements from a vector when you don't care about order.
				//the back elements is never going to get updated, that's not what we want.
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				//So we're going to increment i if we didn't delete a bullet.
				i++;
			}
		}

		
		drawGame(); 
		//calculateFPS();

		_fps = _fpsLimiter.end();

		//print only once every 10 frames.
		static int frameCounter = 0;
		//frameCounter++;
		//It's not efficient
		/*if (++frameCounter % 10 == 0)
		{
			cout << _fps << endl;
		}*/
		if (++frameCounter == 10000) {
			cout << _fps << endl;
			frameCounter = 0;
		}
		

		//if our current frame time is actually eight meaning we process 
		//twice as fast as we thought we would.What we're going to do is
		//delay for an additional eight milliseconds.
		/*This may not always work,on some window platforms,you can't delay
		for less than 16 milliseconds if you try to delay for 8 milliseconds
		or one millisecond,it'll probably end up delaying for 16 ms and that depends on a lot of things.
		If you're not getting a 60 FPS then it could be because of the actual time slice,the OS is giving
		you for SDL delay
		*/
		//float frameTicks = SDL_GetTicks() - startTicks;
		//const float minFrameTime = 1000.f / _maxFPS;
		////Limit the FPS to the max FPS.
		//if (minFrameTime > frameTicks)
		//{
		//	SDL_Delay(minFrameTime - frameTicks);
		//}
	}
}

void MainGame::processInput()
{
	//ask your OS what events do we need to process,
	//what has the user been typing in or moving his mouse around on you known
	//what has been doing
	//get those events and then process them
	SDL_Event e;
	while (SDL_PollEvent(&e) == 1)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << " " << e.motion.y << std::endl;
			_inputManager.setMouseCoords(e.motion.x, e.motion.y);
		
		case SDL_KEYDOWN:
			_inputManager.pressKey(e.key.keysym.sym);
			/*
			*If we use this way, it can't respond to two keys at once, and it moves a little bit jerky.
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -_camera.getMoveSpeed()));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, _camera.getMoveSpeed()));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(_camera.getMoveSpeed(), 0.0));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-_camera.getMoveSpeed(), 0.0));
				break;
			default:
				break;
			}*/
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(e.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(e.button.button);
			break;
		default:
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -_camera.getMoveSpeed()));
	}	
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, _camera.getMoveSpeed()));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(_camera.getMoveSpeed(), 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{ 
		_camera.setPosition(_camera.getPosition() + glm::vec2(-_camera.getMoveSpeed(), 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + _camera.getScaleSpeed());
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - _camera.getScaleSpeed());
	}
	
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertWindowToWorld(mouseCoords);
		//std::cout << mouseCoords.x  << " " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 2.0f, 100);
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	//清除颜色缓冲，用设置的颜色填充整个区域---执行
	//同时清除深度缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram->useProgram();
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _playerTexture->id);
	GLint textureLocation = _colorProgram->getUniformLocation("mySampler");
	//将0号纹理传到GPU对应的位置---设置Uniform变量的值
	glUniform1i(textureLocation, 0);

	//Set the constantly changing time variable
	//GLint timeLocation = _colorProgram->getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint pLocation = _colorProgram->getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture texture = Bengine::ResManager::getTexture("Textures/JimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bengine::Color color;
	color.setColor(255, 255, 255, 255);

	/*
	If you draw in the same place more than once, 
	there will be a dark shadow on the outside of the image
	I'll figure that out later!!!
	It seems that the outer layer of the image itself has a layer of shadow, 
	and multiple draws will increase the shadow effect.
	*/
	/*for (int i = 0; i < 10; ++i)
	{*/
	_spriteBatch.setDraw(pos, uv, texture.id, 0.0f, color);
		//_spriteBatch.setDraw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	//}

	for (int i = 0; i < _bullets.size(); ++i)
	{
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//disable the shader
	_colorProgram->unuseProgram();

	//Swap our buffer and draw everything to the screen
	_window.swapBuffer();
}

//void MainGame::calculateFPS()
//{
//	static const int NUM_SAMPLERS = 10;
//	static float frameTimes[NUM_SAMPLERS];
//	static int currentFrame = 0;
//
//	static float prevTicks = SDL_GetTicks();
//	float currentTicks;
//	currentTicks = SDL_GetTicks();
//	_frameTime = currentTicks - prevTicks;
//	frameTimes[currentFrame % NUM_SAMPLERS] = _frameTime;
//
//	prevTicks = currentTicks;
//
//	int count;
//	//It has to be here, otherwise count is going to be 0 the first time
//	currentFrame++;
//	if (currentFrame < NUM_SAMPLERS)
//	{
//		count = currentFrame;
//	}
//	else
//	{
//		count = NUM_SAMPLERS;
//	}
//
//	float frameTimeAverage = 0;
//	for (int i = 0; i < count; ++i)
//	{
//		frameTimeAverage += frameTimes[i];
//	}
//	frameTimeAverage /= count;
//	
//	if (frameTimeAverage > 0)
//	{
//		_fps = 1000.0f / frameTimeAverage;
//	}
//	else
//	{
//		_fps = 60.0f;
//	}
//	
//}