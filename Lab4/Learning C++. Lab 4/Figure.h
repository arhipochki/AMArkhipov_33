#pragma once

#include <string>
#include <vector>

#include "Circle.h"
#include "Rectangle.h"
#include "Hexagon.h"

/*
	Класс фигуры.

	@param type - тип фигуры
	@param shape - указатель на фигуру
*/
class Figure
{
private:
	std::vector<std::string> types = { "circle" , "rectangle", "hexagon"};
public:
	std::string type;
	void* shape = nullptr;

	/*
	*	Конструкток фигуры, все параметры задаются случайным образом.
	*/
	Figure();

	/*
		Конструктор копирования.
		@param figure - ссылка на фигуру, которую будем копировать.
	*/
	Figure(const Figure& figure);

	/*
		Метод проверки позиции.
		@param _figure - указатель на фигуру, с которой надо сравнить.
		@return result - true, если пересеклись, иначе - false.
	*/
	bool checkPosition(Figure* _figure);

	/*
		Метод площади окружности.
		@return Площадь текущей фигуры.
	*/
	double square();

	/*
		Метод проверки коллизии.
		@param _figure - указатель на фигуру, с которой надо сравнить.
	*/
	void checkCollision(Figure* _figure);

	/*
		Метод отрисовки фигуры.
		@param renderer - указатель на рендерер экрана, где будет отрисована окружность.
	*/
	void drawFigure(SDL_Renderer* renderer);

	/*
		Метод вывод информации о фигуре.
	*/
	void printInfo();

	/*
		Метод присваивания ID фигуре.
	*/
	void setId(int id);
};