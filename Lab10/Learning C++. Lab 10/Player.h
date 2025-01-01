#pragma once

#include "Figure.h"

/**
 * @brief Класс игрока
 * 
 * @param name - имя игрока
 * @param start_team - команда, за которую он играет
 * @param eaten_figures - вектор съеденных фигур
 * @param game_time - игровое время
 * @param clock_start - запущены ли часы
 */
class Player
{
private:
	std::string name;
	ChessTeam start_team;

	std::vector<Figure*> eaten_figures;

	std::chrono::milliseconds game_time;
	bool clock_start = false;
public:
	/**
	 * @brief Основной конструктор
	 * 
	 * @param name - имя
	 * @param time - время на партию
	 */
	Player(std::string name, std::chrono::milliseconds time) : name(name), game_time(time) { }

	/**
	 * @brief Метод назначения стороны, за которую будет играть игрок
	 * 
	 * @param team - тип команды
	 */
	void setStartTeam(ChessTeam team) { start_team = team; }

	/**
	 * @brief Получаем команду игрока
	 * 
	 * @return start_team
	 */
	ChessTeam getTeam() { return start_team; }

	void moveFigure(Figure* figure, int move_to_x, int move_to_y, 
		bool* was_moved, char (*chess_map)[N], std::vector<Figure*>& figures);

	/**
	 * @brief Отнимаем затраченное время
	 * 
	 * @param time - время, которое требуется отнять
	 */
	void takeElapsedTime(std::chrono::milliseconds time) { game_time -= time; }

	/**
	 * @brief Получаем неформатированное время
	 * 
	 * @return game_time
	 */
	std::chrono::milliseconds getRawTime() { return game_time; }

	/**
	 * @brief Получаем форматированное время (мм:сс)
	 * 
	 * @return std::string 
	 */
	std::string getGameTime();

	/**
	 * @brief Получаем, запущены ли часы
	 * 
	 * @return clock_start
	 */
	bool getClock()		{ return clock_start; }

	/**
	 * @brief Меняем статус часов
	 */
	void changeClock()  { clock_start = !clock_start; }
	
	/**
	 * @brief Останавливаем часы
	 */
	void stopClock()	{ clock_start = false; }

	/**
	 * @brief Получаем имя игрока
	 * 
	 * @return std::string 
	 */
	std::string getName() { return name; }

	/**
	 * @brief Получаем вектор съеденных фигур игроком
	 * 
	 * @return std::vector<Figure*> 
	 */
	std::vector<Figure*> getEatenFigures() { return eaten_figures; }
};