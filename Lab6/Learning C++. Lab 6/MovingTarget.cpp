#include <iostream>
#include <cmath>

#include "Defines.h"
#include "MovingTarget.h"
#include "Functions.h"

MovingTarget::MovingTarget() {}

MovingTarget::MovingTarget(const MovingTarget& target)
{
	renderer = target.renderer;
	texture = target.texture;
	speed = target.speed;

	id = target.id;
	px = target.px;
	py = target.py;
	height = target.height;
	width = target.width;
	health = target.health;
	chance = target.chance;
	damage_taken = target.damage_taken;
	attemps = target.attemps;
	destroyed = target.destroyed;
}

MovingTarget::MovingTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id)
	: renderer(renderer), texture(texture)
{
	this->id = id;

	speed = { 0.0f, 1.0f };
	is_movable = true;
	destroyed = false;

	chance = 1.0f * rand() / RAND_MAX + 0.2f * is_movable;

	if (chance > 0.95f)
		chance = 0.95f;

	health = max_health;
	attemps = max_attemps;

	width = 50;
	height = 100;

	px = rand() * (WIDTH / 2) / RAND_MAX + WIDTH / 2;
	py = rand() * (HEIGHT - height) / RAND_MAX + height;
}

MovingTarget::MovingTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id, float px, float py, Speed speed)
	: renderer(renderer), texture(texture), speed(speed)
{
	this->id = id;
	this->px = px;
	this->py = py;

	is_movable = true;

	chance = 1.0f * rand() / RAND_MAX + 0.2f * is_movable;

	if (chance > 0.95f)
		chance = 0.95f;

	health = max_health;
	attemps = max_attemps;

	width = 30.0f;
	height = 30.0f;
}

MovingTarget::~MovingTarget()
{
	if (!destroyed) destroy();
}

void MovingTarget::move()
{
	if (px + width - 1 >= WIDTH)
	{
		speed.vx *= -1;
		px = WIDTH - width;
	}
	if (px <= WIDTH / 2.0f)
	{
		speed.vx *= -1;
		px = WIDTH / 2;
	}
	if (py + height - 1 >= HEIGHT)
	{
		speed.vy *= -1;
		py = HEIGHT - height;
	}
	if (py + 1 <= 0)
	{
		speed.vy *= -1;
		py = 1;
	}

	px += speed.vx;
	py += speed.vy;
}

void MovingTarget::draw()
{
	renderTexture(renderer, texture, px, py, width, height);
}

void MovingTarget::destroy()
{
	texture = nullptr;

	renderer = nullptr;
}

bool MovingTarget::checkDistance(AbstractTarget* a_target)
{
	float leftA = px,			 leftB = a_target->px;
	float rightA = px + width,	 rightB = a_target->px + a_target->width;
	float topA = py,			 topB = a_target->py;
	float bottomA = py + height, bottomB = a_target->py + a_target->height;

	if (bottomA <= topB
		|| topA >= bottomB
		|| rightA <= leftB
		|| leftA >= rightB)
		return false;

	return true;
}

/*
* Получаем знак от числа любого типа
* @param val - значение, от которого нужно получить знак
* @return sign - знак числа
*/
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

void MovingTarget::checkCollision(AbstractTarget* a_target)
{
	if (checkDistance(a_target) && a_target->isShown())
	{
		if (a_target->is_movable)
		{
			MovingTarget* t_target = (static_cast<MovingTarget*>(a_target));

			std::swap(speed, t_target->speed);

			if (sgn(speed.vy) == sgn(t_target->speed.vy))
				speed.vy *= -1;

			move();
			t_target->move();
		}
		else
		{
			speed.vx *= -1;
			speed.vy *= -1;
		}
	}
}

void MovingTarget::printStatistics()
{
	std::cout << "Target type: MovingTarget\n";
	std::cout << "ID: " << id << "\n";
	std::cout << "Health: " << health << "/" << max_health << "\n";
	std::cout << "Attemps: " << attemps << "/" << max_attemps << "\n";
	std::cout << "Damage Taken: " << damage_taken << "\n";
}