#pragma once

#include <string>

const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz");

/*
* ��������� ������, ��������� �� ���� ����������� �������� (� ������ ��������)
*
* @param len ����� ������
* @return result ��������������� ������
**/
std::string generate_string(const int len);