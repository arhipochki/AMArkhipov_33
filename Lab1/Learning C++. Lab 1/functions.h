#pragma once

#include <string>

const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz");

/*
* Генерация строки, состоящая из букв английского алфавита (в нижнем регистре)
*
* @param len длина строки
* @return result сгенерированная строка
**/
std::string generate_string(const int len);