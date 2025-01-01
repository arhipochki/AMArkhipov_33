#pragma once

#include "Figure.h"

/**
 * @brief Класс коня, унаследованный от фигуры
 * 
 */
class Knight : public Figure
{
public:

	// Пустой конструктор
	Knight() {}

	/**
	 * @brief Основной конструктор
	 * 
	 * @param renderer - указатель на рендерер
	 * @param texture - указатель на текстуру
	 * @param x - координата фигуры x по карте
	 * @param y - координата фигуры y по карте
	 * @param size - размер текстуры фигуры
	 * @param type - тип фигуры
	 * @param team - команда фигуры
	 */
	Knight(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int size, ChessType type, ChessTeam team)
		: Figure(renderer, texture, x, y, size, type, team)
	{

	}

	// Переопределённые методы
	void canAttack(char(*chess_map)[N], Figure* figure) override;

	void checkAllPossibleWays(char(*chess_map)[N]) override;
};

