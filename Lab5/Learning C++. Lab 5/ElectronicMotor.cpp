#include "ElectronicMotor.h"

ElectronicMotor::ElectronicMotor()
{
	wear_degree = 0.1f;
	replacement_price_degree = 150.0f * price_degree;
	fixing_price_degree = 70.0f * price_degree;
	service_life_degree = 200.0f;
	fixing_time_degree = 4.0f;

	type = "Electronic motor";

	generateFields();
}

void ElectronicMotor::work(float work_for)
{
	if (fix_type == "fixed"
		&& in_fixing_process >= fixing_time)
		condition += 1.5f * rand() / RAND_MAX;

	SparePart::work(work_for);
}
