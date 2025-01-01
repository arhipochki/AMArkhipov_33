#include "OrdinaryTarget.h"

#include "Functions.h"
#include "Defines.h"

OrdinaryTarget::OrdinaryTarget() {}

OrdinaryTarget::OrdinaryTarget(const OrdinaryTarget& target)
{
	renderer = target.renderer;
	texture = target.texture;
	chance_degree = target.chance_degree;
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

OrdinaryTarget::OrdinaryTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id)
	: renderer(renderer), texture(texture) 
{
	this->id = id;

	// добавить дистанцию
	chance = 1.0f * rand() / RAND_MAX + chance_degree;

	if (chance > 0.9f)
		chance = 0.9f;

	health = max_health;
	attemps = max_attemps;

	width = 50.0f;
	height = 50.0f;

	px = rand() * (WIDTH / 2) / RAND_MAX + WIDTH / 2;
	py = rand() * (HEIGHT - height) / RAND_MAX + height;
}

OrdinaryTarget::~OrdinaryTarget()
{
	if (!destroyed) destroy();
}

void OrdinaryTarget::move()
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

void OrdinaryTarget::destroy()
{
	renderer = nullptr;
	texture = nullptr;
}

void OrdinaryTarget::checkCollision(AbstractTarget* a_target) {}

void OrdinaryTarget::printStatistics()
{
	std::cout << "Target type: OrdinaryTarget\n";
	std::cout << "ID: " << id << "\n";
	std::cout << "Health: " << health << "/" << max_health << "\n";
	std::cout << "Attemps: " << attemps << "/" << max_attemps << "\n";
	std::cout << "Damage Taken: " << damage_taken << "\n";
}

void OrdinaryTarget::draw()
{
	renderTexture(renderer, texture, px, py, width, height);
}