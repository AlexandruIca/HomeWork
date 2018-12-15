#include "graphics.hpp"

int main()
{
    set_width(1280);
    set_height(720);

    triangle(20, 20, 900, 10, 800, 700, AMBER);

    return draw();
}

