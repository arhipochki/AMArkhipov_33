#include "Scene.h"

Scene::~Scene()
{
    for (auto& figure : figures)
    {
        delete figure;
    }

    figures.clear();
}

double Scene::totalSquare()
{
    double total = 0.0f;
    for (auto& figure : this->figures)
        total += figure->square();

    return total;
}