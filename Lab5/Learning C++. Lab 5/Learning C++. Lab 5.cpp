#include <iostream>
#include <chrono>
#include <thread>

#include "Machine.h"

/*
    Перечисление месяцев, начиная с 1
*/
enum class Month {
    JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
    JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

/*
Вариант 1
    Создайте класс Запчасть, которая имеет стоимость замены, стоимость однократной починки, время требуемое на починку, 
        срок службы до полной замены, степень изношенности, 
        метод определения поломки, метод работы, в рамках которого запчасть изнашивается(принимает интенсивность использования).
    Создайте классы Вал, Электродвигатель, Панель управления, Режущая головка, каждый класс должен быть наследован от класса запчасть 
        и определять свой способ проверки наличия поломки и метод работы который принимает интенсивность использования.
    Создайте классы Станок, который будет иметь набор разных запчастей, которые будут использоваться в процессе работы станка 
        и постепенно изнашиваться. Станок простаивает в зависимости от длительности ремонта запчасти, 
        в случае если запчасть полностью выходит из строя и подходит срок ее службы, время на ее замену фиксированные 4 часа.
    Создайте метод работы станка в течении указанного времени, который будет изнашивать каждую составную часть станка с учетом интенсивности работы 
        на станке с возможностью неожиданной поломки в процессе работы.
    (Усложненный вариант) Проведите моделирование работы цеха в течении одного года. В рамках работы цеха происходит каждодневная работа набора 
        станков по 12 часов. Случайным образом определяется интенсивность работы в течении месяца. Требуется получить статистику работы цеха за 
        один год: по количеству заменяемых частей, стоимости ремонта каждого станка, количеству поломок 
        каждого станка и всех станков, суммарный простой станков и максимальный суммарный простой одного станка.
*/
int main()
{
    srand(time(NULL));

    int N;
    std::cout << "Input a count of machines: ";
    std::cin >> N;
    std::cout << "\n";

    const int count_of_years = 1;             // Количество лет работы
    const int count_of_months = 12;           // Количество месяцев работы
    const float hours_to_work = 12.0f;        // Количество часов рабочего дня

    std::vector<Machine*> machines;

    for (int i = 0; i < N; i++)
    {
        machines.push_back(new Machine());
        machines[i]->id = i;

        machines[i]->printInfo();
    }

    char ans;
    std::cout << "Start simulation for 1 year?: [Y]es/[N]o ";
    std::cin >> ans;
    bool is_answered = false;
    while (!is_answered)
    {
        switch (ans)
        {
        case 'Y':
            is_answered = true;
            break;
        case 'N':
            return 0;
        default:
            std::cout << "[Y] or [N]? ";
            std::cin >> ans;
            break;
        }
    }

    auto start = std::chrono::system_clock::now();
    
    int count_of_days = 0;                    // Количество дней для симуляции работы
    const float work_for = 0.1f;              // Снимаем статистику по 0.1 часа (6 минут)
    for (int year = 0; year < count_of_years; year++)
    {
        for (int month = (int)Month::JANUARY; month <= count_of_months; month++)
        {
            Month m = (Month)month;
            if (m == Month::FEBRUARY)
                count_of_days = 28;
            else if (m == Month::APRIL
                || m == Month::JUNE
                || m == Month::SEPTEMBER
                || m == Month::NOVEMBER)
                count_of_days = 30;
            else
                count_of_days = 31;

            for (int day = 1; day <= count_of_days; day++)
            {
                for (float i = work_for; i < hours_to_work + work_for; i += work_for)
                {
                    std::cout << "Month: " << month << " Day: " << day << ". Time has passed: " << i << " hrs \n";

                    for (auto& machine : machines)
                    {
                        machine->work(work_for);

                        std::cout << "Machine ID: " << machine->id << " status: " << ((machine->is_stopped) ? "stopped" : "running") << '\n';
                    }
                }
            }

            // Новый месяц - новый износ.
            for (auto& machine : machines)
            {
                std::cout << "Machine ID: " << machine->id << " ";
                machine->regenerateWearForParts();
            }
        }
    }

    std::cout << "TOTAL DOWNTIMES:\n";
    float downtime_sum = 0.0f;
    float max_downtime = 0.0f;
    for (auto& machine : machines)
    {
        std::cout << "Machine ID: " << machine->id << " total downtime: " << machine->total_downtime << "\n";
        downtime_sum += machine->total_downtime;
        if (machine->total_downtime > max_downtime)
            max_downtime = machine->total_downtime;
    }

    std::cout << "Summary of downtimes: " << downtime_sum << '\n';
    std::cout << "Max downtime: " << max_downtime << '\n';

    std::cout << "TOTAL COUNT OF REPAIRS:\n";
    for (auto& machine : machines)
    {
        std::cout << "Machine ID: " << machine->id << " total count of repairs: " << machine->countOfRepairs() << "\n";
    }

    std::cout << "TOTAL COUNT OF REPLACEMENTS:\n";
    for (auto& machine : machines)
    {
        std::cout << "Machine ID: " << machine->id << " total count of replacements: " << machine->countOfReplacements() << "\n";
    }

    std::cout << "THE AMOUNT OF MONEY SPENT ON MACHINE SUPPORT (Repairs + Replacements):\n";
    for (auto& machine : machines)
    {
        std::cout << "Machine ID: " << machine->id << " total amount of money: " << machine->totalAmount() << "RUB \n";
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "ELAPSED TIME: " << elapsed_seconds.count() << "s \n";

    for (auto& machine : machines)
        delete machine;

    machines.clear();

    return 0;
}