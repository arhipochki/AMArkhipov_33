#pragma once

#include "SDL_image.h"

#include "AbstractTarget.h"
#include "Structures.h"

/*
	Класс движущийся мишени, унаследованный от AbstractTarget

	@param speed - скорость мишени
	@param texture - ссылка на текстуру
	@param renderer - ссылка не рендерер
	@param max_attemps - максимальное количество попыток, чтобы поразить мишень
	@param max_health - максимальное здоровье мишени
*/
class MovingTarget : public AbstractTarget
{
private:
	Speed speed = { 0.0f, 0.0f };
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	const int max_attemps = 12;
	const float max_health = 40.0f;

public:

	/*
		Пустой конструктор мишени
	*/
	MovingTarget();

	/*
		Конструктор копирования

		@param target - ссылка на движущуюся мишень, которую надо скопировать
	*/
	MovingTarget(const MovingTarget& target);

	/*
		Перегруженный конструктор

		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру 
		@param id - номер мишени
	*/
	MovingTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id);

	/*
		Перегруженный конструктор с указанием места появления и её скоростью

		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру
		@param id - номер мишени
		@param px - координата по x
		@param py - координата по y
		@param speed - скорость мишени
	*/
	MovingTarget(SDL_Renderer* renderer, SDL_Texture* texture, int id, float px, float py, Speed speed);

	/*
		Деструктор движущийся мишени
	*/
	~MovingTarget();

	// Перепопределённая функция движения мишени
	void move() override;

	// Перепопределённая функция отрисовки
	void draw() override;

	// Перепопределённая функция уничтожения мишени
	void destroy() override;

	
	/*
		Перепопределённая функция проверки коллизии

		@param target - ссылка на мишень, с которой надо сравнить
	*/
	void checkCollision(AbstractTarget* a_target) override;

	// Переопределённый вывод статистики
	void printStatistics() override;

	/*
		Метод проверки пересечения с мишенью

		@param target - ссылка на мишень, с которой надо сравнить\
		@return true - если пересеклись, иначе false
	*/

	bool checkDistance(AbstractTarget* a_target);
};

