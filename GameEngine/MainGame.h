#pragma once
#include <glad/glad.h>
#include <SDL/SDL.h>
#include <vector>
#include <Bengine/Sprite.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/Window.h>
#include <Bengine/Camera2D.h>
#include <Bengine/SpriteBatch.h>
#include <Bengine/InputManager.h>
#include <Bengine/Timing.h>
#include "Bullet.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame(int w, int h);
	~MainGame();
	void run();
	
private:
	void initSystems();
	void initSDLWindowOpenGL();
	//void initSprites(int num);
	void gameLoop();
	void processInput();
	void drawGame();
	//void calculateFPS();

	Bengine::Window _window;
	Bengine::GLSLProgram* _colorProgram;
	Bengine::Camera2D _camera;
	Bengine::SpriteBatch _spriteBatch;
	Bengine::InputManager _inputManager;
	Bengine::FPSLimiter _fpsLimiter;
	
	/*
	* We're not going to want a bunch of sprites and textures here
	* in the actual main game class,
	*Here is just for demonstration purposes.
	*/
	//Sprite* _sprite;
	//should be pointer,if it's Sprite,it will be an error
	//��Ϊvector������ʱ�Ὣԭ���Ķ������Ƶ��¿ռ䣬ͬʱɾ��ԭ���Ŀռ䣬������һ����ɾ��ԭ���Ŀռ䣬
	//�����Sprite����������������_vboID����ָ�򶥵����ݣ����ٿ������������
	/*
	* in Sprites.cpp
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
	*/
	//std::vector<Bengine::Sprite*> _sprites;

	//what we should be doing is storing one texture per sprite.
	//GLTexture* _playerTexture;
	/**/
	
	int _windowWidth;
	int _windowHeight;
	GameState _gameState;
	float _time;

	std::vector<Bullet> _bullets;

	float _fps;
	float _maxFPS;
	/*float _fps;
	float _frameTime;
	float _maxFPS;*/
};

