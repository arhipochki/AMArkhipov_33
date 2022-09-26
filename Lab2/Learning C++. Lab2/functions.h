#pragma once

/*
	—оздаЄт двумерный массив

	@param arr - указатель на двумерный массив, который будет создан
	@param rows - количество строк массива
	@param cols - количество столбцов массива
	@return ¬озвращает указатель на созданый массив
*/
int** createArray(int rows, int cols);

/*
	ќчищает массив
	
	@param arr - указатель на двумерный массив, который будет очищен
	@param rows - количество строк
*/
void freeArray(int** arr, int rows);

/*
	«аполн€ет массив элементами от 1 до rows * cols

	@param arr - указатель на двумерный массив, который надо заполнить
	@param rows - количество строк
	@param cols - количество столбцов
*/
void fillArray(int** arr, int rows, int cols);

/*
*	¬ыводит массив
* 
*	@param arr - указатель на двумерный массив, который надо вывести
	@param rows - количество строк
	@param cols - количество столбцов
*/
void printArray(int** arr, int rows, int cols);

/*
*	«аполнить массив от rows * cols до 1
*
*	@param arr - указатель на двумерный массив, который надо заполнить
	@param rows - количество строк
	@param cols - количество столбцов
*/
void fillArrayBackward(int** arr, int rows, int cols);

/*
*	«аполнить массив от 1 до rows * cols вдоль главной диагонали
*	
*	@param arr - указатель на двумерный массив, который надо заполнить
	@param rows - количество строк
	@param cols - количество столбцов
*/
void fillArrayAlongMainDiag(int** arr, int rows, int cols);

/*
*	«аполнить массив от 1 до rows * cols вдоль побочной диагонали
*
*	@param arr - указатель на двумерный массив, который надо заполнить
	@param rows - количество строк
	@param cols - количество столбцов
*/
void fillArrayAlongSideDiag(int** arr, int rows, int cols);

/*
*	«аполнить массив от 1 до rows * cols спиралью
*
*	@param arr - указатель на двумерный массив, который надо заполнить
	@param rows - количество строк
	@param cols - количество столбцов
*/
void fillArraySpiral(int** arr, int rows, int cols);