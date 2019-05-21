#include "graphics.hpp"

int main()
{
    set_width(1280);
    set_height(720);

    triangle(100, 20, 40, 220, 1000, 700, LIME);

    triangle(1000, 700, 900, 600, 100, 20, CYAN);

    return draw();
}
