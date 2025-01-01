#include "Figure.h"

Figure::Figure()
{
	type = types[rand() % types.size()];

	if (type == "circle")
		shape = new Circle();
	else if (type == "rectangle")
		shape = new Rectangle();
	else if (type == "hexagon")
		shape = new Hexagon();
}

Figure::Figure(const Figure& figure)
{
	this->type = figure.type;
	this->shape = figure.shape;
}

Figure::~Figure()
{
	delete shape;
}

// Сравниваем всегда по описанной окружности
bool Figure::checkPosition(Figure* figure)
{
	return ((Circle*)this->shape)->checkPosition((Circle*)figure->shape);
}

double Figure::square()
{
	if (this->type == "circle")
		return ((Circle*)this->shape)->square();
	else if (type == "rectangle")
		return ((Rectangle*)this->shape)->square();
	else if (type == "hexagon")
		return ((Hexagon*)this->shape)->square();
}

// Проверяем всегда по описанной окружности
void Figure::checkCollision(Figure* figure)
{
	((Circle*)this->shape)->checkCollision((Circle*)figure->shape);
}

void Figure::drawFigure(SDL_Renderer* renderer)
{
	if (this->type == "circle")
		((Circle*)this->shape)->drawFigure(renderer);
	else if (type == "rectangle")
		((Rectangle*)this->shape)->drawFigure(renderer);
	else if (type == "hexagon")
		((Hexagon*)this->shape)->drawFigure(renderer);
}

void Figure::printInfo()
{
	// ((Circle*)this->shape)->printInfo();		// Привет, полиморфизм

	if (this->type == "circle")
		((Circle*)this->shape)->printInfo();
	else if (type == "rectangle")
		((Rectangle*)this->shape)->printInfo();
	else if (type == "hexagon")
		((Hexagon*)this->shape)->printInfo();
}

void Figure::setId(int id)
{
	((Circle*)this->shape)->setId(id);
}