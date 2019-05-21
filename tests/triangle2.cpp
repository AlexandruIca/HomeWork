#include "graphics.hpp"

int main()
{
    return draw(WITH {
        triangle(width() / 2, height() / 2 - 100, width() / 2 - 100,
                 height() / 2 + 100, width() / 2 + 100, height() / 2 + 100,
                 RED);
    });
}
