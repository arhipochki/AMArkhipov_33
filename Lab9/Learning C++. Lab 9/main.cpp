#include <algorithm>
#include <vector>
#include <iterator>

#include "Functions.h"

// НЕ БЕЙТЕ, УДОБНО ДЛЯ ДЕБАГА! (🤡🤡🤡🤡)
#define TYPE float
#define LEFT -15.0f
#define RIGHT 15.0f

/**
 * Вариант 3
 * Требуется разработать класс для хранения квадратного уровнения в общей форме.
 * Класс должен быть шаблонным и использовать указанный тип для коэффициентов и корней.
 * Конструктор класса принимает все коэффициенты уровавнения и находит корни уравнения.
 * Изменять коэффициенты и корни после создания объекта класса нельзя.
 * Сгенерировать N объектов класса, записав их в контейнер.
 * Перегрузить дружественную функцию - оператор вывода данных в поток, и вывести
 *  все объекты из контейнера.
 * С использованием стандартного алгоритма реализовать метод, который проверяет,
 *  есть ли среди корней введенный пользователем корень.
 * С использованием стандартного алгоритма реализовать метод, который проверяет
 *  количество корней, которые меньше заданного пользователем корня. Использовать лямбда-выражение.
 * (Усложненный вариант) Сделать функцию которая переберая все объекты в котнейнере,
 *  формирует вектор уникальных корней с использованием методов стандартной библиотеки.
 * (Усложненный вариант) Сделать функцию которая сортирует уравнения в котейнере по
 *  возрастанию суммы модулей корней.
 */
int main(void)
{
    const int N = 5;

    std::vector<QuadraticEquation<TYPE>> vec =
        generate<TYPE, std::vector<QuadraticEquation<TYPE>>>(N, LEFT, RIGHT);

    vec.push_back(vec[N - 1]);
    vec.push_back(vec[N - 1]);

    std::cout << "Generated vector:\n";
    std::copy(vec.begin(), vec.end(),
        std::ostream_iterator<QuadraticEquation<TYPE>>(std::cout, "\n"));

    TYPE num[2];
    std::cout << "Input a root (a and b parts, if it's non complex the second part must be 0): ";
    std::cin >> num[0] >> num[1];
    num[0] = round(num[0] * ROUND_TO) / ROUND_TO;
    num[1] = round(num[1] * ROUND_TO) / ROUND_TO;
    std::cout << "\n";

    QuadraticEquation<TYPE> found = findByUserNum(num, vec);

    std::cout << "Equation, that has a root as user's root:\n";
    if (found.isEmpty())
        std::cout << "NOT FOUND!\n";
    else
        std::cout << found << "\n";

    std::cout << "Count of roots lower than user's root: " << findCountOfRootsLowerNum(num, vec) << "\n";

    auto new_vec =
        uniqueVector(vec);

    std::cout << "Unique vector:\n";
    std::copy(new_vec.begin(), new_vec.end(),
        std::ostream_iterator<QuadraticEquation<TYPE>>(std::cout, "\n"));

    sortByRoots(new_vec);

    std::cout << "Sorted unique:\n";
    std::copy(new_vec.begin(), new_vec.end(),
        std::ostream_iterator<QuadraticEquation<TYPE>>(std::cout, "\n"));

    return 0;
}
