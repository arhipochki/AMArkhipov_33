#pragma once

#include <map>

#include "Book.h"

/*
	Класс библиотеки.

	@param MAX_SIZE - макисмальное количество книг в библиотеке
	@param books - словрь книг (привязка id и объект Book)
*/
class Library
{
private:
	const int MAX_SIZE = 30;

public:
	std::map<int, Book*> books;

	// Конструктор
	Library();

	// Деструктор
	~Library();

	/*
		Получение максимального количества книг в библиотеке

		@return MAX_SIZE - максимальное количество книг
	*/
	int getMaxSize();

	/*
		Доступна ли книга для чтения

		@param book - какую книгу хочет взять посетитель
		@return true - если да, иначе false
	*/
	bool isBookAvailable(Book* book);

	/*
		Поиск книги по критериям
		
		@param genre - жанр, подбираемой книги
		@param type - тип размера книги
		@param visitor - id посетителя
		@param read_books - прочитанные книги посетителя
		@return result - подобранная по критериям книга
	*/
	Book* findByCriterias(std::string genre, std::string type, int age, int visitor_id, std::vector<int> read_books);

	/*
		Выдать книгу посетитлю

		@param book - какую книгу выдать
		@return указатель на выбранную книгу
	*/
	Book* giveBook(Book* book);

	/*
	* Вернуть книгу
	* @param book - указатель на книгу, которую надо вернуть
	* @param spent_time - затраченное время на прочтение книги
	*/
	void returnBook(Book* book, int spent_time);
};

