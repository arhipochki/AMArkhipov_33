#pragma once

/*
	������ ��������� ������
	@param arr - ��������� �� ��������� ������, ������� ����� ������
	@param rows - ���������� ����� �������
	@param cols - ���������� �������� �������
	@return ���������� ��������� �� �������� ������
*/
int** create_array(int rows, int cols);

/*
	������� ������
	@param arr - ��������� �� ��������� ������, ������� ����� ������
	@param rows - ���������� �����
*/
void free_array(int** arr, int rows);

/*
	��������� ������ ���������� �� 1 �� rows * cols

	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fill_array(int** arr, int rows, int cols);

/*
*	������� ������
* 
*	@param arr - ��������� �� ��������� ������, ������� ���� �������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void print_array(int** arr, int rows, int cols);

/*
*	��������� ������ �� rows * cols �� 1
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fill_array_backward(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ����� ������� ���������
*	
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fill_array_along_main_diag(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ����� �������� ���������
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fill_array_along_side_diag(int** arr, int rows, int cols);

/*
*	��������� ������ �� 1 �� rows * cols ��������
*
*	@param arr - ��������� �� ��������� ������, ������� ���� ���������
	@param rows - ���������� �����
	@param cols - ���������� ��������
*/
void fill_array_spiral(int** arr, int rows, int cols);