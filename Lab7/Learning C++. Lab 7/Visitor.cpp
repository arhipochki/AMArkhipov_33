#include <iostream>

#include "Visitor.h"

Visitor::Visitor() {}

Visitor::Visitor(int id)
	: id(id)
{
	reading_speed = rand() % (90) + 10;

	generatePreferableGenre();
	generatePrerableSize();
	generateName();
	generateAge();
}

Visitor::~Visitor()
{
	current_book = nullptr;
}

void Visitor::generateName()
{
	std::vector<std::string> names;			// Имена
	std::vector<std::string> middle_names;	// Отчества
	std::vector<std::string> surnames;		// Фамилии

	int sex = rand() % 2;

	if (sex)
	{
		names = { "Юлия", "Полина", "Анастасия", "Татьяна" };
		middle_names = { "Ивановна", "Игоревна", "Вячеславовна", "Петровна" };
		surnames = { "Романова", "Марченко", "Солодкова", "Василькова" };
	}
	else
	{
		names = { "Дмитрий", "Владимир", "Никита", "Джо", "Абэ" };
		middle_names = { "Анатольевич", "Владимирович", "Александрович", "Робинетт", "" };
		surnames = { "Медведев", "Путин", "Зелебоба", "Бидон", "Синдзэ" };
	}

	name = std::string(surnames[rand() % surnames.size()] + " "
		+ names[rand() % names.size()] + " "
		+ middle_names[rand() % middle_names.size()]);
}

void Visitor::generateAge()
{
	const int min_age = 7;
	const int max_age = 70;

	age = rand() % (max_age - min_age) + min_age;
}

void Visitor::generatePreferableGenre()
{
	preferable_genre = genres[rand() % genres.size()];
}

void Visitor::generatePrerableSize()
{
	const std::vector<std::string> sizes = { "small", "medium", "large" };

	preferable_size = sizes[rand() % sizes.size()];
}

void Visitor::printInfo()
{
	std::cout << "Visitor ID: " << id << "\n";
	std::cout << "Visitor name: " << name << "\n";
	std::cout << "Visitor age: " << age << "\n";
	std::cout << "Preferable size: " << preferable_size << "\n";
	std::cout << "Preferable genre: " << preferable_genre << "\n";
	std::cout << "Reading speed (pages per hour): " << reading_speed << "\n";
	std::cout << "Current book: ";
	if (current_book != nullptr)
		current_book->printInfo();
	else
		std::cout << "NONE" << "\n";
}

void Visitor::goTakeBook(Library* library)
{
	float change = 1.0f * rand() / RAND_MAX;
	
	// Предпочтения по книге меняются с шансом в 10%
	if (change < 0.1f)
	{
		generatePreferableGenre();
		generatePrerableSize();
	}
	
	Book* found = library->findByCriterias(preferable_genre, preferable_size, age, id, id_books_read);

	if (found != nullptr)
		current_book = library->giveBook(found);
}

void Visitor::rateBook()
{
	int rate = rand() % 10 + 1; // Оцениваем по 10 бальной шкале
	current_book->rateIt(rate);
}

void Visitor::returnBook(Library* library)
{
	id_books_read.push_back(current_book->getID());
	rateBook();
	library->returnBook(current_book, spent_time);

	read_pages = 0;
	spent_time = 0;
	current_book = nullptr;
}

void Visitor::readBook(float read_for, Library* library)
{
	if (current_book != nullptr)
	{
		int read_part = read_for * reading_speed;
		if (read_pages + read_part > current_book->getPages())
			read_pages += abs(read_pages - current_book->getPages()); // Считаем только оставшиеся страницы
		else
			read_pages += read_part;

		spent_time += read_for;

		if (read_pages >= current_book->getPages())
		{
			std::cout << "Visitor " << id << " has finished reading a book with id: " << current_book->getID() << "\n";
			this->returnBook(library);
		}
	}
}

bool Visitor::isReading()
{
	if (current_book == nullptr)
		return false;
	return true;
}
