#pragma once

/*
	Абстрактный класс мишени.

	@param id - номер мишени
	@param attemps - количество попыток, чтобы сбить мишень 
	@param width - ширина
	@param heigth - высота
	@param px - координата по x
	@param py - координата по y
	@param damage_taken - количество полученного урона
	@param chance - шанс попадания
	@param health - количество здоровья
	@param is_movable - двигающаяся ли мишени
	@param destroyed - уничтожена ли мишень
*/
class AbstractTarget
{
public:
	int id;
	int attemps;
	float width, height;
	float px, py;
	float damage_taken;
	float chance;
	float health;

	bool is_movable;
	bool destroyed;

	// Метод уничтожения мишени
	virtual void destroy() = 0;

	// Метод передвижения мишени
	virtual void move() = 0;

	// Метод проверки коллизий мишений
	virtual void checkCollision(AbstractTarget* a_target) = 0;
	
	// Метод отрисовки мишени
	virtual void draw() = 0;

	// Метод вывода статистики о мишени
	virtual void printStatistics() = 0;

	/*
		Метод, считающая полученый урон

		@param damage - количество полученного урона
	*/
	void takeDamage(float damage);

	/*
		Метод проверки попадания в мишень
	*/
	bool isMissed();

	/*
		Метод, проверяющий, показана ли мишень

		@return true - если мишень не уничтожена и должна быть отрисована, иначе false
	*/
	bool isShown();
};