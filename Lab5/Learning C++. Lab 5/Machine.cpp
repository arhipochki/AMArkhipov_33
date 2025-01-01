#include "Machine.h"

#include <iostream>

Machine::Machine()
{
	spare_parts = { new ControlPanel(), new CuttingHead(),
					new ElectronicMotor(), new Shaft() };
}

Machine::~Machine()
{
	for (auto& part : spare_parts)
		delete part;
	spare_parts.clear();
}

void Machine::regenerateWearForParts()
{
	for (auto& part : spare_parts)
		part->regenerateWear();
}

void Machine::work(float work_for)
{
	is_stopped = false;

	for (auto& part : spare_parts)
		is_stopped |= part->getStatus();

	if (!is_stopped)
	{
		for (auto& part : spare_parts)
		{
			part->work(work_for);

			if (part->getStatus())
				total_downtime += part->getStopTime();
		}
	}
	else
	{
		std::cout << "Waiting to complete a fixing...\n";

		for (auto& part : spare_parts)
		{
			if (part->getStatus())
				part->work(work_for);
		}
	}
}

void Machine::printInfo()
{
	std::cout << "Machine ID: " << id << "\n";
	std::cout << "Is stopped: " << ((is_stopped) ? "true" : "false") << "\n\n";
	for (auto& part : spare_parts)
	{
		part->printInfo();
		std::cout << "\n";
	}
	std::cout << "--------------------------------------\n";
}

int Machine::countOfRepairs()
{
	int count = 0;

	for (auto& part : spare_parts)
		count += part->getCountOfRepairs();

	return count;
}

int Machine::countOfReplacements()
{
	int count = 0;

	for (auto& part : spare_parts)
		count += part->getCountOfReplacements();

	return count;
}

float Machine::totalAmount()
{
	float amount = 0.0f;

	for (auto& part : spare_parts)
	{
		amount += part->getCountOfRepairs() * part->getRepairPrice();
		amount += part->getCountOfReplacements() * part->getReplacementPrice();
	}

	return amount;
}
