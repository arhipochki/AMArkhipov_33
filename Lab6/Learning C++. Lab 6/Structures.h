#pragma once

#include <iostream>
#include "Functions.h"
#include "AbstractTarget.h"

/*
	Структура скорости.
	@param vx - скорость по x.
	@param vy - скорость по y.
*/
struct Speed
{
	float vx;
	float vy;

	/*
		Перегруженный оператор вычитания

		@param s - скорость, которую будем вычитать
		@return result - разность скоростей
	*/
	Speed operator-(Speed& s) { return { vx - s.vx, vy - s.vy }; };
};