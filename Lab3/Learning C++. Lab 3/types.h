#pragma once

#include <string>

/*
	������������ ����: 0 - �������, 1 - �������
*/
enum class Sex { MALE, FEMALE };

/*
	������������ �������, ������� � 1
*/
enum class Month { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
			 JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

/*
	��������� ����.

	@param day - ����
	@param month - ����� �� ������������ Month
	@param year - ���
*/
struct BirthDate {
	int day;
	Month month;
	int year;
};

/*
	��������� ��������.

	@param name - ���.
	@param sex - ���
	@param birth_date - ��������� ��� ��������
*/
struct Person {
	std::string name;
	Sex sex;
	BirthDate birth_date;
};


/*
	����� ��� ������������� � ����������

	@param type - ��� ����������
*/
class customCompareByDate
{ // ����� ���� ������� � ���������
public:
	char type = 0;

	bool operator() (const Person first_person, Person second_person)
	{
		if (type == 'I') // �� �����������
		{
			if (first_person.birth_date.year < second_person.birth_date.year) // ������� ���������� �� �����
				return true;
			else if ((int)first_person.birth_date.month < (int)second_person.birth_date.month // ���������� �� �������, ���� ��������� ����
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;
			else if (first_person.birth_date.day < second_person.birth_date.day // ������� ���������� �� ���, ���� ��������� ������ � ����
				&& first_person.birth_date.month == second_person.birth_date.month
				&& first_person.birth_date.year == second_person.birth_date.year)
				return true;

			return false;
		}
		else // �� ��������
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