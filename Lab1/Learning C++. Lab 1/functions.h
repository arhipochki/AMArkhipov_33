#pragma once

#include <string>

/*
	�������� �������, ������� ������������ ��� ��������� ������
*/
const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz");

/*
* ��������� ������, ��������� �� ���� ����������� �������� (� ������ ��������)
*
* @param len - ����� ������
* @return ��������������� ������
**/
std::string generateString(const int len);