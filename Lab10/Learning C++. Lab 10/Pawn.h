#pragma once

#include "Figure.h"

/**
 * @brief Класс пешки, унаследованный от класса фигур
 * @param way - направление, в котором нужно двигаться пешке
 */
class Pawn : public Figure
{
private:
	int way = 1;
public:
	// Пустой конструктор
	Pawn() {}

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
	 * @param way - направление пешки
	 */
	Pawn(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int size, ChessType type, ChessTeam team, int way)
		: Figure(renderer, texture, x, y, size, type, team)
	{
		this->way = way;
	}

	// Переопределённые методы
	void canAttack(char(*chess_map)[N], Figure* figure) override;
	void checkAllPossibleWays(char(*chess_map)[N]) override;
};