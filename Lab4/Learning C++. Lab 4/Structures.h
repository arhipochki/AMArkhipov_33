#pragma once

/*
	Структура цвета (0 - 255)

	@param r - красный
	@param g - зелёный
	@param b - синий
	@param a - красный
*/
struct RGB {
	int r;
	int g;
	int b;
	int a;
};

/*
	Структура цвета каждое значение принимает (0 - 255)

	@param x - горизонтальная скорость
	@param y - вертикальная скорость
*/
struct Speed {
	float x;
	float y;
};