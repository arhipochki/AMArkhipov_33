#include "CuttingHead.h"

CuttingHead::CuttingHead()
{
	wear_degree = 1.0f;
	replacement_price_degree = 10.0f * price_degree;
	fixing_price_degree = 5.0f * price_degree;
	service_life_degree = 20.0f;
	fixing_time_degree = 0.5f;
	
	type = "Cutting Head";

	generateFields();
}

void CuttingHead::work(float work_for)
{
	if (fix_type == "fixed"
		&& in_fixing_process >= fixing_time)
		condition += 0.5f * rand() / RAND_MAX;

	SparePart::work(work_for);
}
