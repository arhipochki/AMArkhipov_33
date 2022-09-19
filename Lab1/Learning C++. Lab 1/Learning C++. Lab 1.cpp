#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "functions.h"

/*
Вариант 3. Требуется написать программу, которая генерирует строку состоящую из 1000 случайных символов английского алфавита. 
Требуется реализовать игру в угадай слово, когда программа пытается подобрать аналогичную строку посимвольно, 
при этом угадываются символы только последовательно. По итогу, нужно подсчитать и вывести сколько потребовалось итераций на подбор строки, 
и максимальное количество попыток угадать один символ.
*/
int main()
{
	srand(time(NULL));

	const int LEN = 1000;

	std::string hidden_string = generate_string(LEN); // Загадываем строку

	std::string guessed_string;			// Строка, в которой будем отгадывать
	guessed_string.reserve(LEN);		// Выставляем длину строки

	int total_iter_count = 0;			// Количество итераций по отгадыванию строки
	int max_symbol_guess_count = 0;		// Максимальное количество итераций на один символ
	int idx = 0;						// Какой символ (индекс в строке) так долго отгадывали

	for (auto symbol : hidden_string)
	{
		system("cls");
		int cur_symbol_guess_count = 0;	 // Текущее количество попыток отгадывания символа

		std::vector<char> cpy_alphabet(alphabet.c_str(), alphabet.c_str() + alphabet.length()); // Массив символов 

		while (true)
		{
			int pos = rand() % (cpy_alphabet.size());	// Генерируем индекс символа
			char letter = cpy_alphabet[pos];			// Выбираем букву по индексу
			cpy_alphabet.erase(cpy_alphabet.begin() + pos);	// Убираем букву из массива, чтобы снова её не брать

			cur_symbol_guess_count++;
			total_iter_count++;

			if (letter == symbol)
			{
				if (cur_symbol_guess_count > max_symbol_guess_count)
					max_symbol_guess_count = cur_symbol_guess_count;

				guessed_string += letter;

				break;
			}
		}

		std::cout << "Guessed string: " << guessed_string << "\n";
		Sleep(1);
	}

	std::cout << "Hidden string: " << hidden_string << "\n";

	std::cout << "Total iterations: " << total_iter_count << "\n";
	std::cout << "Max iter count on guess one symbol: " << max_symbol_guess_count << "\n";

	return 0;
}
