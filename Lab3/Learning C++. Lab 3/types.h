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

	@param type - тип сортировки
*/
class customCompareByDate
{ // Можно было сделать и структуру
public:
	char type = 0;

	bool operator() (const Person first_person, Person second_person)
	{
		if (type == 'I') // По возрастанию
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
		else // По убыванию
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