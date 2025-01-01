#pragma once

#include "Genres.h"

/*
	Класс книги.

	@param id - идентификатор книги
	@param pages - количество страниц в книге
	@param min_age - минимальный возраст для доступа к книге
	@param count - количество экземпляров книг
	@param count_of_uses - сколько раз брали данное произведение
	@param total_time - суммарное время чтение книги
	@param total_rating - итоговая оценка книги (считается из ratings)
	@param avg_time - среднее время чтение книги (считается из total_time / количество оценок)
	@param book_name - название книги
	@param genre - жанр книги
	@param author - автор книги
	@param type - тип/размер книги (большая, средняя, маленькая)
	@param ratings - массив оценок книги
*/
class Book
{
private:
	const int max_books_count = 10;

	int id = 0;
	int pages = 0;
	int min_age = 0;
	int count = 0;
	int count_of_uses = 0;
	int total_time = 0;

	float total_rating = 0.0f;
	float avg_time = 0.0f;

	std::string book_name;
	std::string genre;
	std::string author;

	std::string type;

	std::vector<float> ratings;
public:

	// Пустой конструктор
	Book();

	/*
		Основной конструктор

		@param id - номер книги
	*/
	Book(int id);

	// Деструктор
	~Book();

	/*
		Генерация автора
	*/
	void generateAuthor();

	/*
		Генерация названия книги
	*/
	void generateBookName();

	/*
		Генерация жанра книги
	*/
	void generateGenre();

	/*
		Генерация страниц
	*/
	void generatePages();

	/*
		Герация возраста
	*/
	void generateAge();

	/*
		Вывод информации о книге
	*/
	void printInfo();

	/*
		Можно ли взять книгу

		@return count - если колиество <= 0 - false, иначе true
	*/
	bool canBeTaken();

	/*
		Взять книгу
	*/
	void takeIt();

	/*
		Вернуть книгу

		@param spent_time - время, затраченное на её чтение
	*/
	void returnIt(int spent_time);

	/*
		Добавление оценки книге

		@param rate - оценка
	*/
	void rateIt(int rate);
	
	/*
		Подсчитать итоговый рейтинг
	*/
	void calculateResults();

	/*
		Получить жанр книги

		@return genre - жанр
	*/
	std::string getGenre();

	/*
		Получить тип размера книги

		@return type - тип книги
	*/
	std::string getType();

	/*
		Получить название книги

		@return name - название книги
	*/
	std::string getName();

	/*
		Получить автора книги

		@return author - автор книги 
	*/
	std::string getAuthor();

	/*
		Получить возрастную категорию книги

		@return min_age - возрастная категория книги
	*/
	int getAge();

	/*
		Получить количество страниц

		@return pages - количество страниц
	*/
	int getPages();

	/*
		Получить id 

		@return id - номер книги
	*/
	int getID();

	/*
		Получить количество взятий книги

		@return count_of_uses - количество взятий
	*/
	int getCountOfUse();
};