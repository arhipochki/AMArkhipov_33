#pragma once

#include <string>

/*
	Перечисление пола: 0 - мужчина, 1 - женщина
*/
enum class Sex { MALE, FEMALE };

/*
	Перечисление месяцев, начиная с 1
*/
enum class Month { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
			 JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

/*
	Структура даты.

	@param day - день
	@param month - месяц из перечисления Month
	@param year - год
*/
struct BirthDate {
	int day;
	Month month;
	int year;
};

/*
	Структура человека.

	@param name - ФИО.
	@param sex - пол
	@param birth_date - структура дня рождения
*/
struct Person {
	std::string name;
	Sex sex;
	BirthDate birth_date;
};


/*
	Класс для использования в сортировке

	@param m_type - тип сортировки
*/
class customCompareByDate
{ // Можно было сделать и структуру
public:
	char m_type = 0;

	bool operator() (const Person first_person, Person second_person)
	{
		if (m_type == 'I') // По увеличению
		{
			if (first_person.birth_date.year < second_person.birth_date.year) // Сначала сравниваем по годам
				return true;
			else if ((int)first_person.birth_date.month < (int)second_person.birth_date.month // Сравниваем по месяцам, если одинакова года
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;
			else if (first_person.birth_date.day < second_person.birth_date.day // Сначала сравниваем по дня, если одинаковы месяцы и года
				&& first_person.birth_date.month == second_person.birth_date.month
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;

			return false;
		}
		else
		{
			if (first_person.birth_date.year > second_person.birth_date.year)
				return true;
			else if ((int)first_person.birth_date.month > (int)second_person.birth_date.month
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;
			else if (first_person.birth_date.day > second_person.birth_date.day
				&& first_person.birth_date.month == second_person.birth_date.month
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;

			return false;
		}
	}
};