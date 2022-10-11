#pragma once

#include "Defines.h"
#include "SDL.h"
#include "Structures.h"

#include <iostream>

/*
	Класс окружности.

	@param radius - радиус окружности.
	@param px - позиция центра по оси X.
	@param py - позиция центра по оси Y.
	@param speed - структура скорсти.
	@param color - структура цвета.
*/
class Circle
{
public:
	int id = 0;
	int radius = 0;
	float px = 0;
	float py = 0;
	Speed speed = { 0, 0 };
	RGB circle_color = { 0, 0, 0, 0 };

	/*
		Конструктор, где каждое значение будет сгенерировано.
	*/
	Circle();

	/*
		Конструктор, где каждое значение будет сгенерировано, кроме радиуса.
	*/
	Circle(int _radius);

	/*
		Конструктор, где каждое значение задано самостоятельно.
	*/
	Circle(int _radius, int _px, int _py, Speed _speed, RGB _color);

	/*
		Конструктор копирования.
		@param _circle - ссылка на окружность, которую будем копировать.
	*/
	Circle(const Circle& _circle);

	/*
		Метод проверки позиции.
		@param _circle - указатель на окружность, с которой надо сравнить.
		@return result - true - пересеклись, false - не пересеклись
	*/
	bool checkPosition(Circle* _circle);

	/*
		Метод площади окружности.
		@return Площадь текущей окружности.
	*/
	virtual double square();

	/*
		Метод расчёта дистанции между двумя окружностями.
		@param _circle - указатель на окружность, с которой надо сравнить.
		@return dist - расстояние между окружностями.
	*/
	float distance(const Circle* _circle);

	/*
		Метод проверки коллизии.
		@param _circle - указатель на окружность, с которой надо сравнить.
	*/
	void checkCollision(Circle* _circle);

	/*
		Метод отрисовки фигуры.
		@param renderer - указатель на рендерер экрана, где будет отрисована окружность.
	*/
	virtual void drawFigure(SDL_Renderer* renderer);

	/*
		Метод вывод информации о шаре.
	*/
	virtual void printInfo();

	/*
		Метод присваивания ID шару.
	*/
	void setId(int id);
protected:
	const double PI = 3.14f;
	const double density = 0.01f;
	const double mass = PI * radius * radius * density;
	const int min_color = 100;
};