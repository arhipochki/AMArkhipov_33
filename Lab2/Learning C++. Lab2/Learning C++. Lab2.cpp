#include <iostream>

#include "functions.h"

/*

	Вариант 2. Требуется написать программу которая выполняет следующие действия.

	1. Получить от пользователя значение N.
	2. Выделить память под двумерный массив N*N. Тип массива int.
	3. Заполнить массив значениями в порядке возрастания от 1 до N*N, так, что элемент [N - 1][N - 1] будет равен N * N.
	4. Предложить пользователю возможность выполнить манипуляции с порядком элементов в массиве.
		- Восстановить прямой порядок элементов(Не является отдельным действием в рамках базовой части задание, т.е. 
			помимо него нужно реализовать еще 2).
		- Сделать обратный порядок элементов (т.е. элемент [N - 1][N - 1] будет иметь значение 1)
		- Сделать порядок элементов таким, что бы они были выложены вдоль главной диагонали.
		- Сделать порядок элементов таким, что бы они были выложены вдоль побочной диагонали.
		- Сделать порядок элементов таким, что бы все значения закручивались по часовой стрелке спиралью от элемента [0,0].

*/
int main()
{
	int N;

	std::cout << "Input an array size: ";
	std::cin >> N;
	std::cout << "\n";

	int** arr = createArray(N, N);

	fillArray(arr, N, N);

	int ans = 0;
	while (true)
	{
		printArray(arr, N, N);

		std::cout << "Actions:\n"
			<< "1) Fill normal\n"
			<< "2) Fill backward\n"
			<< "3) Fill along main diagonal\n"
			<< "4) Fill along side diagonal\n"
			<< "5) Fill like round spiral (from 0,0)\n"
			<< "0) Exit\n";

		std::cout << "Input an action: ";
		std::cin >> ans;
		std::cout << "\n";

		switch (ans)
		{
		case 0:
			return 0;
		case 1:
			fillArray(arr, N, N);
			break;
		case 2:
			fillArrayBackward(arr, N, N);
			break;
		case 3:
			fillArrayAlongMainDiag(arr, N, N);
			break;
		case 4:
			fillArrayAlongSideDiag(arr, N, N);
			break;
		case 5:
			fillArraySpiral(arr, N, N);
			break;
		default:
			break;
		}

		system("cls");
	}

	freeArray(arr, N);

	return 0;
}