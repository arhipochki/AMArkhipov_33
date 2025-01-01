#pragma once

#include "SparePart.h"

/*
	Класс режущей головки.
*/
class CuttingHead : public SparePart
{
public:
	/*
		Конструктор режущей головки.
	*/
	CuttingHead();

	/*
		Метод почасовой работы режущей головки.
	*/
	void work(float work_for) override;
};

