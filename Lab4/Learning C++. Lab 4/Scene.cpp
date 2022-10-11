#include "Scene.h"

double Scene::totalSquare()
{
    double total = 0.0f;
    for (auto& figure : this->figures)
        total += figure->square();

    return total;
}
