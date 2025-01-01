#pragma once

#include <iostream>

#include "SDL.h"

#include "AbstractTarget.h"

/*
	Класс обычной мишени, унаследованный от AbstractTarget

	@param is_shine - уникальное поле, является ли мишень засвечивающейся (влияет на рассчёты шанса попадания)
	@param texture - ссылка на текстуру
	@param renderer - ссылка не рендерер
	@param max_attemps - максимальное количество попыток, чтобы поразить мишень
	@param max_health - максимальное здоровье мишени
*/
class ShineTarget : public AbstractTarget
{
private:
	bool is_shine = true;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	const int max_attemps = 5;
	const float max_health = 25.0f;

public:
	// Пустой конструктор
	ShineTarget();

	/*
		Конструктор копирования

		@param target - ссылка на мишень, которую требуется скопировать.
	*/
	ShineTarget(const ShineTarget& target);

	/*
		Базовый конструктор

		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру
		@param id - номер мишени
	*/
	ShineTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id);

	// Деструктор мишени
	~ShineTarget();

	// Перепопределённая функция движения мишени
	void move() override;

	// Перепопределённая функция уничтожения мишени
	void destroy() override;

	/*
		Перепопределённая функция проверки коллизии

		@param target - ссылка на мишень, с которой надо сравнить
	*/
	void checkCollision(AbstractTarget* a_target) override;
	
	// Перепопределённая функция отрисовки
	void draw() override;

	// Переопределённый вывод статистики
	void printStatistics() override;
};