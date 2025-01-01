#include "SparePart.h"

#include <iostream>

SparePart::SparePart()
{
}

SparePart::SparePart(const SparePart& sparePart)
{
	replacement_price = sparePart.replacement_price;
	fixing_price = sparePart.fixing_price;
	service_life = sparePart.service_life;
	wear = sparePart.wear_degree;
	chance_of_failure = sparePart.chance_of_failure;
	fixing_time = sparePart.fixing_time;

	type = sparePart.type;
	replacement_price_degree = sparePart.replacement_price_degree;
	fixing_price_degree = sparePart.fixing_price_degree;
	service_life_degree = sparePart.service_life_degree;
	wear_degree = sparePart.wear_degree;
	fixing_time_degree = sparePart.replacement_price_degree;
}

void SparePart::generateFields()
{
	replacement_price = rand() * (replacement_price_degree) / RAND_MAX + replacement_price_degree;
	fixing_price = rand() * (fixing_price_degree) / RAND_MAX + fixing_price_degree;
	service_life = rand() * (service_life_degree) / RAND_MAX + service_life_degree;
	wear = rand() * (wear_degree) / RAND_MAX + wear_degree;
	chance_of_failure = 1.0f * rand() / RAND_MAX;
	fixing_time = rand() * (fixing_time_degree) / RAND_MAX + fixing_time_degree;
}

void SparePart::printInfo()
{
	std::cout << "Spare part type: " << type << "\n";
	std::cout << "Is stopped: " << ((is_stopped) ? "true" : "false") << "\n";
	std::cout << "Replacment price: " << replacement_price << " RUB\n";
	std::cout << "Fixing price: " << fixing_price << " RUB\n";
	std::cout << "Fixing time: " << fixing_time << " hrs\n";
	std::cout << "Service life: " << service_life << " hrs\n";
	std::cout << "Wear: " << wear << " % per hour\n";
	std::cout << "Condition: " << condition << "%\n";
	std::cout << "Chance of failure: " << chance_of_failure << "\n";
	std::cout << "Count of repairs: " << count_of_repairs << "\n";
	std::cout << "Count of changes: " << count_of_replacements << "\n";
}

void SparePart::regenerateWear()
{
	wear = rand() * (wear_degree) / RAND_MAX + wear_degree;

	std::cout << "NEW WEAR FOR " << type << " IS: " << wear << "\n";
}

void SparePart::work(float work_for)
{
	if (!is_stopped)
	{
		service_life -= work_for;
		condition -= wear * work_for;

		if (condition <= 0)
		{
			std::cout << "SPARE PART " << type << " IS OUT OF CONDITION. HAS TO BE CHANGED. PRICE: " << replacement_price << ".\n";
			is_stopped = true;

			fix_type = "changed";
		}
		else
		{
			float chance_to_failure = 1.0f * rand() / RAND_MAX;

			if (fabs(chance_to_failure - chance_of_failure) <= 0.001)
			{
				is_stopped = true;
				std::cout << "SPARE PART IS BROKEN: " << type << "\n";
				std::cout << "STOPPED FOR " << fixing_time << " hrs. FIXING PRICE: " << fixing_price << "\n";
				fix_type = "fixed";
			}

			if (service_life <= 0)
			{
				is_stopped = true;
				std::cout << "SPARE PART IS OUT OF SERVICE LIFE: " << type << "\n";
				std::cout << "STOPPED FOR " << fixing_time << " hrs. FIXING PRICE: " << fixing_price << "\n";
				fix_type = "fixed";
			}
		}
	}
	else
	{
		in_fixing_process += work_for;

		if (fix_type == "fixed" && in_fixing_process >= changing_time)
			fix();
		else if (fix_type == "changed" && in_fixing_process >= changing_time)
			replace();
	}
}

void SparePart::fix()
{
	std::cout << "DETAIL " << type << " WAS FIXED AND NOW CAN BE ENABLED!\n";

	count_of_repairs++;
	is_stopped = false;
	in_fixing_process = 0;
}

void SparePart::replace()
{
	std::cout << "DETAIL " << type << " WAS CHANGED AND NOW CAN BE ENABLED!\n";

	generateFields();
	
	condition = 100.0f;

	count_of_replacements++;
	is_stopped = false;
	in_fixing_process = 0;
}

bool SparePart::getStatus()
{
	return is_stopped;
}

float SparePart::getStopTime()
{
	return (fix_type == "fixed") ? fixing_time : changing_time;
}

int SparePart::getCountOfRepairs()
{
	return count_of_repairs;
}

int SparePart::getCountOfReplacements()
{
	return count_of_replacements;
}

float SparePart::getRepairPrice()
{
	return fixing_price;
}

float SparePart::getReplacementPrice()
{
	return replacement_price;
}