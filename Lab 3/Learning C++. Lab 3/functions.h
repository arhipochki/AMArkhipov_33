#pragma once

#include "structures.h"

/*
	Заполняет массив работников сгенерированными людьми

	@param employees - ссылка на массив с работниками
	@param size - количество пользователей
*/
void generateEmployees(Person* employees, int size);

/*
	Генерирует дату рождения (день, месяц, год) до 70 лет включительно

	@return Возвращает сгенерированную структуру BirthDate
*/
BirthDate generateBirthDate();

/*
	Создаёт случаное ФИО

	@param sex - пол человека
	@return Строка с ФИО
*/
std::string generateName(Sex sex);

/*
	Создаёт случайного человека

	@return Возвращает структуру человека
*/
Person generatePerson();

/*
	Заполняет массив работников введёными людьми пользователем

	@param employees - ссылка на массив с работниками
	@param size - количество пользователей
*/
void fillEmployees(Person* employees, int size);

/*
	Выводит всех работников

	@param employees - ссылка на массив с работниками
	@param size - количество пользователей
*/
void printEmployees(Person* employees, int size);

/*
	Выводит информацию о работнике

	@param person - структура Person, информация с которой будет выведена на экран
*/
void printPersonInfo(Person person);

/*
	Поиск работника по фамилии

	@param employees - массив, где будем искать
	@param name - ФИО, по которому будем искать
	@return Возвращает указатель на структуру Person со всеми данными
*/
Person* searchByName(std::string name, Person* employees, int size);

/*
	Формирует срез рабочих по году (больше или меньше заданного года)

	@param year - год, по которому будет делаться срез
	@param type - тип среза (меньше или больше года)
	@param employees - массив рабочих
	@param size - размер массива
*/
void formCrossSectionByYearOfBirth(int year, char type, Person* employees, int size);

/*
	Выводим статистику всех работников определённого пола

	@param sex - пол
	@param employees - массив работников
	@param size - размер массива
*/
void employeesStatisticsBySex(Sex sex, Person* employees, int size);

/*
	Сортирует массив работников по возрастанию или убыванию даты рождения
*/
void sortByAge(char type, Person* employees, int size);