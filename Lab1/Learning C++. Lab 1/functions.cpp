#include "functions.h"

#include <string>
#include <ctime>

std::string generate_string(const int len)
{
	std::string result;
	result.reserve(len);

	for (int i = 0; i < len; i++)
		result += alphabet[rand() % (alphabet.length() - 1)];

	return result;
}
