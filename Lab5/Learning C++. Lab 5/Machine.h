#pragma once

#include <vector>

#include "ControlPanel.h"
#include "CuttingHead.h"
#include "ElectronicMotor.h"
#include "Shaft.h"

/*
	Класс машины.
	@param spare_parts - запчасти, которые будут использоваться в станке
	@param is_stopped - остановлен ли станок
	@param id - номер станка
	@param total_downtime - суммарное время простоя
*/
class Machine
{
public:
	std::vector<SparePart*> spare_parts;
	bool is_stopped = false;
	int id = 0;
	float total_downtime = 0.0f;

	/*
		Конструктор станка.
	*/
	Machine();

	/*
		Дестркутор станка.
	*/
	~Machine();

	/*
		Метод регенерации износа деталей.
	*/
	void regenerateWearForParts();

	/*
		Метод работы станка.
	*/
	void work(float work_for);

	/*
		Выводит информацию о станке и запчастях.
	*/
	void printInfo();

	/*
		Метод, подсчитывающий количество починок деталей.
		@return count - возвращает количество починок.
	*/
	int countOfRepairs();

	/*
		Метод, подсчитывающий количество замен деталей.
		@return count - возвращает количество замен.
	*/
	int countOfReplacements();

	/*
		Метод, подсчитывающий количество затрат на поддержку работы станка.
		@return amount - возвращает количество средств, затраченных на станок.
	*/
	float totalAmount();
};

