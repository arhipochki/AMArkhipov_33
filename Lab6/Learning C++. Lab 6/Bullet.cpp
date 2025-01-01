#include "Bullet.h"

#include "Defines.h"

Bullet::Bullet() { }

Bullet::Bullet(float px, float py, float mouse_x, float mouse_y, SDL_Renderer* renderer, SDL_Texture* texture)
	: px(px), py(py), renderer(renderer), texture(texture)
{
	float dist = sqrtf(powf(this->px - mouse_x, 2) + powf(this->py - mouse_y, 2));
	
	float sin = -1 * (this->px - mouse_x) / dist;
	float cos = -1 * (this->py - mouse_y) / dist;

	speed.vx *= sin;
	speed.vy *= cos;
}

Bullet::Bullet(float px, float py, float mouse_x, float mouse_y, float damage, Speed speed, SDL_Renderer* renderer, SDL_Texture* texture)
	: px(px), py(py), damage(damage), speed(speed), renderer(renderer), texture(texture)
{
	float dist = sqrtf(powf(this->px - mouse_x, 2) + powf(this->py - mouse_y, 2));

	float sin = -1 * (this->px - mouse_x) / dist;
	float cos = -1 * (this->py - mouse_y) / dist;

	this->speed.vx *= sin;
	this->speed.vy *= cos;
}

Bullet::~Bullet()
{
	texture = nullptr;
	renderer = nullptr;
}

bool Bullet::isDestroyed()
{
	return destroyed;
}

bool Bullet::checkDistance(AbstractTarget* a_target)
{
	float leftA = px, leftB = a_target->px;
	float rightA = px + width, rightB = a_target->px + a_target->width;
	float topA = py, topB = a_target->py;
	float bottomA = py + height, bottomB = a_target->py + a_target->height;

	if (bottomA <= topB
		|| topA >= bottomB
		|| rightA <= leftB
		|| leftA >= rightB)
		return false;

	return true;
}

void Bullet::checkWall()
{
	if (!destroyed)
	{
		if (px > WIDTH
			|| px < 0
			|| py > HEIGHT
			|| py < 0)
			destroyed = true;
	}
}

void Bullet::checkCollision(AbstractTarget* a_target)
{
	if (!destroyed && checkDistance(a_target) && a_target->isShown())
	{
		a_target->attemps--;
		if (!a_target->isMissed())
		{
			destroyed = true;
			a_target->takeDamage(damage);
		}
		else if (a_target->attemps <= 0)
		{
			destroyed = true;
			a_target->destroyed = true;
		}
		else
		{
			std::cout << "MISSED!\n";
			destroyed = true;
		}
	}
}

void Bullet::move()
{
	checkWall(); 
	px += speed.vx;
	py += speed.vy;
}

void Bullet::draw()
{ 
	renderTexture(renderer, texture, px, py, width, height);
}