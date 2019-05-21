#include "graphics.hpp"

void update(float const t_time)
{
    line(width() / 2 - 100, height() / 2 + 100, width() / 2 + 100,
         height() / 2 + 100);
}

int main()
{
    line(width() / 2 - 100, height() / 2 - 100, width() / 2 + 100,
         height() / 2 - 100);
    return draw(update);
}
