#pragma once

#include "SparePart.h"

/*
	Класс электрического мотора.
*/
class ElectronicMotor : public SparePart
{	
public:	
	/*
		Конструктор электромотора.
	*/
	ElectronicMotor();

	/*
		Почасовая работа мотора.
	*/
	void work(float work_for) override;
};

