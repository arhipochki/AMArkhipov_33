#pragma once

#include "types.h"

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
	@param found_count - указатель, куда будет сохранено количество найденных пользоватлей
	@return Возвращает массив найденных людей по ФИО
*/
Person* searchByName(std::string name, Person* employees, int size, int* found_count);

/*
	Формирует срез рабочих по году (больше или меньше заданного года)

	@param year - год, по которому будет делаться срез
	@param type - тип среза (меньше или больше года)
	@param employees - массив рабочих
	@param size - размер массива
	@param found_count - указатель, куда будет сохранено количество найденных пользоватлей
	@return Возвращает срез людей по году (больше или меньше опеределённого года)
*/
Person* formCrossSectionByYearOfBirth(int year, char type, Person* employees, int size, int* found_count);

/*
	Выводим статистику всех работников определённого пола

	@param sex - пол
	@param employees - массив работников
	@param size - размер массива
	@param found_count - указатель, куда будет сохранено количество найденных пользоватлей
	@return Возвращает статистику людей определённого пола
*/
Person* employeesStatisticsBySex(Sex sex, Person* employees, int size, int* found_count);

/*
	Сортирует массив работников по возрастанию или убыванию даты рождения

	@param type - тип сортировки 
	@param employees - массив работников, который будем сортировать
	@param size - размер сортируемого массива
*/
void sortByAge(char type, Person* employees, int size);