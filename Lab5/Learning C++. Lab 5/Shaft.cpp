#include "Shaft.h"

Shaft::Shaft()
{
	wear_degree = 0.9f;
	replacement_price_degree = 50.0f * price_degree;
	fixing_price_degree = 30.0f * price_degree;
	service_life_degree = 60.0f;
	fixing_time_degree = 2.0f;

	type = "Shaft";

	generateFields();
}

void Shaft::work(float work_for)
{
	if (fix_type == "fixed"
		&& in_fixing_process >= fixing_time)
		condition += 0.8f * rand() / RAND_MAX;

	SparePart::work(work_for);
}
