#include <iostream>

#include "Library.h"

Library::Library()
{
	int size = rand() % MAX_SIZE + 1;

	for (int i = 0; i < size; i++)
		books[i] = new Book(i);
}

Library::~Library()
{
	for (int i = 0; i < books.size(); i++)
		delete books[i];
	books.clear();
}

int Library::getMaxSize()
{
	return MAX_SIZE;
}

bool Library::isBookAvailable(Book* book)
{
	return book->canBeTaken();
}

Book* Library::findByCriterias(std::string genre, std::string type, int age, int visitor_id, std::vector<int> read_books)
{
	// ПРИОРИТЕТ: возраст > жанр > размер 

	// Поиск по всем 3м критериям (возраст, жанр и тип)
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (age >= it->second->getAge()
			&& genre == it->second->getGenre()
			&& type == it->second->getType()
			&& isBookAvailable(it->second)
			&& std::find(read_books.begin(), read_books.end(), it->second->getID()) == read_books.end())
		{
			return it->second;
		}
	}

	// Поиск по 2м критериям, если не нашли по 3м (возраст и жанр)
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (age >= it->second->getAge()
			&& genre == it->second->getGenre()
			&& isBookAvailable(it->second)
			&& std::find(read_books.begin(), read_books.end(), it->second->getID()) == read_books.end())
		{
			std::cout << "To a visitor (ID): " << visitor_id << " the book was given with different type size: " 
				<< it->second->getType() << "\n";
			return it->second;
		}
	}

	// Поиск по 2м критериям (возраст и размер), если не нашли в предыдущей итерации
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (age >= it->second->getAge()
			&& type == it->second->getType()
			&& isBookAvailable(it->second)
			&& std::find(read_books.begin(), read_books.end(), it->second->getID()) == read_books.end())
		{
			std::cout << "To a visitor (ID): " << visitor_id << " the book was given with different genre: "
				<< it->second->getGenre() << "\n";
			return it->second;
		}
	}

	// Выдаём любую книгу, подходящую под возраст
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (age >= it->second->getAge()
			&& isBookAvailable(it->second)
			&& std::find(read_books.begin(), read_books.end(), it->second->getID()) == read_books.end())
		{
			std::cout << "To a visitor (ID): " << visitor_id << " the book was given with different genre: "
				<< it->second->getGenre() << " and type size : "
				<< it->second->getType() << "\n";
			return it->second;
		}
	}

	std::cout << "NOTHING WAS FOUND!\n";

	// Если ничего не нашли, то nullptr
	return nullptr;
}

Book* Library::giveBook(Book* book)
{
	book->takeIt();
	return book;
}

void Library::returnBook(Book* book, int spent_time)
{
	book->returnIt(spent_time);
}
