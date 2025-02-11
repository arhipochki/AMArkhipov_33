﻿#include <vector>

#include "Functions.h"
#include "Defines.h"
#include "Mouse.h"
#include "ShootingRange.h"
#undef main;

/*
    Вариант 1
    Необходимо реализовать класс оружия, который может стрелять по разному виду мишеней. При этом:

        У оружия есть магазин и он заполняется до максимума патронами.
        Огонь может вестись одиночными или очередями, при этом цель соответственно может получать урон 
            либо от каждого патрона по очереди при стрельбе одиночными, либо от группы патронов при стрельбе очередью.
        Шанс попадания по цели лежит в границах от 0 до 1(double) и рассчитывается 
            на основании параметров цели (зависит от видимости мишени и ее движения).
        При стрельбе генерируется случайное число в том же интервале значений, 
            которое сверяется с шансом и если оно больше, то попадание засчитывается, меньше не засчитывается.
        Мишень может иметь ряд характеристик: расстояние до мишени на стрельбище, 
            размер (площадь мишени, рассчитывается в зависимости от геометрии мишени, определяется разработчиком), 
            форма мишени, материал (отсвечивает или нет), видимость мишени на стрельбище (зависит от расстояния, 
            размера, материала, значит является расчетным), некоторые мишени могут быть движущимися, что влияет на шанс попадания по цели.
        Количество мишеней на стрельбище генерируется случайным образом, при этом их варианты 
            генерируется случайным образом и хранятся так, что работа с ними не зависит от их реального типа.
        Каждая мишень имеет параметр предельного количества попаданий, который определяет 
            после какого количества выстрелов мишень разрушается и перестает быть доступной для стрельбы.
        
        Любая цель должна иметь следующие методы:
            Предоставления шанс попадания по цели
            Получение урона, принимает в себя количество попаданий
            Предоставление доступности для дальнейшей стрельбы
    Требуется:
    Реализовать класс стрельбища, на котором будет находится оружие и мишени.
    Реализовать интерфейсный или абстрактный класс мишени и несколько конкретных классов мишеней. 
        Каждый класс должен иметь свои характеристики, которые могут пересекаться с другими классами, 
           но должна быть хотя бы 1 уникальная, которая будет влиять на расчет шанса попадания, а также разный порог попаданий.
    (На половину баллов) Продемонстрировать работу стрельбища и мишеней.
    (Усложненный вариант) Провести симуляцию стрельбы из оружия по мишени в течении 1 минуты. 
        Скорострельность одиночного режима и режима стрельбы очередями генерировать для оружия перед началом симуляции, 
        при это в процессе режим стрельбы может изменится с некоторым шансом определяемым разработчиком.
    (Усложненный вариант) В конце вывести количество разрушенных мишеней, 
            количество оставшихся, средний урон, нанесенный по мишеням.
*/

int main()
{
    srand(time(NULL));

    SDL_Window* window = SDL_CreateWindow("WTF AM I DOIN'? PART 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    bool isRunning = init();

    SDL_Event event;

    ShootingRange* shooting_range = new ShootingRange(renderer);

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

                if (event.key.keysym.sym == SDLK_r)
                {
                    shooting_range->weapon->reload();
                }

                if (event.key.keysym.sym == SDLK_1)
                {
                    shooting_range->changeWeaponOn(1);
                }

                if (event.key.keysym.sym == SDLK_2)
                {
                    shooting_range->changeWeaponOn(2);
                }

                if (event.key.keysym.sym == SDLK_n && shooting_range->isStatisticsShown())
                {
                    shooting_range->generateTargets();
                }

            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                Uint32 buttons;

                SDL_PumpEvents();  // Получаем последнее событие мыши

                buttons = SDL_GetMouseState(&x, &y); // 1 - левая, 4 - правая

                shooting_range->weapon->shoot(buttons, x, y);
                
                break;
            }
        }

        SDL_RenderClear(renderer);

        shooting_range->draw();

        SDL_RenderPresent(renderer);
    }

    delete shooting_range;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}