#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>

#include "Scene.h"
#include "Defines.h"

#include "SDL.h"
#undef main

/*
    Вариант 1.
        Создайте классы Шестиугольник, Прямоугольник, Круг, которые хранят свое описание и положение на сцене. 
            Пусть каждый из них хранит необходимое количество переменных для описания фигуры на сцене.
        Создайте класс Фигура, который будет хранить указатель на пустоту, за которым будет скрываться фигура, а так же ее тип.
        Создайте класс сцены с параметрами, которы будет хранить в себе массив фигур.
        Заполните сцену случайными фигурами в случайном положении так, в количестве введенном пользователем, 
            чтобы они не пересекались друг с другом. (Если новую фигуру добавить не получится в течении 100 раз, 
            остановить заполнение и считать, что больше фигур поместить не получается, вывести предупреждение в консоль)
        Создайте метод, который подсчитает суммарную площадь фигур на сцене.
        (Усложненный) Смоделируйте постоянное движение фигур по сцене в течение 10 минут, с шагом 0.01 секунду. 
            Скорости определяются случайно и не меняются. Направление движения определяется случайно в начале и меняется в зависимости 
            от столкновения. Столкновения фигур со стенкой и друг другом оценивать по описанной вокруг фигуры окружности.
*/
int main()
{
    srand(time(NULL));
    
    Scene scene;

    const int max_checks = 1000;

    int N;
    std::cout << "Input count of figures: ";
    std::cin >> N;
    std::cout << "\n";

    scene.figures.reserve(N);

    for (int i = 0; i < N; i++)
        scene.figures.push_back(new Figure());

    // Не выставлялся id в цикле заполнения
    for (int i = 0; i < N; i++)
    {
        scene.figures[i]->setId(i);
        scene.figures[i]->printInfo();
    }
    
    // Рассчитываем через max_checks расположение фигур на экране.
    for (int l = 0; l < max_checks; l++)
        for (int i = 0; i < scene.figures.size(); i++)
            for (int j = 0; j < scene.figures.size(); j++)
                if (i != j)
                    scene.figures[i]->checkCollision(scene.figures[j]);
    
    int count = scene.figures.size();
    // Условимся, что на экран нельзя поместить фигуры, которые после расстоновки накладываются друг на друга.
    // Даже если радиус у первого больше, а у второго меньше.
    for (int i = 0; i < scene.figures.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (scene.figures[i]->checkPosition(scene.figures[j]))
            {
                std::cout << "CANNOT BE PLACED:\n";
                scene.figures[i]->printInfo();
                scene.figures.erase(scene.figures.begin() + i);
                i--; j--;
                break;
            }
        }
    }

    std::cout << "REMOVED: " << count - scene.figures.size() << "\n";
    std::cout << "TOTAL SQUARE: " << scene.totalSquare() << "\n";

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("WTF AM I DOIN'?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    bool isRunning = true;
    SDL_Event event;

    auto start = std::chrono::system_clock::now();
    const float work_time = 50.0f; // в минутах

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
            }
        }

        SDL_RenderClear(renderer);

        for (int k = 0; k < scene.figures.size(); k++)
            scene.figures[k]->drawFigure(renderer);

        for (int i = 0; i < scene.figures.size(); i++)
            for (int j = 0; j < scene.figures.size(); j++)
                if (i != j)
                    scene.figures[i]->checkCollision(scene.figures[j]);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Цвет фона

        SDL_RenderPresent(renderer);

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        if (elapsed_seconds.count() >= (work_time * 60))
        {
            std::cout << "TIME IS UP!\n";
            isRunning = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cin.get();

    return 0;
}