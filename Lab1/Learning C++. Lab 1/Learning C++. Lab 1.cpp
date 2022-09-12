#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "functions.h"

int main()
{
	const int LEN = 1000;

	std::string hidden_string = generate_string(LEN);

	std::string guessed_string;			// Строка, в которой будем отгадывать
	guessed_string.reserve(LEN);

	int total_iter_count = 0;			// Количество итераций по отгадыванию строки
	int max_symbol_guess_count = 0;		// Максимальное количество итераций на один символ
	int idx = 0;						// Какой символ (индекс в строке) так долго отгадывали

	for (auto symbol : hidden_string)
	{
		system("cls");
		int cur_symbol_guess_count = 0;

		std::vector<char> cpy_alphabet(alphabet.c_str(), alphabet.c_str() + alphabet.length() + 1);

		while (true)
		{
			int pos = rand() % (cpy_alphabet.size() - 1);
			char letter = cpy_alphabet[pos];
			cpy_alphabet.erase(cpy_alphabet.begin() + pos);

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