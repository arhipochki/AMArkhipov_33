#pragma once

#include "QuadraticEquation.h"

#include <random>

/**
 * @brief Генерация контейнера
 *
 * @tparam Type - тип чисел
 * @tparam Container - тип контейнера
 * @param N - количество чисел
 * @param left - левая граница генерации
 * @param right - правая граница генерации
 * @return Container - заполненый контейнер
 */
template <typename Type, class Container>
Container generate(
    const int& N,
    const Type& left = std::is_floating_point<Type>::value ? -1.f : -100,
    const Type& right = std::is_floating_point<Type>::value ? 1.f : 100
)
{
    std::random_device r;
    std::mt19937 engine(r()); // A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
    Container container;

    if constexpr (std::is_floating_point<Type>::value)
    {
        std::uniform_real_distribution<Type> dist(left, right);

        for (int i = 0; i < N; i++) container.push_back(
            QuadraticEquation(dist(engine), dist(engine), dist(engine))
        );
    }
    else
    {
        std::uniform_int_distribution<Type> dist(left, right);

        for (int i = 0; i < N; i++) container.push_back(
            QuadraticEquation(dist(engine), dist(engine), dist(engine))
        );
    }

    return container;
}

/**
 * @brief Создаём контейнер уравнений с уникальными корнями
 *
 * @tparam Container - тип контейнера
 * @param container - сам конетейнер, в котором будем искать
 * @return Container - новый контейнер, без повторяющихся корней
 */
template <class Container>
Container uniqueVector(
    Container container
)
{
    Container new_container;

    for (const auto el : container)
        if (std::find(new_container.begin(), new_container.end(), el) == new_container.end())
            new_container.push_back(el);

    return new_container;
}

/**
 * @brief Сортировка контейнера по сумме модулей уравнения
 *
 * @tparam Container - тип контейнера
 * @param container - указатель на сортируемый контейнер
 */
template <class Container>
void sortByRoots(Container& container)
{
    std::sort(container.begin(), container.end());
}

/**
 * @brief Поиск уравнения по заданному корню пользователя
 *
 * @tparam T - тип корня
 * @tparam Container - тип контейнера
 * @param user_root - корень пользователя
 * @param container - указатель на контейнер, в котором будем искать
 * @return found - найденный экземпляр уравнения
 */
template <typename T, class Container>
QuadraticEquation<T> findByUserNum(T* user_root, Container& container)
{
    auto found = std::find_if(container.begin(), container.end(),
        [user_root](QuadraticEquation<T>& eq)
        {
            auto roots = eq.getRoots();

            return ((roots[0][0] == user_root[0] && roots[0][1] == user_root[1])
                || (roots[1][0] == user_root[0] && roots[1][1] == user_root[1]));
        }
    );

    if (found == container.end())
        return QuadraticEquation<T>(0, 0, 0);
    else
        return *found;
}

/**
 * @brief Поиск количества корней уравнений, которые меньше корня пользователя
 *
 * @tparam T - тип числа
 * @tparam Container - тип контейнера
 * @param user_num - корень пользователя
 * @param container - контейнер, где будем искать
 * @return int - количество корней
 */
template<typename T, class Container>
int findCountOfRootsLowerNum(T* user_num, Container container)
{
    auto user_module = sqrt(user_num[0] * user_num[0] + user_num[1] * user_num[1]);

    return std::count_if(
        container.begin(), container.end(),
        [user_module](QuadraticEquation<T>& eq)
        {
            auto roots = eq.getRoots();

            auto roots_module = sqrt(roots[0][0] * roots[0][0] + roots[0][1] * roots[0][1]);

            return roots_module < user_module;
        }
    )
        + std::count_if(
            container.begin(), container.end(),
            [user_module](QuadraticEquation<T>& eq)
            {
                auto roots = eq.getRoots();

                auto roots_module = sqrt(roots[1][0] * roots[1][0] + roots[1][1] * roots[1][1]);

                return roots_module < user_module;
            }
        );
}
