#include "functions.h"

#include <cmath>
#include <iostream>
#include <iomanip>

int** createArray(int rows, int cols)
{
	int **arr = new int* [rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new int[cols];

	return arr;
}

void freeArray(int** arr, int rows)
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];

	delete[] arr;
}

void fillArray(int** arr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr[i][j] = rows * i + j + 1;
}

void printArray(int** arr, int rows, int cols)
{
	int width = (int)log10(rows * cols) + 2; // Длина ячеек (с учётом пробела)
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << std::setw(width) << arr[i][j];
		std::cout << "\n";
	}
}

void fillArrayBackward(int** arr, int rows, int cols)
{
	int value = rows * cols;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr[i][j] = value--;
}

void fillArrayAlongMainDiag(int** arr, int rows, int cols)
{
	int i = 0, j = 0, col = 0, line = 0;
	int value = 1;

	while (true)
	{
		/*
			Заполняем ячейки по диагонали
			1 0 => 1 2 => 1 2
			0 0    3 0    3 4
		*/ 		
		while (i < rows && j > -1)
		{
			arr[i][j] = value++;
			i++; j--;
		}

		i = line;
		j = ++col;

		// Если дошли до последнего стобца, то начинаем с последнего столбца и новой строчки
		if (j >= cols - 1)
		{
			col = cols - 1;
			j = col;
			line++;
		}

		// Если дошли до правой нижней ячейки - выходим
		if (i == (rows - 1) && j == (cols - 1))
			break;
	}

	// Выставляем значение последней ячейки
	arr[rows - 1][cols - 1] = rows * cols;
}

void fillArrayAlongSideDiag(int** arr, int rows, int cols)
{
	int i = rows - 1, j = 0, col = 0, line = rows - 1;
	int value = 1;

	while (true)
	{
		/*
			Заполняем ячейки по диагонали
			0 0 => 2 0 => 2 0
			1 0    1 3    1 3
		*/
		while (i < rows && j < cols)
		{
			arr[i][j] = value++;
			i++; j++;
		}

		i = --line;
		j = col;

		// Если вышли за первую строку, то выставляем первую строку и начинаем со следующего столбца
		if (i <= 0)
		{
			line = 0;
			i = line;
			col++;
		}

		// Если дошли до правого верхнего угла - выходим
		if (i == (0) && j == (cols - 1))
			break;
	}

	arr[0][cols - 1] = rows * cols;
}

void fillArraySpiral(int** arr, int rows, int cols)
{
	int i = 0, j = 0,
		t_rows = rows,
		t_cols = cols,
		next_row = 1,
		next_col = 0;

	int value = 1;

	while (true)
	{
		// Заполняем все ячейки в строке
		for (j = next_col; j < t_cols; j++)
			arr[i][j] = value++;
		j--; // Учитываем принцип работы цикла for, значение становится на 1 меньше или больше взависимости от пути

		// Заполняем все ячейки в стобце
		for (i = next_row; i < t_rows; i++)
			arr[i][j] = value++;
		i--;

		t_cols--; // Уменьшаем количесвто столбцов, которые предстоит заполнить
		for (j = t_cols - 1; j > next_col - 1; j--)
			arr[i][j] = value++;
		j++;

		t_rows--; // Уменьшаем количесвто строк, которые предстоит заполнить
		for (i = t_rows - 1; i > next_row - 1; i--)
			arr[i][j] = value++;
		i++;

		// Сдвигаем старт заполнения 
		next_col++;
		next_row++;

		// Если дошли до центра (последнего числа) - выходим
		if (t_rows == (int)(rows / 2) && t_cols == (int)floor(cols / 2))
			break;
	}
}