#include "Circle.h"

#include <cmath>

Circle::Circle()
{
    radius = rand() % (WIDTH / 16) + 1;
    px = rand() % (WIDTH - radius) + radius;
    py = rand() % (HEIGHT - radius) + radius;

    this->speed = Speed{ ((0.01f * (-WIDTH / (4 * radius))) + 0.01f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX),
                   ((0.01f * (-WIDTH / (4 * radius))) + 0.01f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX) };

    circle_color = RGB{ rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color, 
        rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color };
}

Circle::Circle(int _radius) : radius(_radius)
{
    px = rand() % (WIDTH - radius) + radius;
    py = rand() % (HEIGHT - radius) + radius;

    speed = Speed{ ((0.01f * (-WIDTH / (4 * radius))) + 0.1f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX),
                   ((0.01f * (-WIDTH / (4 * radius))) + 0.1f * (rand() * ((WIDTH) / (4 * radius))) / RAND_MAX) };

    circle_color = RGB{ rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color,
        rand() % (255 - min_color) + min_color, rand() % (255 - min_color) + min_color };
}

Circle::Circle(int _radius, int _px, int _py, Speed _speed, RGB _color) 
    : radius(_radius), px(_px), py(_py), speed(_speed), circle_color(_color)
{}

Circle::Circle(const Circle& _circle)
{
    this->id = _circle.id;
    this->radius = _circle.radius;
    this->px = _circle.px;
    this->py = _circle.py;
    this->speed = _circle.speed;
    this->circle_color = _circle.circle_color;
}

void Circle::drawFigure(SDL_Renderer* renderer)
{
    // Mid-point algorithm: https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm&oldid=889172082#C_example
    
    const int diameter = (this->radius * 2);

	int x = this->radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int error = (dx - diameter);

    SDL_SetRenderDrawColor(renderer, 
        this->circle_color.r, this->circle_color.g, 
        this->circle_color.b, this->circle_color.a);

	while (x >= y)
	{
        SDL_RenderDrawPoint(renderer, this->px + x, this->py + y);
        SDL_RenderDrawPoint(renderer, this->px + y, this->py + x);
        SDL_RenderDrawPoint(renderer, this->px - y, this->py + x);
        SDL_RenderDrawPoint(renderer, this->px - x, this->py + y);
        SDL_RenderDrawPoint(renderer, this->px - x, this->py - y);
        SDL_RenderDrawPoint(renderer, this->px - y, this->py - x);
        SDL_RenderDrawPoint(renderer, this->px + y, this->py - x);
        SDL_RenderDrawPoint(renderer, this->px + x, this->py - y);

        if (error <= 0)
        {
            ++y;
            error += dy;
            dy += 2;
        }

        if (error > 0)
        {
            --x;
            dx += 2;
            error += (dx - diameter);
        }
	}

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

double Circle::square()
{
	return this->PI * powf(this->radius, 2);
}

float Circle::distance(const Circle* _circle)
{
    float dX = this->px - _circle->px;
    float dY = this->py - _circle->py;

    return sqrt(pow(dX, 2) + pow(dY, 2));
}

/*
* Получаем знак от числа любого типа
* @param val - значение, от которого нужно получить знак
* @return sign - знак числа
*/ 
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void Circle::checkCollision(Circle* _circle)
{
    // Проверяем, вышли ли за границы экрана
    if (this->py - this->radius + 1 <= 0)
    {
        this->py = this->radius;
        this->speed.y *= -1;
    }

    if (this->py + this->radius - 1 >= HEIGHT)
    {
        this->py = HEIGHT - this->radius;
        this->speed.y *= -1;
    }

    if (this->px + this->radius - 1 >= WIDTH)
    {
        this->px = WIDTH - this->radius;
        this->speed.x *= -1;
    }

    if (this->px - this->radius + 1 <= 0)
    {
        this->px = this->radius;
        this->speed.x *= -1;
    }

    if (_circle->py - _circle->radius + 1 <= 0)
    {
        _circle->py = _circle->radius;
        _circle->speed.y *= -1;
    }

    if (_circle->py + _circle->radius - 1 >= HEIGHT)
    {
        _circle->py = HEIGHT - _circle->radius;
        _circle->speed.y *= -1;
    }

    if (_circle->px + _circle->radius - 1 >= WIDTH)
    {
        _circle->px = WIDTH - _circle->radius;
        _circle->speed.x *= -1;
    }

    if (_circle->px - _circle->radius + 1 <= 0)
    {
        _circle->px = _circle->radius;
        _circle->speed.x *= -1;
    }

    // Теория: https://youtu.be/KrbNkCkeRGg

    // Передвигаем фигуры
    this->px += (this->speed.x);
    this->py += (this->speed.y);

    _circle->px += (_circle->speed.x);
    _circle->py += (_circle->speed.y);

    // Рассчитываем расстояние между фигурами, если оно 0, делаем его 0.01, чтобы исключить деление на 0
    float dist = distance(_circle);
    if (dist == 0) dist = 0.01;
    float sin = (this->px - _circle->px) / dist;
    float cos = (this->py - _circle->py) / dist;
    if (dist < this->radius + _circle->radius)          // Произошло пересечение
    {
        float vector_norm1 = _circle->speed.x * sin + _circle->speed.y * cos;       // Считаем нормаль первой фигуры
        float vector_norm2 = this->speed.x * sin + this->speed.y * cos;             // Считаем нормаль второй фигуры
        float dt = (this->radius + _circle->radius - dist) / (vector_norm1 - vector_norm2);     // Считаем скорость

        if (dt > (this->radius + _circle->radius)) dt = (this->radius + _circle->radius);
        if (dt < -(this->radius + _circle->radius)) dt = -(this->radius + _circle->radius);

        // Отодвигаем фигуры на расстояние их скорости * на расстояние радиусов
        this->px -= this->speed.x * dt;
        this->py -= this->speed.y * dt;
        _circle->px -= _circle->speed.x * dt;
        _circle->px -= _circle->speed.y * dt;

        // Повторно считаем, столкнулись ли
        dist = distance(_circle);
        if (dist == 0) dist = 0.01;
        sin = (this->px - _circle->px) / dist;
        cos = (this->py - _circle->py) / dist;

        vector_norm1 = _circle->speed.x * sin + _circle->speed.y * cos;
        vector_norm2 = this->speed.x * sin + this->speed.y * cos;

        // Считаем векторы транспонирования, т.е. новые скорости, согласно абсолютно упругому удару (без учёта масс, считаем, что они равны)
        float vector_trans1 = -_circle->speed.x * cos + _circle->speed.y * sin;
        float vector_trans2 = -this->speed.x * cos + this->speed.y * sin;

        float temp = vector_norm2;
        vector_norm2 = vector_norm1;
        vector_norm1 = temp;

        // Считаем новые скорости с учётом углов оттлакивания
        this->speed.x = vector_norm2 * sin - vector_trans2 * cos;
        this->speed.y = vector_norm2 * cos + vector_trans2 * sin;
        _circle->speed.x = vector_norm1 * sin - vector_trans1 * cos;
        _circle->speed.y = vector_norm1 * cos + vector_trans1 * sin;

        // Отодвигаем
        this->px += this->speed.x * dt;
        this->py += this->speed.y * dt;
        _circle->px += _circle->speed.x * dt;
        _circle->py += _circle->speed.y * dt;
    }
}

bool Circle::checkPosition(Circle* _circle)
{
    if (this->py - this->radius + 1 <= 0)
        this->py = this->radius;

    if (this->py + this->radius - 1 >= HEIGHT)
        this->py = HEIGHT - this->radius;

    if (this->px + this->radius - 1 >= WIDTH)
        this->px = WIDTH - this->radius;

    if (this->px - this->radius + 1 <= 0)
        this->px = this->radius;

    float dist = distance(_circle);
    if (dist == 0) dist = 0.01;
    if (dist < this->radius + _circle->radius)
    {
        std::cout << "---------------------------------------\n";
        std::cout << "INTERSECTED!\n";
        this->printInfo();
        _circle->printInfo();
        std::cout << "---------------------------------------\n\n";
        return true;
    }
    else
    {
        return false;
    }
}

void Circle::printInfo()
{
    std::cout << "ID: " << this->id << "\n";
    std::cout << "TYPE: CIRCLE\n";
    std::cout << "RADIUS: " << this->radius << "\n";
    std::cout << "SQUARE: " << this->square() << "\n";
    std::cout << "COLOR: rgba(" << this->circle_color.r << ", " << this->circle_color.g << ", "
        << this->circle_color.b << ", " << this->circle_color.a << ")\n";
    std::cout << "PX: " << this->px << " PY: " << this->py << "\n";
    std::cout << "SPEED X: " << this->speed.x << " SPEED Y: " << this->speed.y << "\n\n";
}

void Circle::setId(int id)
{
    this->id = id;
}