#pragma once
#include <glm/glm.hpp>
#include <Bengine/SpriteBatch.h>
#include <Bengine/ResManager.h>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();
	
	void init(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	void draw(Bengine::SpriteBatch& spriteBatch);
	//Returns true when we are out of life.
	bool update();

private:
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	Bengine::GLTexture _texture;
};

