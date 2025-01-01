#pragma once

#include "Circle.h"

/*
	Класс шестиугольника. Наследуется от окружности (circle)
	@param - hexagon_color - цвет шестиугольника
*/
class Hexagon : public Circle
{
public:
	RGB hexagon_color = RGB{ 0, 0, 0, 0 };

	/*
		Конструктор шестиугольника. Все параметры задаются случайным образом.
	*/
	Hexagon();

	/*
		Конструктор копирования.
		@param hexagon - ссылка на шестиугольник, который будет скопирован.
	*/
	Hexagon(const Hexagon& hexagon);

	/*
		Метод подсчёта площади шестиугольника.
		@return reuslt - площадь фигуры.
	*/
	double square() override;

	/*
		Метод отрисовки шестиугольника.
		@param renderer - рендерер окна, где будет отрисована фигура.
	*/
	void drawFigure(SDL_Renderer* renderer) override;

	/*
		Метод, выводящий информацию о шестиугольнике.
	*/
	void printInfo() override;
};