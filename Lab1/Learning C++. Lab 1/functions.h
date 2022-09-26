#pragma once

#include <string>

/*
	Основной алфавит, который используется для генерации строки
*/
const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz");

/*
* Генерация строки, состоящая из букв английского алфавита (в нижнем регистре)
*
* @param len - длина строки
* @return Сгенерированная строка
**/
std::string generateString(const int len);