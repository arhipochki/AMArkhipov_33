#include "Hexagon.h"

Hexagon::Hexagon()
{
	Circle();

	this->circle_color = RGB{ 0xFF, 0x00, 0x00, 0xFF };

	this->hexagon_color = RGB{ rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color,
	rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color };
}

Hexagon::Hexagon(const Hexagon& hexagon)
{
	this->id = hexagon.id;
	this->px = hexagon.px;
	this->py = hexagon.py;
	this->radius = hexagon.radius;
	this->circle_color = hexagon.circle_color;
	this->hexagon_color = hexagon.hexagon_color;
	this->speed = hexagon.speed;
}

double Hexagon::square()
{
	return 1.5 * 1.73 * pow(this->radius, 2); // S = 3*sqrt(3) / 2 * R^2
}

void Hexagon::drawFigure(SDL_Renderer* renderer)
{
#if DRAW_CIRCLES_ON_FIGURES == 1
	Circle::drawFigure(renderer);
#endif

	SDL_SetRenderDrawColor(renderer, this->hexagon_color.r, this->hexagon_color.g,
		this->hexagon_color.b, this->hexagon_color.a);

	int sides = 6;
	float angle = 0.0f;
	float incr = 2.0 * PI / sides;

	int tX = this->radius * cos(angle) + this->px;
	int tY = this->radius * sin(angle) + this->py;

	for (int i = 0; i < sides; i++)
	{
		int oX = tX;
		int oY = tY;
		angle += incr;
		tX = this->radius * cos(angle) + this->px;
		tY = this->radius * sin(angle) + this->py;

		SDL_RenderDrawLine(renderer, oX, oY, tX, tY);
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void Hexagon::printInfo()
{
	std::cout << "ID: " << this->id << "\n";
	std::cout << "TYPE: HEXAGON\n";
	std::cout << "RADIUS: " << this->radius << "\n";
	std::cout << "SQUARE: " << this->square() << "\n";
	std::cout << "COLOR: rgba(" << this->hexagon_color.r << ", " << this->hexagon_color.g << ", "
		<< this->hexagon_color.b << ", " << this->hexagon_color.a << ")\n";
	std::cout << "CIRCLE COLOR: rgba(" << this->circle_color.r << ", " << this->circle_color.g << ", "
		<< this->circle_color.b << ", " << this->circle_color.a << ")\n";
	std::cout << "PX: " << this->px << " PY: " << this->py << "\n";
	std::cout << "SPEED X: " << this->speed.x << " SPEED Y: " << this->speed.y << "\n\n";
}