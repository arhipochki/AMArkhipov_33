#include <iostream>

#include "Book.h"
#include "Genres.h"

Book::Book() {}

Book::Book(int id)
	: id(id)
{
	count = rand() % max_books_count + 1;

	generateAuthor();
	generateBookName();
	generateGenre();
	generatePages();
	generateAge();
}

Book::~Book() {}

void Book::generateAuthor()
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
		names = { "Иосиф", "Владимир", "Никита", "Юрий", "Константин" };
		middle_names = { "Виссарионович", "Ильич", "Сергеевич", "Владимирович", "Устинович" };
		surnames = { "Сталин", "Ленин", "Хрущёв", "Андропов", "Черненко" };
	}

	author = std::string(surnames[rand() % surnames.size()] + " "
		+ names[rand() % names.size()] + " "
		+ middle_names[rand() % middle_names.size()]);
}

void Book::generateBookName()
{
	std::vector<std::string> first_part = {
		"Приключения", "Приключение", "Мир", "История", "Истории", "Дни"
	};
	
	std::vector<std::string> second_part = {
		"Негров", "Гарри Шпроттера", "Элли", "Врунгеля", "Гаца", "Дэндзи", "Лиллии", "KSI"
	};

	std::vector<std::string> third_part = {
		"в забытых мирах", "в космосе", "на необитаемом острове", "в подвалах Питера", "на столе у хирурга", "и PRIME'овый запой"
	};

	book_name = first_part[rand() % first_part.size()] + " "
				+ second_part[rand() % second_part.size()] + " "
				+ third_part[rand() % third_part.size()];
}

void Book::generateGenre()
{
	genre = genres[rand() % genres.size()];
}

void Book::generatePages()
{
	const int max_pages = 2000;
	const int min_pages = 50;

	pages = rand() % (max_pages - min_pages) + min_pages;

	if (pages < 100)
		type = "small";
	else if (pages < 500)
		type = "medium";
	else
		type = "large";
}

void Book::generateAge()
{
	std::vector<int> ages = { 0, 3, 6, 12, 16, 18 };

	min_age = ages[rand() % ages.size()];
}

void Book::printInfo()
{
	std::cout << "\nBook ID: " << id << "\n";
	std::cout << "Book name: " << book_name << "\n";
	std::cout << "Books count: " << count << "\n";
	std::cout << "Book was taken: " << count_of_uses << " times\n";
	std::cout << "Author: " << author << "\n";
	std::cout << "Genre: " << genre << "\n";
	std::cout << "Pages: " << pages << "\n";
	std::cout << "Min age: " << min_age << "\n";
	std::cout << "Total rating: " << total_rating << "\n";
	std::cout << "Total read time: " << total_time << " hrs\n";
	std::cout << "Avg read time: " << avg_time << " hrs\n";
}

bool Book::canBeTaken()
{
	return count > 0;
}

void Book::takeIt()
{
	std::cout << id << " count " << count << "\n";

	count_of_uses++;
	count--;
}

void Book::returnIt(int spent_time)
{
	total_time += spent_time;

	count++;
}

void Book::rateIt(int rate)
{
	ratings.push_back(rate);
}

void Book::calculateResults()
{
	total_rating = 0.0f;

	if (!ratings.empty())
	{
		for (auto& rate : ratings)
		{
			total_rating += rate;
		}

		total_rating /= ratings.size();
	
		avg_time = total_time / ratings.size();
	}
}

std::string Book::getGenre()
{
	return genre;
}

std::string Book::getType()
{
	return type;
}

std::string Book::getName()
{
	return book_name;
}

std::string Book::getAuthor()
{
	return author;
}

int Book::getAge()
{
	return min_age;
}

int Book::getPages()
{
	return pages;
}

int Book::getID()
{
	return id;
}

int Book::getCountOfUse()
{
	return count_of_uses;
}