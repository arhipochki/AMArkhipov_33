#pragma once

#include "SparePart.h"

/*
	Класс панели управления.
*/
class ControlPanel : public SparePart
{
public:
	/*
		Конструктор панели управления.
	*/
	ControlPanel();

	/*
		Деструктор панели управления.
	*/
	~ControlPanel() {};

	/*
		Метод почасовой работы панели.
	*/
	void work(float work_for) override;
};

