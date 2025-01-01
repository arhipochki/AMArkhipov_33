#include "Mouse.h"

#include "Functions.h"

Mouse::Mouse(SDL_Renderer* renderer, SDL_Texture* texture)
	: renderer(renderer), texture(texture)
{
	rect.w = 20;
	rect.h = 20;
	point.w = 1;
	point.h = 1;

	SDL_ShowCursor(false);
}

Mouse::~Mouse()
{
	renderer = nullptr;
	texture = nullptr;
}

void Mouse::update()
{
	SDL_GetMouseState(&rect.x, &rect.y);
	point.x = rect.x;
	point.y = rect.y;
}

void Mouse::draw()
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
