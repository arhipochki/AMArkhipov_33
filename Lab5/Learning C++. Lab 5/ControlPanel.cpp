#include "ControlPanel.h"

#include <iostream>

ControlPanel::ControlPanel()
{
	wear_degree = 0.05f;
	replacement_price_degree = 60.0f * price_degree;
	fixing_price_degree = 30.0f * price_degree;
	service_life_degree = 80.0f;
	fixing_time_degree = 1.0f;

	type = "control panel";

	generateFields();
}

void ControlPanel::work(float work_for)
{
	if (fix_type == "fixed"
		&& in_fixing_process >= fixing_time)
		condition += 1.0f * rand() / RAND_MAX;
	
	SparePart::work(work_for);
}