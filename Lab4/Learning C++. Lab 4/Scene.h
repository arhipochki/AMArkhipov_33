#pragma once

#include "Figure.h"

/*
	Класс сцены.

	@param figures - вектор фигур
*/
class Scene
{
public:
	std::vector<Figure*> figures;

	/*
		Деструктор
	*/
	~Scene();

	/*
		Метод, считающий площадь всех фигур на сцене.
		@return total - суммарная площадь фигур на экране
	*/
	double totalSquare();
};
