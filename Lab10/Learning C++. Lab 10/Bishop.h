#pragma once

#include "Figure.h"

/**
 * @brief Класс слона, унаследованный от класса фигуры
 * 
 */
class Bishop : public Figure
{
public:

	// Пустой конструктор
	Bishop() {}

	/**
	 * @brief Основной конструктор
	 * 
	 * @param renderer - указатель на рендерер
	 * @param texture - указаталь на текстуру
	 * @param x - координата по x
	 * @param y - координата по y
	 * @param size - размер текстуры
	 * @param type - тип фигуры
	 * @param team - команда фигуры
	 */
	Bishop(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int size, ChessType type, ChessTeam team)
		: Figure(renderer, texture, x, y, size, type, team)
	{	}

	/**
	 * @brief Метод возможных атак фигуры
	 * 
	 * @param chess_map - указатель на карту
	 * @param figure - атакуемая фигура
	 */
	void canAttack(char(*chess_map)[N], Figure* figure) override;

	/**
	 * @brief Проверка всех возможных ходов фигуры
	 * 
	 * @param chess_map - указатель на карту
	 */
	void checkAllPossibleWays(char(*chess_map)[N]) override;
};