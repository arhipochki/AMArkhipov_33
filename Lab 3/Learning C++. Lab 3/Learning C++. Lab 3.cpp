#include <ctime>
#include <iostream>
#include <Windows.h>

#include "functions.h"

/*
    Вариант 1. Требуется написать программу, в которой:

    Будет реализована структура "Работник" с полями:
        - ФИО
        - Пол
        - Год рождения (Структура Даты)
    Создан массив хранящий N работников, кол-во считывается с клавиатуры.
    Заполнены или сгенерированы N работников.
    Написаны функции которые:
        - Проводит поиск по массиву работников и находит работника по ФИО.
        - Формирует срез работников из массива по году рождения (больше или меньше).
        - Выводит статистику работников по полу.
        - Сортирует массив работников по возрасту (учитываются все составляющие даты).
*/
int main()
{
    SetConsoleCP(1251);         // Выставляем ввод кириллицы в том числе
    SetConsoleOutputCP(1251);   // Выставляем вывод кириллицы в том числе

    srand(time(NULL));

    int N = 0;

    std::cout << "Input a count of employees: ";
    std::cin >> N;
    std::cout << "\n";

    Person* employees = new Person[N];

    char generate = 0;

    std::cout << "Input employees or generate them? [G]enerate/[I]nput: ";
    std::cin >> generate;
    std::cout << "\n";

    bool loop = true;
    while (loop)
    {
        switch (generate)
        {
        case 'G':
            loop = false;
            generateEmployees(employees, N);
            break;
        case 'I':
            loop = false;
            fillEmployees(employees, N);
            break;
        default:
            std::cout << "Ooops, wrong input. Choose one from [G, I]: ";
            std::cin >> generate;
            std::cout << "\n";
            break;
        }
    }

    system("cls");
    printEmployees(employees, N);

    int ans = 0;
    while (true)
    {
        std::cout << "Actions:\n"
            << "1) Search by name\n"
            << "2) Forms a cross-section of employees from the array by year of birth\n"
            << "3) See an employees statistics by sex\n"
            << "4) Sort employees by date of birth\n"
            << "5) Print employees\n"
            << "0) Exit\n"
            << "Choose an action: ";
        std::cin >> ans;
        std::cout << "\n";

        std::string name;
        int year = 0;
        char type = 0;
        char sex = 0;

        Person* found_person;

        system("cls");

        switch (ans)
        {
        case 0:
            return 0;
        case 1:
            std::cout << "Input a name to look for: ";
            std::cin.ignore(); // игнорируем последний перенос строки (\n)
            std::getline(std::cin, name);
            std::cout << "\n";
            found_person = searchByName(name, employees, N);

            if (found_person != nullptr)
                printPersonInfo(*found_person);
            else
                std::cout << "NOT FOUND\n\n";

            break;
        case 2:
            std::cout << "Input a year to make a cross-section: ";
            std::cin >> year;
            std::cout << "[A]bove or [L]ower?: ";
            std::cin >> type;
            std::cout << "\n";

            loop = true;
            while (loop)
            {
                switch (type)
                {
                case 'A':
                    loop = false;
                    break;
                case 'L':
                    loop = false;
                    break;
                default:
                    std::cout << "Ooops, wrong input. Choose one from [A, L]: ";
                    std::cin >> type;
                    std::cout << "\n";
                    break;
                }
            }

            formCrossSectionByYearOfBirth(year, type, employees, N);
            break;
        case 3:
            std::cout << "Input a sex to make a statistics [M]ale, [F]emale: ";
            std::cin >> sex;
            std::cout << "\n";

            loop = true;
            while (loop)
            {
                switch (sex)
                {
                case 'M':
                    loop = false;
                    employeesStatisticsBySex(Sex::MALE, employees, N);
                    break;
                case 'F':
                    loop = false;
                    employeesStatisticsBySex(Sex::FEMALE, employees, N);
                    break;
                default:
                    std::cout << "Ooops, wrong input. Choose one from [M, F]: ";
                    std::cin >> sex;
                    std::cout << "\n";
                    break;
                }
            }
            break;
        case 4:
            std::cout << "[I]ncrease or [D]ecrease?: ";
            std::cin >> type;
            std::cout << "\n";

            loop = true;
            while (loop)
            {
                switch (type)
                {
                case 'I':
                    loop = false;
                    break;
                case 'D':
                    loop = false;
                    break;
                default:
                    std::cout << "Ooops, wrong input. Choose one from [I, D]: ";
                    std::cin >> type;
                    std::cout << "\n";
                    break;
                }
            }

            sortByAge(type, employees, N);

            printEmployees(employees, N);
            break;
        case 5:
            printEmployees(employees, N);
            break;
        default:
            break;
        }
    }

    delete[] employees;

    return 0;
}