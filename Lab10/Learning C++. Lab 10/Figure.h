#pragma once

#include "Functions.h"
#include "ChessType.h"
#include "Defines.h"

#include "Logger.h"

/**
 * @brief Класс фигуры
 * 
 * @param logger - объект логгера
 * @param ren - указатель на рендерер
 * @param tex - указатель на текстуру
 * @param map_x - координата x по карте 
 * @param map_y - координата y по карте 
 * @param texture_x - координата текстуры x по окну
 * @param texture_y - координата текстуры y по окну 
 * @param size - размер текстуры фигуры (можно было упразднить)
 * @param type - тип фигуры
 * @param team - команда фигуры
 * @param possible_ways - возможные пути фигуры
 * @param possible_attacks - возможные атаки (используется только в пешке, но можно было подвязать все фигуры)
 * @param history_of_moves - история ходов фигуры
 * @param eaten_figures - вектор съеденных фигур фигурой
 * @param first_move - первый ход ли фигуры 
 * @param is_attacked - атакована ли фигура (используется только в короле)
 */
class Figure
{
protected:
	Logger logger = Logger();

	SDL_Renderer* ren = nullptr;
	SDL_Texture* tex = nullptr;

	int map_x = 0;
	int map_y = 0;
	int texture_x = 0, texture_y = 0;
	int size = 0;

	ChessType type = ChessType::Pawn;
	ChessTeam team = ChessTeam::Black;

	std::vector<std::pair<int, int>> possible_ways;
	std::vector<std::pair<int, int>> possible_attacks;

	std::vector<std::pair<int, int>> history_of_moves;

	std::vector<Figure*> eaten_figures;

	bool first_move = true;
	bool is_attacked = false; // only for king
public:

	// Пустой конструктор
	Figure() {}

	/**
	 * @brief Основной конструктор
	 * 
	 * @param renderer - указатель на ренедерер
	 * @param texture - указатель на текстуру
	 * @param x - координата x по карте
	 * @param y - координата y по карте
	 * @param size - размер текстуры
	 * @param type - тип фигуры
	 * @param team - команда фигуры
	 */
	Figure(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int size, ChessType type, ChessTeam team)
		: ren(renderer), tex(texture), map_x(x), map_y(y), size(size), type(type), team(team)
	{
		texture_x = FIELD_X + map_x * size; // (x - FIELD_X) / size
		texture_y = FIELD_Y + map_y * size;
	}

	Figure(Figure* figure);

	/**
	 * @brief Абстрактный метод возможности атаки фигурой
	 * 
	 * @param chess_map - указатель на карту поля
	 * @param figure - фигура, которую надо проверить на возможность атаки
	 */
	virtual void canAttack(char(*chess_map)[N], Figure* figure) { }

	/**
	 * @brief Метод проверки возможных путей фигуры
	 * 
	 * @param chess_map - указатель на карту поля
	 */
	virtual void checkAllPossibleWays(char(*chess_map)[N]) { }

	// Метод очистки возможных путей фигуры
	void clearPossibleWays() { possible_ways.clear(); }

	/**
	 * @brief Метод передвижения фигуры
	 * 
	 * @param chess_map - указатель на карту поля
	 * @param figures - ссылка на вектор фигур
	 * @param move_to_x - новая координата x по карте
	 * @param move_to_y - новая координата y по карте
	 * @param was_moved - указатель на переменную, куда вернётся результат хода (true - была двинута, иначе false)
	 * @param hand_move - передвижение ли игроком (по умолчанию false)
	 * @param eaten_figures - указатель на вектор, куда будут созраняться съеденные фигуры (по умолчанию nullptr)
	 */
	void move(char(*chess_map)[N], std::vector<Figure*>& figures, int move_to_x, 
			int move_to_y, bool* was_moved = nullptr, bool hand_move = false, std::vector<Figure*>* eaten_figures = nullptr);

	// Метод отрисовки текстуры фигуры
	void draw() { renderTexture(ren, tex, texture_x, texture_y, size, size); }

	// Метод отрисовки возможных путей фигуры
	void drawWays();

	// Вывод информации о фигуре
	void printInfo();
	
	/**
	 * @brief Метод удаления хода
	 * 
	 * @param move - ход, который будет удалён из возможных ходов фигуры
	 */
	void eraseMove(std::pair<int, int> move);

	/**
	 * @brief Удаляем пересекаемые ходы с фигурой
	 * 
	 * @param figure - указатель на фигуру, с которой будем сравнить ходы
	 */
	void removeIntersectedWays(Figure* figure);

	// Метод удаления дублированных ходов
	void removeDuplicatedWays();

	// Метод получения типа фигуры
	ChessType getType() { return type; }

	// Метод получения команды фигуры
	ChessTeam getTeam() { return team; }

	/**
	 * @brief Метод добавления съеденной фигуры
	 * 
	 * @param figure - указатель на съеденную фигуру
	 */
	void addEatenFigure(Figure* figure) { eaten_figures.push_back(figure); }
	
	/**
	 * @brief Задаём координату x по карте
	 * 
	 * @param x - новая координата
	 */
	void setMapX(int x) { map_x = x; }

	/**
	 * @brief Задаём координату y по карте
	 * 
	 * @param y - новая координата
	 */
	void setMapY(int y) { map_y = y; }

	/**
	 * @brief Задаём состояние фигуры (атаковано ли)
	 * 
	 * @param state - состояние (true или false)
	 */
	void setAttacked(bool state) { is_attacked = state; }

	// Метод получение координаты текстуры по x
	int getTextureX()	{ return texture_x; }

	// Метод получение координаты текстуры по y
	int getTextureY()	{ return texture_y; }

	// Метод получение координаты x фигуры по карте
	int getMapX()		{ return map_x; }

	// Метод получение координаты x фигуры по карте
	int getMapY()		{ return map_y; }

	// Метод получение размера текстуры
	int getSize()		{ return size; }

	// Метод получение состояния фигуры (атакована ли она)
	bool isAttacked() { return is_attacked; }

	// Метод получение вектора возможных путей
	std::vector<std::pair<int, int>> getPossibleWays()		{ return possible_ways; }
	
	// Метод получение вектора возможных атак
	std::vector<std::pair<int, int>> getPossibleAttacks()	{ return possible_attacks; }
	
	// Метод получение вектора истории ходов
	std::vector<std::pair<int, int>> getHistoryOfMoves()	{ return history_of_moves; }

	// Метод получение вектора съеденных фигур
	std::vector<Figure*> getEatenFigures() { return eaten_figures; }
};