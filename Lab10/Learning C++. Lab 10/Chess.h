#pragma once

#include "Functions.h"
#include "Player.h"
#include "Logger.h"

/**
 * @brief Класс игры "шахматы"
 * 
 * @param logger - объект логгера, с помощью которого будем выводить информацию
 * @param window - указатель окна
 * @param renderer - указатель на рендерер
 * @param font - указатель на шрифт
 * @param font_images - массив текстур из имён игроков
 * @param font_times - массив текстур из времён игроков
 * @param last_message - текстура последнего сообщения о мате
 * @param winner - последнее сообщение
 * @param game_time_mseconds - время на партию (милли секунды)
 * @param isRunning - запущено ли окно
 * @param game_started - началась ли игра
 * @param game_ended - закончилась ли игра
 * @param statistics_shown - показана ли статистика
 * @param loaded_textures - словарь загруженных текстур
 * @param textures - массив путей текстур
 * @param figures - вектор фигур
 * @param kings - массив королей (вынесим отдельно для удобства просчёта шаха/мата)
 * @param players - массив игроков
 * @param chess_map - поле
 * @param current_team_move - текущий ход у команды
 * @param launch_path - путь, откуда запустили программу
 */
class Chess
{
private:
	Logger logger = Logger();

	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font = nullptr;
	SDL_Texture* font_images[2];
	SDL_Texture* font_times[2];
	SDL_Texture* last_message;

	std::string winner = "game ended";

	const std::chrono::milliseconds game_time_mseconds = std::chrono::milliseconds(60 * 60 * 1000);

	bool isRunning = false;
	bool game_started = false;
	bool game_ended = false;
	bool statistics_shown = false;

	std::map<std::string, SDL_Texture*> loaded_textures;

	//vector of figures for each coors (y, x)
	std::vector<Figure*> figures;

	Figure* kings[2];

	Player* players[2];

	//Карта. P - pawn, N - Knight, B - Bishop, K - King, Q - Queen
	char chess_map[N][N] = {
	   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	   {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	   {'0', '0', '0', '0', '0', '0', '0', '0'},
	   {'0', '0', '0', '0', '0', '0', '0', '0'},
	   {'0', '0', '0', '0', '0', '0', '0', '0'},
	   {'0', '0', '0', '0', '0', '0', '0', '0'},
	   {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
	};

	ChessTeam current_team_move = ChessTeam::White;

	std::string launch_path = "";
public:

	// Основной конструктор
	Chess(std::string lauch_path);

	// Деструктор
	~Chess();

	// Метод отрисовки текстур
	void draw();

	// Основный метод, тело игры
	void run();

	// Метод проверки мата
	void checkCheckmate();

	// Метод проверки шаха
	void checkTheCheck();

	/**
	 * @brief Проверка возможных путей у фигуры
	 * 
	 * @param figure - указатель на фигуру
	 */
	void checkPossibleWays(Figure* figure);

	// Вывод статистики по игре
	void printStatistics();

	// Отсчёт времени у ходящего игрока
	void takeTime();
};