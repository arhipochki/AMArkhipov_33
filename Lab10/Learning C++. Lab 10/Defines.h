#pragma once

#include <map>

#include "Logger.h"

// Размер поля NxN
const int N				= 8;

// Высота экрана
const int WIDTH			= 1920;

// Ширина экрана
const int HEIGHT		= 1080;

// Размер тайла
const int TILE_SIZE		= 198 * HEIGHT / WIDTH;

// Погрешность поля (поля слева и снизу)
const int BOARD_ERR		= 35;

// Ширина поля
const int FIELD_WIDTH	= 500 * WIDTH / HEIGHT;

// Высота поля
const int FIELD_HEIGHT	= 500 * WIDTH / HEIGHT;

// Координата поля по x
const int FIELD_X		= WIDTH * 0.5;

// Координата поля по Y
const int FIELD_Y		= HEIGHT * 0.05;

// Координата x для отрисовки имени игроков
const int PLAYER_LABEL_X		= FIELD_X - 2 * TILE_SIZE;

// Координата y для отрисовки первого игрока
const int FIRST_PLAYER_LABEL_Y  = FIELD_Y;

// Координата y для отрисовки второго игрока
const int SECOND_PLAYER_LABEL_Y = FIELD_Y + FIELD_HEIGHT - TILE_SIZE;

// Словарь букв поля
const std::map<int, char> FIELD_LETTERS = {
	{0, 'a'}, {1, 'b'},
	{2, 'c'}, {3, 'd'},
	{4, 'e'}, {5, 'f'},
	{6, 'g'}, {7, 'h'}
};