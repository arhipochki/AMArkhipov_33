#pragma once

#include "SDL.h"

/*
	Класс укзателя мыши.

	@param renderer - ссылка на рендерер
	@param texture - ссылка на текстуру курсора
	@param rect - размеры курсора в виде структуры прямоугольника
	@param point - структура прямоугольника, указывающая на конкретный x, y.
*/
class Mouse
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Rect point;

public:

	/*
		Конструктор мыши.

		@param renderer - указатель на рендерер.
		@param texture - указатель на текстуру.
	*/
	Mouse(SDL_Renderer* renderer, SDL_Texture* texture);

	// Деструктор мыши
	~Mouse();

	// Метод обновления данных у мыши.
	void update();

	// Метод отрисовки мыши.
	void draw();
};

