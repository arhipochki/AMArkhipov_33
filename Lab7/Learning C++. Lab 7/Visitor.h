#pragma once

#include "Library.h"

/*
	Класс посетителя.

	@param id - id посетителя
	@param age - возраст посетителя
	@param preferable_size - предпочитаемый размер книги (кол-во страниц)
	@param preferable_genre - предпочитаемый жанр
	@param name - имя посетителя
	@param reading_speed - скорость чтения (страницы в час)
	@param id_books_read - массив прочитанных книг (по id книги)
	@param current_book - текущая книга у поситителя
	@param read_pages - прочитанное количество страниц относительно текущей книги
	@param spent_time - затраченное время на чтение текущей книги
*/
class Visitor
{
private:
	int id = 0;
	int age = 0;

	std::string preferable_size;	// small (<100), medium (100 <= x <= 500), large (>500)
	std::string preferable_genre;
	std::string name;

	int reading_speed = 0;

	std::vector<int> id_books_read;
	Book* current_book = nullptr;

	int read_pages = 0;
	int spent_time = 0;

	// Генерация имени посетителя
	void generateName();

	// Генерация возраста
	void generateAge();
public:

	// Пустой конструктор
	Visitor();

	/*
		Основной конструктор

		@param id - id посетителя
	*/
	Visitor(int id);

	// Деструктор
	~Visitor();

	// Вывод информации о посетителе
	void printInfo();

	// Генерация предпочитаемого жанра
	void generatePreferableGenre();

	// Генерация предпочитаемого размера книги
	void generatePrerableSize();

	/*
		Взять книгу из библиотеки

		@param library - из какой библиотеки надо взять книгу
		@param book - книга, которую хотим взять
	*/
	void goTakeBook(Library* library);

	/*
		Оцениваем книгу
	*/
	void rateBook();

	/*
		Вернуть книгу в библиотеку
		@param library - в какую библиотеку надо вернуть книгу
	*/
	void returnBook(Library* libraryok);

	/*
		Метод чтения книги
	
		@param read_for - сколько времени читать
		@param library - если дочитали, вернуть книгу в библиотеку
	*/
	void readBook(float read_for, Library* library);

	/*
		Метод проверки наличия книги

		@return false - если current_book == nullptr, иначе true
	*/
	bool isReading();
};