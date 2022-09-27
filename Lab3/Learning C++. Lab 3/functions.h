#pragma once

#include "types.h"

/*
	��������� ������ ���������� ���������������� ������

	@param employees - ������ �� ������ � �����������
	@param size - ���������� �������������
*/
void generateEmployees(Person* employees, int size);

/*
	���������� ���� �������� (����, �����, ���) �� 70 ��� ������������

	@return ���������� ��������������� ��������� BirthDate
*/
BirthDate generateBirthDate();

/*
	������ �������� ���

	@param sex - ��� ��������
	@return ������ � ���
*/
std::string generateName(Sex sex);

/*
	������ ���������� ��������

	@return ���������� ��������� ��������
*/
Person generatePerson();

/*
	��������� ������ ���������� �������� ������ �������������

	@param employees - ������ �� ������ � �����������
	@param size - ���������� �������������
*/
void fillEmployees(Person* employees, int size);

/*
	������� ���� ����������

	@param employees - ������ �� ������ � �����������
	@param size - ���������� �������������
*/
void printEmployees(Person* employees, int size);

/*
	������� ���������� � ���������

	@param person - ��������� Person, ���������� � ������� ����� �������� �� �����
*/
void printPersonInfo(Person person);

/*
	����� ��������� �� �������

	@param employees - ������, ��� ����� ������
	@param name - ���, �� �������� ����� ������
	@param found_count - ���������, ���� ����� ��������� ���������� ��������� ������������
	@return ���������� ������ ��������� ����� �� ���
*/
Person* searchByName(std::string name, Person* employees, int size, int* found_count);

/*
	��������� ���� ������� �� ���� (������ ��� ������ ��������� ����)

	@param year - ���, �� �������� ����� �������� ����
	@param type - ��� ����� (������ ��� ������ ����)
	@param employees - ������ �������
	@param size - ������ �������
	@param found_count - ���������, ���� ����� ��������� ���������� ��������� ������������
	@return ���������� ���� ����� �� ���� (������ ��� ������ ������������� ����)
*/
Person* formCrossSectionByYearOfBirth(int year, char type, Person* employees, int size, int* found_count);

/*
	������� ���������� ���� ���������� ������������ ����

	@param sex - ���
	@param employees - ������ ����������
	@param size - ������ �������
	@param found_count - ���������, ���� ����� ��������� ���������� ��������� ������������
	@return ���������� ���������� ����� ������������ ����
*/
Person* employeesStatisticsBySex(Sex sex, Person* employees, int size, int* found_count);

/*
	��������� ������ ���������� �� ����������� ��� �������� ���� ��������

	@param type - ��� ���������� 
	@param employees - ������ ����������, ������� ����� �����������
	@param size - ������ ������������ �������
*/
void sortByAge(char type, Person* employees, int size);