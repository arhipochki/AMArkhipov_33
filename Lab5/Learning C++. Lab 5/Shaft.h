#pragma once

#include "SparePart.h"

/*
	Класс вала.
*/
class Shaft : public SparePart
{	
public:
	/*
		Конструктор вала.
	*/
	Shaft();

	/*
		Почасовая работа вала.
	*/
	void work(float work_for) override;
};

