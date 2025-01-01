#pragma once

#include <string>
#include <vector>

#include "Bullet.h"
#include "OrdinaryTarget.h"
#include "MovingTarget.h"
#include "ShineTarget.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Weapon.h"

#include "Mouse.h"

/*
	Класс стрельбища

	@param statistics_shown - показана ли статистика или нет (требуется для проверки и генерации новых мишеней)
	@param renderer - указатель на рендерер
	@param font - указатель на шрифт
	@param font_image - указаталь, который будет преобразован из шрифта
	@param bullet_texture - указатель на текстуру пули
	@param background_texture - указатель на текстуру фона
	@param mouse - указатель на курсор
	@param font_color - цвет текста
	@param textures - массив текстур
	@param targets - массив мишеней
	@param weapon - указатель на выбранное оружие
*/
class ShootingRange
{
private:
	bool statistics_shown = false;

	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;
	SDL_Texture* font_image = nullptr;
	SDL_Texture* bullet_texture;
	SDL_Texture* background_texture = nullptr;
	Mouse* mouse = nullptr;
	SDL_Color font_color = { 0, 0, 0, 255 };

	std::vector<SDL_Texture*> textures;
	std::vector<AbstractTarget*> targets;

public:
	Weapon* weapon = nullptr;

	/*
		Пустой конструктор
	*/
	ShootingRange();

	/*
		Основной конструктор 

		@param renderer - ссылка на рендерер
	*/
	ShootingRange(SDL_Renderer* renderer);

	/*
		Деструктор
	*/
	~ShootingRange();

	/*
		Метод отрисовки всех объектов на стрельбище
	*/
	void draw();

	/*
		Метод генерации мишеней
	*/
	void generateTargets();

	/*
		Метод смены оружия

		@param weapon_id - номер оружия
	*/
	void changeWeaponOn(int weapon_id);

	/*
		Метод, возвращающий показана ли статистика или нет

		@return statistics_shown
	*/
	bool isStatisticsShown();
};