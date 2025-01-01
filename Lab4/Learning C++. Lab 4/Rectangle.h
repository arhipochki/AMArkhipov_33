#pragma once

#include "Circle.h"

/*
	Класс прямоугольника. Наследуется от класса окружности (circle)

	@param width - ширина прямоугольника
	@param - heught - высота прямоугольника
	@param rectangle_color - цвет прямоугольника
*/
class Rectangle : public Circle
{
public:
	int width = 0;
	int height = 0;

	RGB rectangle_color = RGB {0, 0, 0, 0};

	/*
		Конструктор прямоугольника. Все параметры задаются случайно
	*/
	Rectangle();

	/*
		Конструктор копирования
	*/
	Rectangle(const Rectangle& rectangle);

	/*
		Метод, считающий площадь прямоугольника
		@return result - посчитанная площадь
	*/
	double square() override;

	/*
		Метод отрисовки прямоугольника
		@param renderer - ссылка на рендерер окна, где будет отрисован прямоугольник
	*/
	void drawFigure(SDL_Renderer* renderer) override;

	/*
		Метод вывода информации о прямоугольнике
	*/
	void printInfo() override;
};