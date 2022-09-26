#include "functions.h"

#include <string>

std::string generateString(const int len)
{
	std::string result;
	result.reserve(len);

	for (int i = 0; i < len; i++)
		result += alphabet[rand() % (alphabet.length() - 1)];

	return result;
}