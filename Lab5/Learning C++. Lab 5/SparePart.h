#pragma once

#include <string>

/*
	Класс запчасть.

	@param price_degree  - для перевода цены в нужную степень (тут в тысячах)
	@param changing_time - время замены (в часах)
			 										// Степени: параметры от которых будет генерироваться значение (от degree до rand() * degree)
	@param wear_degree - cтепень износа
	@param replacement_price_degree - cтепень стоимости замены детали
	@param fixing_price_degree - cтепень стоимости ремонта детали
	@param service_life_degree - cтепень жизни детали
	@param fixing_time_degree - степень времени ремонта детали
	 
	@param replacement_price - цена замены
	@param fixing_price - цена починки
	@param service_life - время работы до поломки (в часах)
	@param wear - износ в час
	@param condition - состояние детали
	@param chance_of_failure - шанс выхода из строя
	@param fixing_time - время на починку
	@param working_time - время, сколько проработала запчасть
	@param in_fixing_process - сколько прошло времени с начала ремонта/замены
	
	@param count_of_repairs - количество ремонтов
	@param count_of_replacements - количество замен
	
	@param type - тип детали
	@param fix_type - тип ремонта: changed, fixed
	
	@param is_stopped - выведена ли деталь из работы
*/
class SparePart
{
protected:
	const float price_degree = 1000.0f;
	const float changing_time = 4.0f;

	float wear_degree = 0.00f;
	float replacement_price_degree = 0.0f;
	float fixing_price_degree = 0.0f;
	float service_life_degree = 0.0f;
	float fixing_time_degree = 0.0f;

	float replacement_price = 0.0f;
	float fixing_price = 0.0f;
	float service_life = 0.0f;
	float wear = 0.0f;
	float condition = 100.0f;
	float chance_of_failure = 0.0f;
	float fixing_time = 0.0f;
	float working_time = 0.0f;
	float in_fixing_process = 0.0f;

	int count_of_repairs = 0;
	int count_of_replacements = 0;

	std::string type = "spare part";
	std::string fix_type = "changed";

	bool is_stopped = false;

public:
	/*
		Пустой конструктор детали.
	*/
	SparePart();

	/*
		Конуструктор копирования.
		@param sparePart - указатель на запчасть, которая будет скопирована.
	*/
	SparePart(const SparePart& sparePart);

	/*
		Метод генерации полей детали.
	*/
	void generateFields();

	/*
		Метод вывода информации о запчасти.
	*/
	void printInfo();

	/*
		Метод регенерации износа.
	*/
	void regenerateWear();

	/*
		Метод ремонта.
	*/
	void fix();

	/*
		Метод замены.
	*/
	void replace();

	/*
		Метод разовой работы детали.
		@param work_for - время работы.
	*/
	virtual void work(float work_for);

	/*
		Метод проверки статуса рабоы.
		@return is_stopped - остановлена или нет запчасть. 
	*/
	bool getStatus();

	/*
		Метод, возвращающий значение, на сколько встала деталь.
		@return fixing_time - время отстранения от работы детали.
	*/
	float getStopTime();

	/*
		Метод, возвращающий значение, сколько было починок у детали.
		@return count_of_repairs - количество починок.
	*/
	int getCountOfRepairs();

	/*
		Метод, возвращающий значение, сколько было замен детали.
		@return count_of_replacements - количество починок.
	*/
	int getCountOfReplacements();

	/*
		Метод, возвращающий значение, сколько стоит ремонт детали.
		@return fixing_price - возвращает количество средст на ремонт детали.
	*/
	float getRepairPrice();

	/*
		Метод, возвращающий значение, сколько стоит замена детали.
		@return replacement_price - возвращает количество средст на замену детали.
	*/
	float getReplacementPrice();
};