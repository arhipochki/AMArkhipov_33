#include "ShineTarget.h"

#include "Defines.h"
#include "Functions.h"


ShineTarget::ShineTarget() {}

ShineTarget::ShineTarget(const ShineTarget& target)
{
	renderer = target.renderer;
	texture = target.texture;
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

ShineTarget::ShineTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id)
	: renderer(renderer), texture(texture)
{
	this->id = id;

	destroyed = false;
	is_movable = false;

	// добавить дистанцию
	chance = 1.0f * rand() / RAND_MAX + 0.15f * is_shine;

	if (chance > 0.9f)
		chance = 0.9f;

	health = max_health;
	attemps = max_attemps;

	width = 30;
	height = 100;

	px = rand() * (WIDTH / 2) / RAND_MAX + WIDTH / 2;
	py = rand() * (HEIGHT - height) / RAND_MAX + height;
}

ShineTarget::~ShineTarget()
{
	if (!destroyed) destroy();
}

void ShineTarget::move()
{
	if (px + width - 1 >= WIDTH)
		px = WIDTH - width;
	if (px <= WIDTH / 2.0f)
		px = WIDTH / 2;
	if (py + height - 1 >= HEIGHT)
		py = HEIGHT - height;
	if (py + 1 <= 0)
		py = 1;
}

void ShineTarget::destroy()
{
	texture = nullptr;

	renderer = nullptr;
}

void ShineTarget::checkCollision(AbstractTarget* a_target) {}

void ShineTarget::draw()
{
	renderTexture(renderer, texture, px, py, width, height);
}

void ShineTarget::printStatistics()
{
	std::cout << "Target type: ShineTarget\n";
	std::cout << "ID: " << id << "\n";
	std::cout << "Health: " << health << "/" << max_health << "\n";
	std::cout << "Attemps: " << attemps << "/" << max_attemps << "\n";
	std::cout << "Damage Taken: " << damage_taken << "\n";
}
