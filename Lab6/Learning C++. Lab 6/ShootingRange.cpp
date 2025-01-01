#include "ShootingRange.h"

#include "Functions.h"

ShootingRange::ShootingRange() { }

ShootingRange::ShootingRange(SDL_Renderer* renderer)
    : renderer(renderer)
{
    const int N = 9;
    std::string path[N] = { "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\ShineTarget.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\fireded.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\MovingTarget.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\FireBall.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\Background.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\iceded.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\iceball.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\bedolaga.png",
                            "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\imgs\\cursor.png" };

    std::string font_path = "C:\\Users\\lexan\\source\\repos\\Learning C++. Lab 6\\x64\\Debug\\fonts\\DePixelKlein.ttf";

    for (int i = 0; i < N; i++)
        textures.push_back(loadTexture(renderer, path[i]));

    background_texture = textures[4];

    bullet_texture = textures[3];

    weapon = new Weapon(renderer, textures[1], bullet_texture);

    mouse = new Mouse(renderer, textures[8]);

    generateTargets();

    font = openFont(font_path, 64);
}

ShootingRange::~ShootingRange()
{
    delete mouse;
    renderer = nullptr;

    delete weapon;

    for (auto& target : targets)
    {
        delete target;
    }
    targets.clear();

    for (auto& texture : textures)
        SDL_DestroyTexture(texture);
    textures.clear();

    TTF_CloseFont(font);

    SDL_DestroyTexture(font_image);
    SDL_DestroyTexture(bullet_texture);
}

void ShootingRange::draw()
{
    renderTexture(renderer, background_texture, 0, 0, WIDTH, HEIGHT);

    mouse->update();

    if (weapon->bullets_count == 0)
    {
        font_image = renderText(renderer, font, "Press R to reload", font_color);
        renderTexture(renderer, font_image, 5, 5, 300, 50);
    }
    else
    {
        font_image = renderText(renderer, font, std::to_string(weapon->bullets_count) + "/" + std::to_string(weapon->max_bullets_count), font_color);
        renderTexture(renderer, font_image, 5, 5, 100, 50);
    }

    bool all_destroyed = true;

    for (auto& target : targets)
        all_destroyed &= target->destroyed;

    if (all_destroyed)
    {
        int image_width = 300;
        int image_heigth = 200;

        font_image = renderText(renderer, font, "THE END!", font_color);
        renderTexture(renderer, font_image, WIDTH / 2 - image_width / 2,
            HEIGHT / 2 - image_heigth / 2);

        font_image = renderText(renderer, font, "Press N for new targets!", font_color);
        renderTexture(renderer, font_image, WIDTH / 2 - image_width,
            HEIGHT / 2 + image_heigth / 4, image_width * 2, image_heigth / 2);

        if (!statistics_shown)
        {
            std::cout << "STATISTICS:\n";

            float avg_damage = 0.0f;

            for (auto& target : targets)
            {
                target->printStatistics();
                avg_damage += target->damage_taken;
            }

            std::cout << "AVG DAMAGE: " << avg_damage / targets.size() << "\n";

            for (auto& target : targets)
                delete target;
            targets.clear();

            statistics_shown = true;
        }
    }
    weapon->draw();

    for (auto& target : targets)
        if (target->isShown())
            target->draw();

    for (int i = 0; i < targets.size(); i++)
    {
        targets[i]->move();
        for (int j = 0; j < targets.size(); j++)
            if (j != i)
                targets[j]->checkCollision(targets[i]);
    }

    for (auto& bullet : weapon->bullets)
    {
        bullet->draw();
        bullet->move();
        for (auto& target : targets)
            bullet->checkCollision(target);
    }

    mouse->draw();

    for (int i = 0; i < weapon->bullets.size(); i++)
    {
        if (weapon->bullets[i]->isDestroyed())
        {
            weapon->bullets[i]->~Bullet();
            weapon->bullets.erase(weapon->bullets.begin() + i);
        }
    }
}

void ShootingRange::changeWeaponOn(int weapon_id)
{
    switch (weapon_id)
    {
        case 1: // Огненый маг
            delete weapon; 
            weapon = new Weapon(renderer, textures[1], textures[3]);
            break;
        case 2: // Ледяной маг
            delete weapon;
            weapon = new Weapon(renderer, textures[5], textures[6], 7.0f, 5, { 2.5f, 2.5f });
            break;
        default:
            break;
    }
}

void ShootingRange::generateTargets()
{
    statistics_shown = false;
    targets.clear();

    int max_targets_count = 10;

    int targets_count = rand() % max_targets_count + 1;

    for (int i = 0; i < targets_count; i++)
    {
        int choice = rand() % 3;

        if (choice == 0)
            targets.push_back(new ShineTarget(renderer, textures[0], i));
        if (choice == 1)
            targets.push_back(new OrdinaryTarget(renderer, textures[7], i));
        if (choice == 2)
            targets.push_back(new MovingTarget(renderer, textures[2], i));
    }
}

bool ShootingRange::isStatisticsShown()
{
    return statistics_shown;
}
