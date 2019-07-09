#include "graphics.hpp"

void update(float const)
{
    circle(width() / 2, height() / 2, 300, AMBER);
}

int main(int, char*[])
{
    return draw(update);
}
