#include "Weapon.h"

#include "Functions.h"

Weapon::Weapon() {}

Weapon::Weapon(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* bullet_texture)
    : renderer(renderer), texture(texture), bullet_texture(bullet_texture) { }

Weapon::Weapon(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* bullet_texture, 
                float bullet_damage, int max_bullets_count, Speed bullet_speed)
    : renderer(renderer), texture(texture), bullet_texture(bullet_texture), 
       max_bullets_count(max_bullets_count), bullet_damage(bullet_damage), bullet_speed(bullet_speed) { }

Weapon::~Weapon()
{
    for (auto& bullet : bullets)
        delete bullet;
    bullets.clear();

    bullet_texture = nullptr;
	texture = nullptr;
	renderer = nullptr;
}

void Weapon::reload()
{
    bullets_count = max_bullets_count;
}

void Weapon::shoot(Uint32 buttons, float mouse_x, float mouse_y)
{
    int count = 0;
    if ((buttons & SDL_BUTTON_LMASK) != 0)
        count = one_shot_count;
    else if ((buttons & SDL_BUTTON_RMASK) != 0)
        count = burst_shot_count;

    if (bullets_count <= 0)
    {
        bullets_count = 0;
        count = 0;
    }
    else if (bullets_count - count < 0)
    {
        count = bullets_count;
        bullets_count = 0;
    }
    else
    {
        bullets_count -= count;
    }

    for (int i = 0; i < count; i++)
    {
        bullets.push_back(new Bullet(
            px + width + 10.0f * (i * 3),
            py - 3.0f * i,
            mouse_x, mouse_y,
            bullet_damage,
            bullet_speed,
            renderer,
            bullet_texture));
    }
}

void Weapon::draw()
{
	renderTexture(renderer, texture, px, py, width, height);
}
