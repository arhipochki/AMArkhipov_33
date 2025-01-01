#pragma once

#include <iostream>

#include "AbstractTarget.h"
#include "SDL.h"

/*
	Класс обычной мишени, унаследованный от AbstractTarget

	@param texture - ссылка на текстуру
	@param renderer - ссылка не рендерер
	@param chance_degree - степень шанса (влияет на рассчёты шансы попадания)
	@param max_attemps - максимальное количество попыток, чтобы поразить мишень
	@param max_health - максимальное здоровье мишени
*/
class OrdinaryTarget : public AbstractTarget
{
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	float chance_degree = 0.01f * rand() / RAND_MAX - 0.05f;

	const int max_attemps = 3;
	const float max_health = 10.0f;

public:

	// Пустой конструктор
	OrdinaryTarget();

	/*
		Конструктор копирования

		@param target - обычная мишень, которую надо скопировать
	*/
	OrdinaryTarget(const OrdinaryTarget& target);

	/*
		Основной конструктор

		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру
		@param id - номер мишени
	*/
	OrdinaryTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id);

	// Деструктор
	~OrdinaryTarget();

	// Перепопределённая функция движения мишени
	void move() override;

	// Перепопределённая функция уничтожения мишени
	void destroy() override;

	/*
		Перепопределённая функция проверки коллизии

		@param target - ссылка на мишень, с которой надо сравнить
	*/
	void checkCollision(AbstractTarget* a_target) override;

	// Переопределённый вывод статистики
	void printStatistics() override;

	// Перепопределённая функция отрисовки
	void draw() override;
};

