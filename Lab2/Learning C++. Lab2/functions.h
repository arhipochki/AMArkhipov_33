#pragma once

/*
	������ ��������� ������

	@param arr - ��������� �� ��������� ������, ������� ����� ������
	@param rows - ���������� ����� �������
	@param cols - ���������� �������� �������
	@return ���������� ��������� �� �������� ������
*/
int** createArray(int rows, int cols);

/*
	������� ������
	
	@param arr - ��������� �� ��������� ������, ������� ����� ������
	@param rows - ���������� �����
*/
void freeArray(int** arr, int rows);

/*
	��������� ������ ���������� �� 1 �� rows * cols

	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fillArray(int** arr, int rows, int cols);

/*
*	������� ������
* 
*	@param arr - ��������� �� ��������� ������, ������� ���� �������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void printArray(int** arr, int rows, int cols);

/*
*	��������� ������ �� rows * cols �� 1
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fillArrayBackward(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ����� ������� ���������
*	
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fillArrayAlongMainDiag(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ����� �������� ���������
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fillArrayAlongSideDiag(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ��������
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fillArraySpiral(int** arr, int rows, int cols);