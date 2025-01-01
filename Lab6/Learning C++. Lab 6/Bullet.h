#pragma once

#include "Structures.h"

/*
	Класс пули.
	@param px - центр по x.
	@param py - центр по y.
	@param width - ширина текстуры пули.
	@param height - высота текстуры пули.
	@param speed - скорость пули.
	@param destroyed - уничтожена ли пуля.
	@param renderer - ссылка на рендер.
	@param texture - ссылка на текстуру.
*/
class Bullet
{
private:
	float px = 0.0f;
	float py = 0.0f;
	float width = 15.0f;
	float height = 15.0f;
	float damage = 4.0f;
	Speed speed = { 5.0f, 5.0f };
	bool destroyed = false;

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
public:
	
	/*
		Базовый пустой конструктор
	*/
	Bullet();

	/*
		Перегруженный конструктор с указанием позиций начала пули, куда лететь, где и что отрисовывать

		@param px - координата по x
		@param py - координата по y
		@param mouse_x - координата мыши по x
		@param mouse_y - координата мыши по y
		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру пули
	*/
	Bullet(float px, float py, float mouse_x, float mouse_y, SDL_Renderer* renderer, SDL_Texture* texture);

	/*
		Перегруженный конструктор с указанием позиций начала пули, 
		куда лететь, новым уроном, новой скоростью, где и что отрисовывать

		@param px - координата по x
		@param py - координата по y
		@param mouse_x - координата мыши по x
		@param mouse_y - координата мыши по y
		@param damage - новый урон от пули
		@param speed - новая скорость пули
		@param renderer - ссылка на рендерер
		@param texture - ссылка на текстуру пули
	*/
	Bullet(float px, float py, float mouse_x, float mouse_y, float damage, Speed speed, SDL_Renderer* renderer, SDL_Texture* texture);

	/*
		Деструктор пули
	*/
	~Bullet();

	/*
		Метод, возвращающий состание пули
		@return destroyed - уничтожена ли пуля
	*/
	bool isDestroyed();

	/*
		Метод, проверябщий расстояние пули и мишени

		@param a_target - ссылка на мишень
		@return true - если пересеклись, иначе false
	*/
	bool checkDistance(AbstractTarget* a_target);

	/*
		Метод проверка коллизии и взаимодействие с мишенью
		@param a_target - ссылка на мишень
	*/
	void checkCollision(AbstractTarget* a_target);

	// Метод, проверяющий соударение со стенкой экрана
	void checkWall();

	// Метод передвижения пули
	void move();

	// Метод отрисовки пули
	void draw();
};
