#include "Rectangle.h"

Rectangle::Rectangle()
{
	this->width = rand() % (WIDTH / 16) + 1;
	this->height = rand() % (HEIGHT / 16) + 1;

	this->radius = sqrt(this->width * this->width + this->height * this->height) / 2;

	this->px = rand() % (WIDTH - this->radius) + this->radius;
	this->py = rand() % (HEIGHT - this->radius) + this->radius;

	this->speed = Speed{ ((0.01f * (-WIDTH / (4 * radius))) + 0.01f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX),
				   ((0.01f * (-WIDTH / (4 * radius))) + 0.01f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX) };

	this->circle_color = RGB{ 0xFF, 0x00, 0x00, 0xFF };

	this->rectangle_color = RGB{ rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color,
		rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color };
}

Rectangle::Rectangle(const Rectangle& rectangle)
{
	this->id = rectangle.id;
	this->width = rectangle.width;
	this->height = rectangle.height;
	this->radius = rectangle.radius;
	this->px = rectangle.px;
	this->py = rectangle.py;
	this->speed = rectangle.speed;
	this->circle_color = rectangle.circle_color;
	this->rectangle_color = rectangle.rectangle_color;
}

void Rectangle::drawFigure(SDL_Renderer* renderer)
{
#if DRAW_CIRCLES_ON_FIGURES == 1
	Circle::drawFigure(renderer);
#endif

	SDL_Rect rect;

	rect.x = this->px - this->width / 2;
	rect.y = this->py - this->height / 2;
	rect.w = this->width;
	rect.h = this->height;

	SDL_SetRenderDrawColor(renderer, this->rectangle_color.r, this->rectangle_color.g,
		this->rectangle_color.b, this->rectangle_color.a);

	SDL_RenderDrawRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

double Rectangle::square()
{
	return this->width * this->height;
}

void Rectangle::printInfo()
{
	std::cout << "ID: " << this->id << "\n";
	std::cout << "TYPE: RECTANGLE\n";
	std::cout << "RADIUS: " << this->radius << "\n";
	std::cout << "SQUARE: " << this->square() << "\n";
	std::cout << "WIDTH: " << this->width << " HEIGHT: " << this->height << "\n";
	std::cout << "CIRCLE COLOR: rgba(" << this->circle_color.r << ", " << this->circle_color.g << ", "
		<< this->circle_color.b << ", " << this->circle_color.a << ")\n";
	std::cout << "RECTANGLE COLOR: rgba(" << this->rectangle_color.r << ", " << this->rectangle_color.g << ", "
		<< this->rectangle_color.b << ", " << this->rectangle_color.a << ")\n";
	std::cout << "PX: " << this->px << " PY: " << this->py << "\n";
	std::cout << "SPEED X: " << this->speed.x << " SPEED Y: " << this->speed.y << "\n\n";
}