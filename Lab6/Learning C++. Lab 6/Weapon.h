#pragma once

#include <string>
#include <vector>

#include "Bullet.h"
#include "Defines.h"
#include "SDL.h"

/*
	Класс оружия

	@param renderer - указатель на рендерер
	@param texture - указатель на текстуру
	@param bullet_texture - указатель на текстуру пули
	@param bullets - массив пуль
	@param max_bullets_count - максимальное количество пуль
	@param bullets_count - текущее количество пуль
	@param one_shot_count - количество пуль за нажатие одиночной атаки
	@param burst_shot_count - количество пуль за нажатие атаки очередями
	@param width - ширина персонажа
	@param height - высота персонажа
	@param bullet_damage - урон от пули
	@param px - позиция персонажа по x
	@param py - позиция персонажа по y
	@param bullet_speed - скорость пули
*/
class Weapon
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* bullet_texture = nullptr;

public:
	std::vector<Bullet*> bullets;

	int max_bullets_count = 10;
	int bullets_count = max_bullets_count;
	int one_shot_count = 1;
	int burst_shot_count = 3;

	float width = 60.0f;
	float height = 150.0f;
	float bullet_damage = 4.0f;

	float px = 100.0f;
	float py = HEIGHT - height;

	Speed bullet_speed = { 5.0f, 5.0f };

	/*
		Пустой конструктор
	*/
	Weapon();

	/*
		Основной конструктор

		@param renderer - указатель на рендерер
		@param texture - указатель на текстуру
		@param bullet_texture - указатель на текстуру пули
	*/
	Weapon(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* bullet_texture);

	/*
		Перегруженный основной конструктор

		@param renderer - указатель на рендерер
		@param texture - указатель на текстуру
		@param bullet_texture - указатель на текстуру пули
		@param damage - новый урон от пули
		@param max_bulltes_count - новое количество боезапаса
		@param bullet_speed - новая скорость пули
	*/
	Weapon(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* bullet_texture, float damage, int max_bullets_count, Speed bullet_speed);

	/*
		Деструктор
	*/
	~Weapon();

	/*
		Метод стрельбы

		@param buttons - нажатые кнопки
		@param mouse_x - координата мышки по x
		@param mouse_y - координата мышки по y
	*/
	void shoot(Uint32 buttons, float mouse_x, float mouse_y);

	/*
		Метод отрисовки
	*/
	void draw();

	/*
		Метод перезарядки оружия
	*/
	void reload();
};