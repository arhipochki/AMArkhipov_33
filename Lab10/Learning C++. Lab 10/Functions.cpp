#include <sstream>
#include <fstream>

#include "Functions.h"
#include "Defines.h"

bool init()
{
	// Инициализация шрифтов
	if (TTF_Init() != 0)
	{
		std::cout << "Could't init TTF: " << TTF_GetError() << "\n";
		return false;
	}

	// Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Couldn't init SDL: " << SDL_GetError() << "\n";
		return false;
	}

	// Инициализация SDL_Image
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "Could't init image: " << IMG_GetError() << "\n";
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());

	if (!texture)
		std::cout << IMG_GetError() << "\n";

	return texture;
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h)
{
	SDL_Rect dist;
	dist.x = x;
	dist.y = y;
	dist.w = w;
	dist.h = h;

	SDL_RenderCopy(renderer, texture, NULL, &dist);
}

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h); // Получаем исходные размеры текстуры

	renderTexture(renderer, texture, x, y, w, h);
}

void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color)
{
	SDL_Rect rect;
	rect.w = w;
	rect.h = h;

	rect.x = x;
	rect.y = y;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderDrawRect(renderer, &rect);
}

std::string getSourcePath(const std::string& m_path, const std::string& relative_path)
{
	std::ifstream f;
	f.open(m_path + "/" + relative_path.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Error: FAILED TO OPEN A RELATIVE PATH FILE!: " << relative_path << "\n";
		return {};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

TTF_Font* openFont(const std::string& font_file, int font_size)
{
	TTF_Font* font = TTF_OpenFont(font_file.c_str(), font_size);
	if (font == nullptr)
		std::cout << "Couldn't load a font: " << TTF_GetError() << "\n";

	return font;
}

SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& message, SDL_Color color)
{
	SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (font == nullptr)
	{
		std::cout << "Couldn't make a surface: " << SDL_GetError() << "\n";
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		std::cout << "Couldn't create a texture: " << SDL_GetError() << "\n";

	SDL_FreeSurface(surf);

	return texture;
}
