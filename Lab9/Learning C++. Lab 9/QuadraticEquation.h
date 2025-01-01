#pragma once

#include <cmath>
#include <iostream>
#include <string>

// Округляем до тысячных
const int ROUND_TO = 1000;

/**
 * @brief Класс квадратного уравнения
 *
 * Класс квадратного уравнения предусматривает собой комплексное уравнение,
 * где по умолчанию мнимая часть равна 0.
 *
 * @tparam T - тип значений квадратного корня
 * @tparam TEnabled - параметр, который предусматривает, чтобы передаваемый тип был арифметическим (численным)
 * @param is_complex - будут ли у корней мнимые части
 * @param no_roots - будут ли у корни у уравнение (исключаем деление на 0, все корни равны 0, не решается методом дискрименанта)
 * @param a - коэфициент a
 * @param b - коэфициент b
 * @param c - коэфициент c
 * @param roots - корни уравнения (двумерный массив, где два корня содержат действительную и мнимые части)
 */
template <
    typename T,
    typename TEnabled = typename std::enable_if_t<std::is_arithmetic<T>::value, T>
>
class QuadraticEquation {
private:
    bool is_complex = false;
    bool no_roots = false;

    T a;
    T b;
    T c;

    T roots[2][2];
public:

    /**
     * @brief Основной конструктор
     *
     * @param a - коэфициент a
     * @param b - коэфициент b
     * @param c - коэфициент c
     */
    QuadraticEquation(T a, T b, T c)
        : a(a), b(b), c(c)
    {
        // Исключаем деление на 0
        if (a == 0)
        {
            roots[0][0] = 0; roots[1][0] = 0;
            no_roots = true;

            return;
        }

        T d = b * b - 4 * a * c;

        if (d < 0)
        {
            is_complex = true;
            d *= -1;

            T d_root = sqrt(d);

            roots[0][0] = roots[1][0] = round((-b) / (2 * a) * ROUND_TO) / ROUND_TO;

            roots[0][1] = round((d_root) / (2 * a) * ROUND_TO) / ROUND_TO;
            roots[1][1] = round((-d_root) / (2 * a) * ROUND_TO) / ROUND_TO;
        }
        else
        {
            T d_root = sqrt(d);

            roots[0][1] = roots[1][1] = 0;

            roots[0][0] = round((-b + d_root) / (2 * a) * ROUND_TO) / ROUND_TO;
            roots[1][0] = round((-b - d_root) / (2 * a) * ROUND_TO) / ROUND_TO;
        }
    }

    /**
     * @brief Получить коэф. а
     *
     * @return a
     */
    T getCoefA()   const { return a; }

    /**
     * @brief Получить коэф. и
     *
     * @return b
     */
    T getCoefB()   const { return b; }

    /**
     * @brief Получить коэф. с
     *
     * @return с
     */
    T getCoefC()   const { return c; }
    
    /**
     * @brief Получаем сумму модулей корней
     *
     * @return result
     */
    T getRootsModuleSum() const {
        return
            sqrt(roots[0][0] * roots[0][0] + roots[0][1] * roots[0][1]) +
            sqrt(roots[1][0] * roots[1][0] + roots[1][1] * roots[1][1]);
    }

    /**
     * @brief Получаем корни
     *
     * @return T(*)[2] - возвращает массив из 2-х указателей на корни (которые так же являются массивом [2])
     */
    T (*getRoots())[2] { return roots; }

        /**
         * @brief Комплексное ли число
         *
         * @return is_complex
         */
    bool isComplex() const { return is_complex; }

    /**
     * @brief Пустое ли уравнение
     *
     * @return true - если все коэф-ты 0, иначе false
     */
    bool isEmpty()   const { return (a == 0 && b == 0 && c == 0); }

    // Перегрузка оператора равно. Сравниваем по равенству коэфициентов
    friend bool operator==(const QuadraticEquation<T>& a, const QuadraticEquation<T>& b)
    {
        return (a.getCoefA() == b.getCoefA() &&
            a.getCoefB() == b.getCoefB() &&
            a.getCoefC() == b.getCoefC());
    }

    // Перегрузка оператора не равно. Сравниваем по равенству коэфициентов
    friend bool operator!=(const QuadraticEquation<T>& a, const QuadraticEquation<T>& b)
    {
        return (a.getCoefA() != b.getCoefA() ||
            a.getCoefB() != b.getCoefB() ||
            a.getCoefC() != b.getCoefC());
    }

    // Перегрузка оператора меньше. Сравниваем по сумме модулей корней
    friend bool operator<(const QuadraticEquation<T>& a, const QuadraticEquation<T>& b)
    {
        return (a.getRootsModuleSum() < b.getRootsModuleSum());
    }

    // Перегрузка оператора больше. Сравниваем по сумме модулей корней
    friend bool operator>(const QuadraticEquation<T>& a, const QuadraticEquation<T>& b)
    {
        return (a.getRootsModuleSum() > b.getRootsModuleSum());
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& stream, QuadraticEquation<T> eq)
    {
        if (eq.a == 0)
            stream << "";
        else if (eq.a == 1)
            stream << "x^2";
        else if (eq.a == -1)
            stream << "-x^2";
        else
            stream << eq.a << "x^2";

        if (eq.b == 0)
            stream << "";
        else if (eq.b == 1 && eq.a)
            stream << "+x";
        else if (eq.b == 1)
            stream << "x";
        else if (eq.b == -1)
            stream << "-x";
        else if (eq.b != 1 && eq.b > 0 && eq.a)
            stream << "+" << eq.b << "x";
        else
            stream << eq.b << "x";

        if (eq.c == 0)
            stream << "";
        else if (eq.c > 0 && eq.a || eq.c > 0 && eq.b)
            stream << "+" << eq.c;
        else
            stream << eq.c;

        if (eq.no_roots)
            stream << "\nEquation not quadratic! Can't be solved with discriminant!\n";
        else
        {
            if (eq.is_complex)
            {
                stream << "\nComplex Roots: " << eq.roots[0][0];
                stream << (eq.roots[0][1] > 0 ? "+" : "") << eq.roots[0][1] << "i, ";
                stream << eq.roots[1][0];
                stream << (eq.roots[1][1] > 0 ? "+" : "") << eq.roots[1][1] << "i\n";
            }
            else
                stream << "\nRoots: " << eq.roots[0][0] << ", " << eq.roots[1][0] << "\n";
        }

        return stream;
    }
};
