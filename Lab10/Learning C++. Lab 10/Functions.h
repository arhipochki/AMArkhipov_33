#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_ttf.h"

/*
* Получаем знак от числа любого типа
* @param val - значение, от которого нужно получить знак
* @return sign - знак числа
*/
template <typename T>
int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

/*
	Функция, инициализирующая все нужные модули

	@return true - если всё загрузилось успешно, иначе false
*/
bool init();

/*
	Функция загрузки шрифта

	@param font_file - путь к шрифту
	@param font_size - размер шрифта
	@return TTF_Font* - указатель на новый шрифт, если всё успешно, иначе nullptr
*/
TTF_Font* openFont(const std::string& font_file, int font_size);

/*
	Функция загрузки текстуры

	@param renderer - ссылка на рендерер, где впоследующем будет отрисована текстура
	@param path - путь до текстуры
	@return SDL_Texture* - ссылка на загруженную текстуру, если всё успешно, иначе nullptr
*/
SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);

/*
	Функция превращения текста в текстуру

	@param renderer - ссылка на рендерер, где впоследующем будет отрисован текст
	@param font - ссылка на открытый шрифт
	@param message - текст
	@param color - цвет текста
	@return SDL_Texture* - ссылка на созданную текстуру из текста и шрифта, если всё успешно, иначе nullptr
*/
SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color);

/*
	Функция отрисовки текстуры с задананными размерами

	@param renderer - ссылка на рендерер, где будет отрисована текстура
	@param texture - ссылка на текстуру, которую надо отрисовать
	@param x - позиция по x
	@param y - позиция по y
	@param w - ширина текстуры
	@param h - высота текстуры
*/
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h);

/*
	Функция отрисовки текстуры

	@param renderer - ссылка на рендерер, где будет отрисована текстура
	@param texture - ссылка на текстуру, которую надо отрисовать
	@param x - позиция по x
	@param y - позиция по y
*/
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

/*
	Функция отрисовки квадрата
	
	@param renderer - указатель на рендерер
	@param x - позиция по x
	@param y - позиция по y
	@param w - ширина квадрата
	@param h - высота квадрата
	@param color - цвет квадрата
*/
void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color = { 0, 255, 0, 255 });

/*
	Функция получения полного пути

	@param m_path - изначальный путь
	@param relative_path - директория, до которой нужно вернуть путь
	@return full_path - полный путь до файла
*/
std::string getSourcePath(const std::string& m_path, const std::string& relative_path);