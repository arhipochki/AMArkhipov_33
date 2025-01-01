#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_ttf.h"

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
	Функция получения полного пути

	@param path - до какого файла вернуть путь
	@return full_path - полный путь до файла
*/
std::string getSourcePath(const std::string& path);