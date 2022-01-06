#include "Bullet.h"


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) 
{
	init(pos, dir, speed, lifeTime);
}
Bullet::~Bullet()
{

}

void Bullet::init(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_position = pos;
	_direction = dir;
	_speed = speed;
	_texture = Bengine::ResManager::getTexture("Textures/JimmyJump_pack/PNG/CharacterRight_Standing.png");
}

void Bullet::draw(Bengine::SpriteBatch& spriteBatch)
{
	Bengine::Color color;
	color.setColor(255, 255, 255, 255);

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.setDraw(posAndSize, uv, _texture.id, 0.0f, color);
}

bool Bullet::update()
{
	_position += _direction * _speed;
	if (_lifeTime--)
	{
		return false;
	}
	return true;
}